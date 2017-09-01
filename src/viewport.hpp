#pragma once

#include "rect.hpp"
#include "matrix.hpp"

namespace vew
{
	// A viewport that encapsulates a rendering bounds and camera parameters.
	// Canvas space is in pixels, top left is origin, +x is right, +y is down (screen space).
	// View space is in world relative to the viewer, origin is at viewer position within world, +x is right, +y is forward, +z is up (world space relative to camera).
	class Viewport
	{
	public:
		Viewport();

		// Returns the fieldOfView in radians.
		double getFieldOfView() const;

		// Returns the vertical fieldOfView in radians.
		double getVerticalFieldOfView() const;

		// Sets the fieldOfView in radians.
		void setFieldOfView(double fieldOfView);

		// Sets the bounds in canvas space but as a fraction of the total screen.
		void setBounds(Rectd bounds);

		// Returns the near distance.
		double getNearDistance() const;

		// Sets the near distance.
		void setNearDistance(double nearDistance);

		// Returns the bounds in pixels.
		Rectd getPixelBounds() const;

		// Returns a normalized position in view space from a position in screen space.
		Vector3d canvasSpaceToViewSpace(Vector2d position) const;

		// Returns a position in screen space from a position in view space.
		Vector2d viewSpaceToCanvasSpace(Vector3d position) const;

		// Returns the projection as a float for GL.
		Matrix44f getProjection() const;

		// Internal to vew. Sets the size of the canvas.
		void setCanvasSize(Vector2d size);

	private:
		void updateProjection();

		double fieldOfView;
		Rectd bounds;
		double nearDistance;
		Vector2d canvasSize;
		double aspectRatio;
		Matrix44f projection;
	};
}