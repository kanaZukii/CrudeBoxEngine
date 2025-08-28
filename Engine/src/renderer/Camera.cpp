#include "Camera.h"

Camera::Camera(){
    this->position.set(Vector2(0.0f, 0.0f));
    projectMat.setIdentity();
    projectionSize = Vector2(worldUnits * projectionWidth,
                            worldUnits * projectionHeight);
    adjustProjection();
}

void Camera::adjustProjection(){
    projectMat.ortho(0.0f, projectionSize.x * zoom, 0.0f, projectionSize.y * zoom, 0.0f, farZ);
    inverseProjection = projectMat;
    if(!inverseProjection.invert()){
        std::cerr << "Cannot invert projection matrix!";
    }
}

const Matrix4& Camera::getView() const{
    Vector3 cameraPos(position.x, position.y, 20.0f);
    Vector3 target(position.x, position.y, 0.0f);
    Vector3 up(0.0f, 1.0f, 0.0f);

    viewMat = Matrix4::lookAt(cameraPos, target, up);
    inverseView = viewMat;
    if(!inverseView.invert()){
        std::cerr << "Cannot invert view matrix!";
    }
    return viewMat;
}

void Camera::addZoom(float val){
    zoom += val;
}

void Camera::setZoom(float val){
    zoom = val;
}

void Camera::setPosition(const Vector2& position){
    this->position.set(position);
}

void Camera::addPosition(const Vector2& position){
    this->position += position;
}

float Camera::getZoom(){
    return zoom;
}

const Vector2& Camera::getPosition() const{
    return position;
}

const Matrix4& Camera::getProjection()const{
    return projectMat;
}
const Vector2& Camera::getProjectionSize()const{
    return projectionSize;
}
const Matrix4& Camera::getInverseProjection()const{
    return inverseProjection;
}
const Matrix4& Camera::getInverseView()const{
    return inverseView;
}