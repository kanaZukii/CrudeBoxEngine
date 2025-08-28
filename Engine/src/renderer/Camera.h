#pragma once

#include <iostream>

#include "Math.h"

class Camera {
    public:
        Camera();
        void addZoom(float val);
        void setZoom(float val);
        void setPosition(const Vector2& position);
        void addPosition(const Vector2& position);
        void adjustProjection();
        float getZoom();
        const Vector2& getPosition()const;
        const Matrix4& getView() const;
        const Matrix4& getProjection() const;
        const Vector2& getProjectionSize() const;
        const Matrix4& getInverseProjection() const;
        const Matrix4& getInverseView() const;

    private:
        float zoom = 1.0f;
        float worldUnits = 4.0f;
        float projectionWidth = 160.0f;
        float projectionHeight = 90.0f;
        float farZ = 100.0f;
        Vector2 projectionSize;
        Vector2 position;
        mutable Matrix4 projectMat, viewMat, inverseProjection, inverseView;
};
