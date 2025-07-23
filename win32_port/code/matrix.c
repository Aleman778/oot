#include "ultra64/ultratypes.h"
#include "matrix.h"

Mat4 mat4_identity() {
    Mat4 result = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    return result;
}

Mat4
mat4_orthographic(f32 left, f32 top, f32 right, f32 bottom, f32 near, f32 far) {
    Mat4 result;
    bzero(&result, sizeof(Mat4));
    result.m00 = 2.0f / (right - left);
    result.m11 = 2.0f / (top - bottom);
    result.m22 = 2.0f / (far - near);
    result.m33 = 1.0f;
    
    result.m03 = -(right + left) / (right - left);
    result.m13 = -(top + bottom) / (top - bottom);
    result.m23 = -(far + near) / (far - near);    
    return result;
}
#ifndef PI_F32
#define PI_F32 3.14159265358979323846f
#endif

f32
degrees_to_radians(f32 degrees) {
    return degrees * PI_F32 / 180.0f;
}

Mat4
mat4_perspective(f32 fov, f32 aspect_ratio, f32 near, f32 far) {
    
    f32 tan_half_fov = tanf(degrees_to_radians(fov/2.0f));
    f32 z_range = near - far;
    
    Mat4 result;
    bzero(&result, sizeof(Mat4));
    result.m00 = 1.0f / (tan_half_fov * aspect_ratio);
    result.m11 = 1.0f / (tan_half_fov);
    result.m22 = (-far - near) / z_range;
    result.m23 = (2.0f*far*near) / z_range;
    result.m32 = 1.0f;
    return result;
}

Mat4
mat4_mul(Mat4 a, Mat4 b) {
    Mat4 result;
    result.m00 = a.m00*b.m00 + a.m01*b.m10 + a.m02*b.m20 + a.m03*b.m30;
    result.m01 = a.m00*b.m01 + a.m01*b.m11 + a.m02*b.m21 + a.m03*b.m31;
    result.m02 = a.m00*b.m02 + a.m01*b.m12 + a.m02*b.m22 + a.m03*b.m32;
    result.m03 = a.m00*b.m03 + a.m01*b.m13 + a.m02*b.m23 + a.m03*b.m33;
    
    result.m10 = a.m10*b.m00 + a.m11*b.m10 + a.m12*b.m20 + a.m13*b.m30;
    result.m11 = a.m10*b.m01 + a.m11*b.m11 + a.m12*b.m21 + a.m13*b.m31;
    result.m12 = a.m10*b.m02 + a.m11*b.m12 + a.m12*b.m22 + a.m13*b.m32;
    result.m13 = a.m10*b.m03 + a.m11*b.m13 + a.m12*b.m23 + a.m13*b.m33;
    
    result.m20 = a.m20*b.m00 + a.m21*b.m10 + a.m22*b.m20 + a.m23*b.m30;
    result.m21 = a.m20*b.m01 + a.m21*b.m11 + a.m22*b.m21 + a.m23*b.m31;
    result.m22 = a.m20*b.m02 + a.m21*b.m12 + a.m22*b.m22 + a.m23*b.m32;
    result.m23 = a.m20*b.m03 + a.m21*b.m13 + a.m22*b.m23 + a.m23*b.m33;
    
    result.m30 = a.m30*b.m00 + a.m31*b.m10 + a.m32*b.m20 + a.m33*b.m30;
    result.m31 = a.m30*b.m01 + a.m31*b.m11 + a.m32*b.m21 + a.m33*b.m31;
    result.m32 = a.m30*b.m02 + a.m31*b.m12 + a.m32*b.m22 + a.m33*b.m32;
    result.m33 = a.m30*b.m03 + a.m31*b.m13 + a.m32*b.m23 + a.m33*b.m33;
    return result;
}

Mat4
mat4_transpose(Mat4 m) {
    Mat4 result = m;
    result.m01 = m.m10;
    result.m02 = m.m20;
    result.m03 = m.m30;
    
    result.m10 = m.m01;
    result.m12 = m.m21;
    result.m13 = m.m31;
    
    result.m20 = m.m02;
    result.m21 = m.m12;
    result.m23 = m.m32;
    
    result.m30 = m.m03;
    result.m31 = m.m13;
    result.m32 = m.m23;
    return result;
}
