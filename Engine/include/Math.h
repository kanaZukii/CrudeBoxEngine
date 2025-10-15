#pragma once
#include <cmath>
#include <algorithm> 

#define PI 3.14159265358979323846f

struct Vector2
{
    float x, y;

    Vector2() : x(0), y(0) {}

    Vector2(float x, float y) : x(x), y(y) {}

    void set(const Vector2& b){
        x = b.x;
        y = b.y;
    }

    Vector2 operator+(const Vector2& b) const{
        return Vector2(x + b.x, y + b.y);
    }

    Vector2 operator-(const Vector2& b) const{
        return Vector2(x - b.x, y - b.y);
    }

    Vector2 operator*(float scale) const{
        return Vector2(x * scale, y * scale);
    }

    Vector2 operator/(float scale) const{
        return Vector2(x / scale, y / scale);
    }

    Vector2& operator+=(const Vector2& b) {
        x += b.x; y += b.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& b) {
        x -= b.x; y -= b.y;
        return *this;
    }

    bool operator==(const Vector2& b) {
        const float eps = 1e-6f;
        return std::fabs(x - b.x) < eps &&
            std::fabs(y - b.y) < eps;
    }

    float length() const {
        return std::sqrt((x*x) + (y*y));
    }

    float dot(const Vector2& b) const{
        return x * b.x + y * b.y;
    }

    void mulComponent(const Vector2& b){
        x *= b.x;
        y *= b.y;
    }

    void divSComponent(const Vector2& b){
        x /= b.x;
        y /= b.y;
    }

    void normalize(){
        float len = length();
        if(len != 0){
            x /= len;
            y /= len;
        }
    }
};

struct Vector3
{
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}

    Vector3(float x, float y, float z) : x(x), y(y),  z(z) {}

    void set(const Vector3& b){
        x = b.x;
        y = b.y;
        z = b.z;
    }

    Vector3 operator+(const Vector3& b) const{
        return Vector3(x + b.x, y + b.y, z + b.z);
    }

    Vector3 operator-(const Vector3& b) const{
        return Vector3(x - b.x, y - b.y, z - b.z);
    }

    Vector3 operator*(float scale) const{
        return Vector3(x * scale, y * scale, z * scale);
    }

    Vector3 operator/(float scale) const{
        return Vector3(x / scale, y / scale, z / scale);
    }

    Vector3& operator+=(const Vector3& b) {
        x += b.x; y += b.y; z += b.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& b) {
        x -= b.x; y -= b.y; z -= b.z;
        return *this;
    }

    bool operator==(const Vector3& b) {
        const float eps = 1e-6f;
        return std::fabs(x - b.x) < eps &&
            std::fabs(y - b.y) < eps &&
            std::fabs(z - b.z) < eps;
    }

    float length() const{
        return std::sqrt((x*x) + (y*y) + (z*z));
    }

    static float dot(const Vector3& a, const Vector3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    void mulComponent(const Vector3& b){
        x *= b.x;
        y *= b.y;
        z *= b.z;
    }

    void divComponent(const Vector3& b){
        x /= b.x;
        y /= b.y;
        z /= b.z;
    }

    void normalize(){
        float len = length();
        if(len != 0){
            x /= len;
            y /= len;
            z /= len;
        }
    }

    static Vector3 cross(const Vector3& a, const Vector3& b) {
        return Vector3{
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }
};

struct Vector4
{
    float x,y,z,w;

    Vector4() : x(0), y(0), z(0), w(0) {}
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    void set(const Vector3& b){
        x = b.x;
        y = b.y;
        z = b.z;
    }

    Vector4 operator+(const Vector4& b) const{
        return Vector4(x + b.x, y + b.y, z + b.z, w + b.w);
    }

    Vector4 operator-(const Vector4& b) const{
        return Vector4(x - b.x, y - b.y, z - b.z, w - b.w);
    }

    Vector4 operator*(float scale) const{
        return Vector4(x * scale, y * scale, z * scale, w * scale);
    }

    Vector4 operator/(float scale) const{
        return Vector4(x / scale, y / scale, z / scale, w / scale);
    }

    Vector4& operator+=(const Vector4& b) {
        x += b.x; y += b.y; z += b.z; w += b.w;
        return *this;
    }

    Vector4& operator-=(const Vector4& b) {
        x -= b.x; y -= b.y; z -= b.z; w -= b.w;
        return *this;
    }

    bool operator==(const Vector4& b) {
        const float eps = 1e-6f;
        return std::fabs(x - b.x) < eps &&
            std::fabs(y - b.y) < eps &&
            std::fabs(z - b.z) < eps &&
            std::fabs(w - b.w) < eps;
    }

    float length() const{
        return std::sqrt((x*x) + (y*y) + (z*z) + (w*w));
    }

    float dot(const Vector4& b) const{
        return x * b.x + y * b.y + z * b.z + w * b.w;
    }

    void mulComponent(const Vector4& b){
        x *= b.x;
        y *= b.y;
        z *= b.z;
        w *= b.w;
    }

    void divComponent(const Vector4& b){
        x /= b.x;
        y /= b.y;
        z /= b.z;
        w /= b.w;
    }

    void normalize(){
        float len = length();
        if(len != 0){
            x /= len;
            y /= len;
            z /= len;
            w /= len;
        }
    }

    static Vector4 cross(const Vector4& a, const Vector4& b) {
        return Vector4{
             a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x,
            0.0f
        };
    }
};

struct Matrix3
{
    float m[9];

    Matrix3() {
        std::fill(m, m + 9, 0.0f);
    }

    Matrix3(const float arr[9]) {
        std::copy(arr, arr + 9, m);
    }

    void setIdentity() {
        std::fill(m, m + 9, 0.0f);
        m[0]  = 1.0f;
        m[4]  = 1.0f;
        m[8] = 1.0f;
    }

    static Matrix3 identity() {
        Matrix3 mat;
        mat.setIdentity();
        return mat;
    }

    bool invert() {
        float det = m[0]*(m[4]*m[8]-m[5]*m[7]) -
                    m[1]*(m[3]*m[8]-m[5]*m[6]) +
                    m[2]*(m[3]*m[7]-m[4]*m[6]);

        if(det == 0.0f) return false;

        float invDet = 1.0f / det;

        float inv[9];
        inv[0] =  (m[4]*m[8] - m[5]*m[7]) * invDet;
        inv[1] = -(m[1]*m[8] - m[2]*m[7]) * invDet;
        inv[2] =  (m[1]*m[5] - m[2]*m[4]) * invDet;
        inv[3] = -(m[3]*m[8] - m[5]*m[6]) * invDet;
        inv[4] =  (m[0]*m[8] - m[2]*m[6]) * invDet;
        inv[5] = -(m[0]*m[5] - m[2]*m[3]) * invDet;
        inv[6] =  (m[3]*m[7] - m[4]*m[6]) * invDet;
        inv[7] = -(m[0]*m[7] - m[1]*m[6]) * invDet;
        inv[8] =  (m[0]*m[4] - m[1]*m[3]) * invDet;

        std::copy(inv, inv + 9, m);
        return true;
    }

    
    static Matrix3 lookAt(const Vector2& from, const Vector2& to) {
        Vector2 dir = to - from; dir.normalize();
        Matrix3 mat;
        mat.setIdentity();
        mat.m[0] = dir.x; mat.m[3] = -dir.y;
        mat.m[1] = dir.y; mat.m[4] = dir.x;
        return mat;
    }
};

struct Matrix4
{
    float m[16];

    Matrix4() {
        std::fill(m, m + 16, 0.0f);
    }

    Matrix4(const float arr[16]) {
        std::copy(arr, arr + 16, m);
    }

    void setIdentity() {
        std::fill(m, m + 16, 0.0f);
        m[0]  = 1.0f;
        m[5]  = 1.0f;
        m[10] = 1.0f;
        m[15] = 1.0f;
    }

    static Matrix4 identity() {
        Matrix4 mat;
        mat.setIdentity();
        return mat;
    }

     // Orthographic projection
    void ortho(float left, float right, float bottom, float top, float near, float far) {
        setIdentity();
        m[0] = 2.0f / (right - left);
        m[5] = 2.0f / (top - bottom);
        m[10] = -2.0f / (far - near);
        m[12] = -(right + left) / (right - left);
        m[13] = -(top + bottom) / (top - bottom);
        m[14] = -(far + near) / (far - near);
    }

    bool invert() {
        float inv[16], det;
        const float* a = m;

        inv[0] = a[5]  * a[10] * a[15] - 
                 a[5]  * a[11] * a[14] - 
                 a[9]  * a[6]  * a[15] + 
                 a[9]  * a[7]  * a[14] +
                 a[13] * a[6]  * a[11] - 
                 a[13] * a[7]  * a[10];

        inv[4] = -a[4]  * a[10] * a[15] + 
                  a[4]  * a[11] * a[14] + 
                  a[8]  * a[6]  * a[15] - 
                  a[8]  * a[7]  * a[14] - 
                  a[12] * a[6]  * a[11] + 
                  a[12] * a[7]  * a[10];

        inv[8] = a[4]  * a[9] * a[15] - 
                 a[4]  * a[11] * a[13] - 
                 a[8]  * a[5] * a[15] + 
                 a[8]  * a[7] * a[13] + 
                 a[12] * a[5] * a[11] - 
                 a[12] * a[7] * a[9];

        inv[12] = -a[4]  * a[9] * a[14] + 
                   a[4]  * a[10] * a[13] +
                   a[8]  * a[5] * a[14] - 
                   a[8]  * a[6] * a[13] - 
                   a[12] * a[5] * a[10] + 
                   a[12] * a[6] * a[9];

        inv[1] = -a[1]  * a[10] * a[15] + 
                  a[1]  * a[11] * a[14] + 
                  a[9]  * a[2] * a[15] - 
                  a[9]  * a[3] * a[14] - 
                  a[13] * a[2] * a[11] + 
                  a[13] * a[3] * a[10];

        inv[5] = a[0]  * a[10] * a[15] - 
                 a[0]  * a[11] * a[14] - 
                 a[8]  * a[2] * a[15] + 
                 a[8]  * a[3] * a[14] + 
                 a[12] * a[2] * a[11] - 
                 a[12] * a[3] * a[10];

        inv[9] = -a[0]  * a[9] * a[15] + 
                  a[0]  * a[11] * a[13] + 
                  a[8]  * a[1] * a[15] - 
                  a[8]  * a[3] * a[13] - 
                  a[12] * a[1] * a[11] + 
                  a[12] * a[3] * a[9];

        inv[13] = a[0]  * a[9] * a[14] - 
                  a[0]  * a[10] * a[13] - 
                  a[8]  * a[1] * a[14] + 
                  a[8]  * a[2] * a[13] + 
                  a[12] * a[1] * a[10] - 
                  a[12] * a[2] * a[9];

        inv[2] = a[1]  * a[6] * a[15] - 
                 a[1]  * a[7] * a[14] - 
                 a[5]  * a[2] * a[15] + 
                 a[5]  * a[3] * a[14] + 
                 a[13] * a[2] * a[7] - 
                 a[13] * a[3] * a[6];

        inv[6] = -a[0]  * a[6] * a[15] + 
                  a[0]  * a[7] * a[14] + 
                  a[4]  * a[2] * a[15] - 
                  a[4]  * a[3] * a[14] - 
                  a[12] * a[2] * a[7] + 
                  a[12] * a[3] * a[6];

        inv[10] = a[0]  * a[5] * a[15] - 
                  a[0]  * a[7] * a[13] - 
                  a[4]  * a[1] * a[15] + 
                  a[4]  * a[3] * a[13] + 
                  a[12] * a[1] * a[7] - 
                  a[12] * a[3] * a[5];

        inv[14] = -a[0]  * a[5] * a[14] + 
                   a[0]  * a[6] * a[13] + 
                   a[4]  * a[1] * a[14] - 
                   a[4]  * a[2] * a[13] - 
                   a[12] * a[1] * a[6] + 
                   a[12] * a[2] * a[5];

        inv[3] = -a[1] * a[6] * a[11] + 
                  a[1] * a[7] * a[10] + 
                  a[5] * a[2] * a[11] - 
                  a[5] * a[3] * a[10] - 
                  a[9] * a[2] * a[7] + 
                  a[9] * a[3] * a[6];

        inv[7] = a[0] * a[6] * a[11] - 
                 a[0] * a[7] * a[10] - 
                 a[4] * a[2] * a[11] + 
                 a[4] * a[3] * a[10] + 
                 a[8] * a[2] * a[7] - 
                 a[8] * a[3] * a[6];

        inv[11] = -a[0] * a[5] * a[11] + 
                   a[0] * a[7] * a[9] + 
                   a[4] * a[1] * a[11] - 
                   a[4] * a[3] * a[9] - 
                   a[8] * a[1] * a[7] + 
                   a[8] * a[3] * a[5];

        inv[15] = a[0] * a[5] * a[10] - 
                  a[0] * a[6] * a[9] - 
                  a[4] * a[1] * a[10] + 
                  a[4] * a[2] * a[9] + 
                  a[8] * a[1] * a[6] - 
                  a[8] * a[2] * a[5];

        det = a[0] * inv[0] + a[1] * inv[4] + a[2] * inv[8] + a[3] * inv[12];
        if(det == 0.0f) return false;

        det = 1.0f / det;
        for(int i = 0; i < 16; i++) m[i] = inv[i] * det;

        return true;
    }

    static Matrix4 lookAt(const Vector3& eye, const Vector3& target, const Vector3& up) {
        Vector3 f = target - eye; f.normalize();// forward
        Vector3 r = Vector3::cross(f, up); r.normalize(); // right
        Vector3 u = Vector3::cross(r, f);           // up

        Matrix4 mat;
        mat.setIdentity();

        mat.m[0] = r.x; mat.m[4] = r.y; mat.m[8]  = r.z;  mat.m[12] = -Vector3::dot(r, eye);
        mat.m[1] = u.x; mat.m[5] = u.y; mat.m[9]  = u.z;  mat.m[13] = -Vector3::dot(u, eye);
        mat.m[2] = -f.x; mat.m[6] = -f.y; mat.m[10] = -f.z; mat.m[14] = Vector3::dot(f, eye);

        return mat;
    }

    // Matrix4& operator=(const Matrix4& matB){
    //     std::copy(matB.m, matB.m + 16, m);
    //     return *this;
    // }
};

inline float degToRadians(float angleDeg){
    return angleDeg * (M_PI / 180.0f);
}

inline void rotateVec2(Vector2& vec2, float angle, const Vector2& center){
    float x = vec2.x - center.x;
    float y = vec2.y - center.y;

    float radians = degToRadians(angle);
    float sin = std::sin(radians);
    float cos = std::cos(radians);

    float xPrime = (x * cos) - (y * sin);
    float yPrime = (x * sin) + (y * cos);

    xPrime += center.x;
    yPrime += center.y;

    vec2.x = xPrime;
    vec2.y = yPrime;
}