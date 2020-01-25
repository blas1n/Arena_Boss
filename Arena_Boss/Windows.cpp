#include "Windows.h"
#include "Util.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Windows::Windows(const tstring& title, int width, int height,
    int sampleCount, int sampleQuality)
    : programPath(/*FileSystem::CurrentRunningPath() 파일 시스템 구축 후 주석 해제*/),
    hInstance(GetModuleHandle(nullptr)),
    windowTitle(title)
{
    InitWindows(width, height);
    InitD3D(sampleCount, sampleQuality);
}

Windows::~Windows()
{
    DestroyD3D();
    DestroyWindows();
}

void Windows::InitWindows(int width, int height)
{
    assert(width > 0 && height > 0);

    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = nullptr;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = windowClassName.c_str();
    wc.hIconSm = nullptr;

    assert(RegisterClassEx(&wc));

    DWORD style = 0;
    style |= WS_VISIBLE;
    style &= ~WS_SIZEBOX;

    RECT winRect = { 0, 0, width, height };
    if (!AdjustWindowRect(&winRect, style, FALSE))
    {
        UnregisterClass(windowClassName.c_str(), hInstance);
        assert(false);
    }

    const auto resolution = Math::Vector2
    {
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN)
    };

    size.SetX(winRect.right - winRect.left);
    size.SetX(winRect.bottom - winRect.top);
    pos = (resolution - size) / 2;
    center = resolution / 2;

    hWnd = CreateWindow(
        windowClassName.c_str(), windowTitle.c_str(),
        style, pos.GetX(), pos.GetY(),
        size.GetX(), size.GetY(),
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hWnd)
    {
        UnregisterClass(windowClassName.c_str(), hInstance);
        assert(false);
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
    SetForegroundWindow(hWnd);
    SetFocus(hWnd);

    UpdateClientPos();
}

void Windows::InitD3D(int sampleCount, int sampleQuality)
{
    assert(CreateD3DDevice());

    UINT maxMSAAQuality = 0;
    auto hr = device->CheckMultisampleQualityLevels(
        SWAPCHAIN_BUFFER_FORMAT, sampleCount, &maxMSAAQuality);

    if (FAILED(hr) || sampleQuality >= maxMSAAQuality)
    {
        DestroyD3D();
        assert(false);
    }

    if (!CreateSwapChain(sampleCount, sampleQuality))
    {
        DestroyD3D();
        assert(false);
    }

    if (!CreateRenderTargetView())
    {
        DestroyD3D();
        assert(false);
    }

    if (!CreateDepthStencilBuffer(sampleCount, sampleQuality))
    {
        DestroyD3D();
        assert(false);
    }
    
    deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
    SetDefaultViewport();
    deviceContext->IASetPrimitiveTopology(PRIMITIVE_TOPOLOGY);
}

void Windows::UpdateClientPos()
{
    RECT rect;
    GetClientRect(hWnd, &rect);

    POINT LT{ rect.left, rect.top };
    POINT RB{ rect.right, rect.bottom };

    ClientToScreen(hWnd, &LT);
    ClientToScreen(hWnd, &RB);

    pos = LT;
    size = RB;
    size -= LT;
    center = pos + (size / 2);
}

bool Windows::CreateD3DDevice()
{
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
    UINT createDeviceFlag = 0;

#ifdef _DEBUG
    createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    auto hr = D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        createDeviceFlag,
        &featureLevel, 1,
        D3D11_SDK_VERSION,
        &device,
        nullptr,
        &deviceContext
    );

    return SUCCEEDED(hr);
}

bool Windows::CreateSwapChain(int sampleCount, int sampleQuality)
{
    DXGI_MODE_DESC scBuf;
    scBuf.Width = size.GetX();
    scBuf.Height = size.GetY();
    scBuf.RefreshRate.Numerator = 60;
    scBuf.RefreshRate.Denominator = 1;
    scBuf.Format = SWAPCHAIN_BUFFER_FORMAT;
    scBuf.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scBuf.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    DXGI_SWAP_CHAIN_DESC sc;
    sc.BufferDesc = scBuf;
    sc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sc.BufferCount = 1;
    sc.OutputWindow = hWnd;
    sc.Windowed = true;
    sc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sc.Flags = 0;
    sc.SampleDesc.Count = sampleCount;
    sc.SampleDesc.Quality = sampleQuality;

    IDXGIDevice* dxgiDevice = nullptr;
    auto hr = device->QueryInterface<IDXGIDevice>(&dxgiDevice);
    if (FAILED(hr))
        return false;

    IDXGIAdapter* dxgiAdapter = nullptr;
    hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter));
    Util::ReleaseCOMObjects(dxgiDevice);
    if (FAILED(hr))
        return false;

    IDXGIFactory* dxgiFactory = nullptr;
    hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgiFactory));
    Util::ReleaseCOMObjects(dxgiAdapter);
    if (FAILED(hr))
        return false;

    hr = dxgiFactory->CreateSwapChain(device, &sc, &swapChain);
    Util::ReleaseCOMObjects(dxgiFactory);
    return SUCCEEDED(hr);
}

bool Windows::CreateRenderTargetView()
{
    ID3D11Texture2D* buf;
    HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buf));
    if (FAILED(hr))
        return false;

    hr = device->CreateRenderTargetView(buf, nullptr, &renderTargetView);
    Util::ReleaseCOMObjects(buf);
    return SUCCEEDED(hr);
}

bool Windows::CreateDepthStencilBuffer(int sampleCount, int sampleQuality)
{
    D3D11_TEXTURE2D_DESC depthStencilBufDesc;
    depthStencilBufDesc.ArraySize = 1;
    depthStencilBufDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilBufDesc.CPUAccessFlags = 0;
    depthStencilBufDesc.Format = DEPTHSTENCIL_BUFFER_FORMAT;
    depthStencilBufDesc.Width = size.GetX();
    depthStencilBufDesc.Height = size.GetY();
    depthStencilBufDesc.MipLevels = 1;
    depthStencilBufDesc.MiscFlags = 0;
    depthStencilBufDesc.SampleDesc.Count = sampleCount;
    depthStencilBufDesc.SampleDesc.Quality = sampleQuality;
    depthStencilBufDesc.Usage = D3D11_USAGE_DEFAULT;

    auto hr = device->CreateTexture2D(
        &depthStencilBufDesc, nullptr,
        &depthStencilBuffer
    );

    if (FAILED(hr))
        return false;

    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = sampleCount > 1 ?
        D3D11_DSV_DIMENSION_TEXTURE2DMS : D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Flags = 0;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    hr = device->CreateDepthStencilView(
        depthStencilBuffer,
        &depthStencilViewDesc,
        &depthStencilView
    );

    return SUCCEEDED(hr);
}

void Windows::DestroyWindows()
{
    if (hWnd)
        DestroyWindow(hWnd);

    UnregisterClass(windowClassName.c_str(), hInstance);
}

void Windows::DestroyD3D()
{
    Util::ReleaseCOMObjects(swapChain, deviceContext,
        renderTargetView, depthStencilBuffer, depthStencilView);

#ifdef _DEBUG
    if (device)
    {
        ID3D11Debug* debug = nullptr;
        HRESULT hr = device->QueryInterface<ID3D11Debug>(&debug);
        if (SUCCEEDED(hr))
            debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
        Util:: ReleaseCOMObjects(debug);
    }
#endif

    Util::ReleaseCOMObjects(device);
}

void Windows::SetDefaultViewport(void)
{
   D3D11_VIEWPORT vp;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.Width = size.GetX();
    vp.Height = size.GetY();
    vp.MaxDepth = 1.0f;
    vp.MinDepth = 0.0f;
    deviceContext->RSSetViewports(1, &vp);
}

void Windows::DoEvents()
{
    MSG msg;
    
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}