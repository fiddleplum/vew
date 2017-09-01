#include "viewport.hpp"
#include <limits>

namespace vew
{
	Viewport::Viewport()
	{
		fieldOfView = M_PI / 3.0;
		aspectRatio = 1;
		bounds = Rectd({0, 0}, {1, 1});
		nearDistance = 1;
		canvasSize = {1, 1};
		projection = Matrix44f::zero();
		projection(3, 1) = 1;
		updateProjection();
	}

	double Viewport::getFieldOfView() const
	{
		return fieldOfView;
	}

	double Viewport::getVerticalFieldOfView() const
	{
		if (aspectRatio >= 1)
		{
			return 2 * atan2(tan(fieldOfView / 2), aspectRatio);
		}
		else
		{
			return fieldOfView;
		}
	}

	void Viewport::setFieldOfView(double fieldOfView)
	{
		this->fieldOfView = fieldOfView;
		updateProjection();
	}

	void Viewport::setBounds(Rectd bounds)
	{
		this->bounds = bounds;
		updateProjection();
	}

	double Viewport::getNearDistance() const
	{
		return nearDistance;
	}

	void Viewport::setNearDistance(double nearDistance)
	{
		this->nearDistance = nearDistance;
		updateProjection();
	}

	Rectd Viewport::getPixelBounds() const
	{
		return Rectd(bounds.min.scale(canvasSize), bounds.max.scale(canvasSize));
	}

	Vector3d Viewport::canvasSpaceToViewSpace(Vector2d position) const
	{
		Rectd pixelBounds = getPixelBounds();
		Vector3d positionInNormalSpace = {
			2.0 * (position[0] - pixelBounds.min[0]) / (pixelBounds.max[0] - pixelBounds.min[0]) - 1.0,
			1.0 - 2.0 * (position[1] - pixelBounds.min[1]) / (pixelBounds.max[1] - pixelBounds.min[1]),
			-1};
		return Vector3d::zero();
		// TODO
	}

	Vector2d Viewport::viewSpaceToCanvasSpace(Vector3d position) const
	{
		// TODO
		return Vector2d::zero();
	}

	Matrix44f Viewport::getProjection() const
	{
		return projection;
	}

	void Viewport::setCanvasSize(Vector2d size)
	{
		canvasSize = size;
		updateProjection();
	}

	void Viewport::updateProjection()
	{
		double epsilon = std::numeric_limits<double>::epsilon();
		Vector2d pixelSize = bounds.getSize().scale(canvasSize);
		if (0 < fieldOfView && fieldOfView < M_PI && pixelSize[0] > 0 && pixelSize[1] > 0)
		{
			aspectRatio = pixelSize[0] / pixelSize[1];
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

/*

The infinity matrix (y becomes -z, z becomes y):

Sx 0   0  0
0  0   Sz 0
0  1-δ 0  -n(2-δ) 
0  1   0  0

*/