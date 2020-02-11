#include "D3D.h"
#include "Util.h"
#include "Windows.h"

#pragma comment(lib, "d3d11.lib")

namespace ArenaBoss
{
    D3D::D3D(Windows& inWindows, uint32_t sampleCount, uint32_t sampleQuality)
        : backgroundColor(), windows(inWindows)
    {
        assert(CreateD3DDevice());

        UINT maxMSAAQuality = 0;
        auto hr = device->CheckMultisampleQualityLevels(
            SWAPCHAIN_BUFFER_FORMAT, sampleCount, &maxMSAAQuality);

        assert(SUCCEEDED(hr) && sampleQuality < maxMSAAQuality);

        assert(CreateSwapChain(sampleCount, sampleQuality));
        assert(CreateRenderTargetView());
        assert(CreateDepthStencilBuffer(sampleCount, sampleQuality));

        deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
        SetDefaultViewport();
        deviceContext->IASetPrimitiveTopology(PRIMITIVE_TOPOLOGY);
    }

    D3D::~D3D()
    {
        Util::ReleaseObjects(swapChain, deviceContext,
            renderTargetView, depthStencilBuffer, depthStencilView);

#   ifdef _DEBUG
        if (device)
        {
            ID3D11Debug* debug = nullptr;
            HRESULT hr = device->QueryInterface<ID3D11Debug>(&debug);
            if (SUCCEEDED(hr))
                debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
            Util::ReleaseObjects(debug);
        }
#   endif

        Util::ReleaseObjects(device);
    }

    void D3D::SetDefaultViewport()
    {
        const auto size = windows.GetSize();

        D3D11_VIEWPORT vp;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        vp.Width = size.x;
        vp.Height = size.y;
        vp.MaxDepth = 1.0f;
        vp.MinDepth = 0.0f;
        deviceContext->RSSetViewports(1, &vp);
    }

    bool D3D::CreateD3DDevice()
    {
        auto featureLevel = D3D_FEATURE_LEVEL_11_0;
        UINT createDeviceFlag = 0;

#   ifdef _DEBUG
        createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#   endif

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

    bool D3D::CreateSwapChain(uint32_t sampleCount, uint32_t sampleQuality)
    {
        const auto size = windows.GetSize();

        DXGI_MODE_DESC scBuf;
        scBuf.Width = static_cast<UINT>(size.x);
        scBuf.Height = static_cast<UINT>(size.y);
        scBuf.RefreshRate.Numerator = 60;
        scBuf.RefreshRate.Denominator = 1;
        scBuf.Format = SWAPCHAIN_BUFFER_FORMAT;
        scBuf.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        scBuf.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

        DXGI_SWAP_CHAIN_DESC sc;
        sc.BufferDesc = scBuf;
        sc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sc.BufferCount = 1;
        sc.OutputWindow = windows.GetWindowsHandle();
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
        Util::ReleaseObjects(dxgiDevice);
        if (FAILED(hr))
            return false;

        IDXGIFactory* dxgiFactory = nullptr;
        hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&dxgiFactory));
        Util::ReleaseObjects(dxgiAdapter);
        if (FAILED(hr))
            return false;

        hr = dxgiFactory->CreateSwapChain(device, &sc, &swapChain);
        Util::ReleaseObjects(dxgiFactory);
        return SUCCEEDED(hr);
    }

    bool D3D::CreateRenderTargetView()
    {
        ID3D11Texture2D* buf;
        HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buf));
        if (FAILED(hr))
            return false;

        hr = device->CreateRenderTargetView(buf, nullptr, &renderTargetView);
        Util::ReleaseObjects(buf);
        return SUCCEEDED(hr);
    }

    bool D3D::CreateDepthStencilBuffer(uint32_t sampleCount, uint32_t sampleQuality)
    {
        const auto size = windows.GetSize();

        D3D11_TEXTURE2D_DESC depthStencilBufDesc;
        depthStencilBufDesc.ArraySize = 1;
        depthStencilBufDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depthStencilBufDesc.CPUAccessFlags = 0;
        depthStencilBufDesc.Format = DEPTHSTENCIL_BUFFER_FORMAT;
        depthStencilBufDesc.Width = static_cast<UINT>(size.x);
        depthStencilBufDesc.Height = static_cast<UINT>(size.y);
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
}