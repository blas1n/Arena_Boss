#include "Matrix4x4.h"
#include <glm/gtx/quaternion.hpp>
#include "MathFunctions.h"
#include "Matrix3x3.h"
#include "Quaternion.h"
#include "Rotator.h"

namespace ArenaBoss::Math
{
    constexpr Matrix4x4 Matrix4x4::ONE()
    {
        return Matrix4x4{ 1.0f };
    }

    constexpr Matrix4x4 Matrix4x4::ZERO()
    {
        return Matrix4x4{ 0.0f };
    }

    constexpr Matrix4x4 Matrix4x4::IDENTITY()
    {
        return Matrix4x4
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
        };
    }

    Matrix4x4::Matrix4x4(const Matrix3x3& mat) noexcept
        : value(mat.value) {}

    Matrix4x4& Matrix4x4::operator=(const Matrix3x3& other) noexcept
    {
        value = glm::mat4{ other.value };
        return *this;
    }

    void Matrix4x4::Set(
        float inM00, float inM01, float inM02, float inM03,
        float inM10, float inM11, float inM12, float inM13,
        float inM20, float inM21, float inM22, float inM23,
        float inM30, float inM31, float inM32, float inM33) noexcept
    {
        m00 = inM00;
        m01 = inM01;
        m02 = inM02;
        m03 = inM03;
        m10 = inM10;
        m11 = inM11;
        m12 = inM12;
        m13 = inM13;
        m20 = inM20;
        m21 = inM21;
        m22 = inM22;
        m23 = inM23;
        m30 = inM30;
        m31 = inM31;
        m32 = inM32;
        m33 = inM33;
    }

    Vector3 Matrix4x4::GetScale() const
    {
        return Vector3{ GetXAxis().Length(), GetYAxis().Length(), GetZAxis().Length() };
    }

    Matrix4x4 Matrix4x4::CreateFromPosition(const Vector3& position)
    {
        return CreateFromPosition(position.x, position.y, position.z);
    }

    Matrix4x4 Matrix4x4::CreateFromPosition(float x, float y, float z)
    {
        const float temp[]
        {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
               x,    y,    z, 1.0f
        };

        return Matrix4x4{ temp };
    }

    Matrix4x4 Matrix4x4::CreateFromPosition(float position)
    {
        return CreateFromPosition(position, position, position);
    }

    Matrix4x4 Matrix4x4::CreateFromRotationX(float theta)
    {
        const float temp[]
        {
            1.0f,              0.0f,             0.0f, 0.0f,
            0.0f,  Math::Cos(theta), Math::Sin(theta), 0.0f,
            0.0f, -Math::Sin(theta), Math::Cos(theta), 0.0f,
            0.0f,              0.0f,             0.0f, 1.0f
        };

        return Matrix4x4{ temp };
    }

    Matrix4x4 Matrix4x4::CreateFromRotationY(float theta)
    {
        const float temp[]
        {
            Math::Cos(theta), 0.0f, -Math::Sin(theta), 0.0f,
                        0.0f, 1.0f,              0.0f, 0.0f,
            Math::Sin(theta), 0.0f,  Math::Cos(theta), 0.0f,
                        0.0f, 0.0f,              0.0f, 1.0f
        };

        return Matrix4x4{ temp };
    }

    Matrix4x4 Matrix4x4::CreateFromRotationZ(float theta)
    {
        const float temp[]
        {
             Math::Cos(theta), Math::Sin(theta), 0.0f, 0.0f,
            -Math::Sin(theta), Math::Cos(theta), 0.0f, 0.0f,
                         0.0f,             0.0f, 1.0f, 0.0f,
                         0.0f,             0.0f, 0.0f, 1.0f
        };

        return Matrix4x4{ temp };
    }

    Matrix4x4 Matrix4x4::CreateFromRotation(const Rotator& rotator)
    {
        return CreateFromRotation(rotator.AsQuaternion());
    }

    Matrix4x4 Matrix4x4::CreateFromRotation(const Quaternion& quat)
    {
        return glm::toMat4(quat.value);
    }

    Matrix4x4 Matrix4x4::CreateFromScale(const Vector3& scale)
    {
        return CreateFromScale(scale.x, scale.y, scale.z);
    }

    Matrix4x4 Matrix4x4::CreateFromScale(float x, float y, float z)
    {
        const float temp[]
        {
               x, 0.0f, 0.0f, 0.0f,
            0.0f,    y, 0.0f, 0.0f,
            0.0f, 0.0f,    z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };

        return Matrix4x4{ temp };
    }

    Matrix4x4 Matrix4x4::CreateFromScale(float scale)
    {
        return CreateFromScale(scale, scale, scale);
    }

    Matrix4x4 Matrix4x4::CreateLookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
    {
        return glm::lookAt(eye.value, center.value, up.value);
    }

    Matrix4x4 Matrix4x4::CreateOrtho(float width, float height, float near, float far)
    {
        return glm::ortho(0.0f, width, 0.0f, height, near, far);
    }

    Matrix4x4 Matrix4x4::CreatePerspectiveFOV(float fov, float width, float height, float near, float far)
    {
        return glm::perspectiveFov(fov, width, height, near, far);
    }

    Matrix4x4 Matrix4x4::CreateSimpleViewProjection(float width, float height)
    {
        const float temp[]
        {
            2.0f / width,          0.0f, 0.0f, 0.0f,
                    0.0f, 2.0f / height, 0.0f, 0.0f,
                    0.0f,          0.0f, 1.0f, 0.0f,
                    0.0f,          0.0f, 1.0f, 1.0f
        };

        return Matrix4x4{ temp };
    }
}