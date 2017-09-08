#pragma once

#include "matrix.hpp"
#include "component.hpp"

namespace vew
{
	class Camera : public Component
	{
	public:
		// Constructor.
		Camera();

		// Returns the field of view in radians.
		double getFieldOfView() const;

		// Returns the horizontal and vertical fields of view in radians.
		Vector2d getFieldOfViewXY() const;

		// Sets the field of view in radians.
		void setFieldOfView(double fieldOfView);

		// Returns the near distance.
		double getNearDistance() const;

		// Sets the near distance.
		void setNearDistance(double nearDistance);

		// Internal. Sets the aspect ratio.
		void setAspectRatio(double aspectRatio);

		// Internal. Returns the projection as a float matrix for GL.
		Matrix44f getProjection() const;

	private:
		void updateProjection();

		double fieldOfView;
		double nearDistance;
		double aspectRatio;
		Matrix44f projection;
	};
}