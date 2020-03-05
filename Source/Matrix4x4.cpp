#include "Matrix4x4.h"
#include "Matrix3x3.h"

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
}