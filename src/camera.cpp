#include "camera.hpp"
#include "entity.hpp"
#include <emscripten/bind.h>
#include <limits>

namespace vew
{
	ComponentRegister<Camera> cameraRegister("camera");

	Camera::Camera()
	{
		fieldOfView = M_PI / 3.0;
		aspectRatio = 1;
		nearDistance = 1;
		projection = Matrix44f::zero();
		projection(3, 1) = 1;
		updateProjection();
	}

	double Camera::getFieldOfView() const
	{
		return fieldOfView;
	}

	Vector2d Camera::getFieldOfViewXY() const
	{
		if (aspectRatio >= 1)
		{
			return Vector2d{fieldOfView, 2 * atan2(tan(fieldOfView / 2), aspectRatio)};
		}
		else
		{
			return Vector2d{2 * atan2(tan(fieldOfView / 2), 1.0 / aspectRatio), fieldOfView};
		}
	}

	void Camera::setFieldOfView(double fieldOfView)
	{
		this->fieldOfView = fieldOfView;
		updateProjection();
	}

	double Camera::getNearDistance() const
	{
		return nearDistance;
	}

	void Camera::setNearDistance(double nearDistance)
	{
		this->nearDistance = nearDistance;
		updateProjection();
	}

	void Camera::setAspectRatio(double aspectRatio)
	{
		this->aspectRatio = aspectRatio;
		updateProjection();
	}

	Matrix44f Camera::getProjection() const
	{
		return projection;
	}

	void Camera::updateProjection()
	{
		double epsilon = std::numeric_limits<double>::epsilon();
		if (0 < fieldOfView && fieldOfView < M_PI && aspectRatio != 0)
		{
			double invTanHalfFieldOfView = 1 / tan(fieldOfView / 2);
			if (aspectRatio >= 1)
			{
				projection(0, 0) = (float)invTanHalfFieldOfView;
				projection(1, 2) = (float)(invTanHalfFieldOfView * aspectRatio);
			}
			else
			{
				projection(0, 0) = (float)(invTanHalfFieldOfView / aspectRatio);
				projection(1, 2) = (float)invTanHalfFieldOfView;
			}
			projection(2, 1) = (float)(1.0 - epsilon);
			projection(2, 3) = (float)(nearDistance * (epsilon - 2.0));
		}
	}
}

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Camera)
{
	emscripten::class_<vew::Camera, emscripten::base<vew::Component>>("Camera")
		.constructor<>()
		.function("getFieldOfView", &vew::Camera::getFieldOfView)
		.function("getFieldOfViewXY", &vew::Camera::getFieldOfViewXY)
		.function("setFieldOfView", &vew::Camera::setFieldOfView)
		.function("getNearDistance", &vew::Camera::getNearDistance)
		.function("setNearDistance", &vew::Camera::setNearDistance);
}

/*

The infinity matrix (y becomes -z, z becomes y):

Sx 0   0  0
0  0   Sz 0
0  1-δ 0  -n(2-δ)
0  1   0  0

*/