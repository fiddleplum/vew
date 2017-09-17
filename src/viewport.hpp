#pragma once

#include "rect.hpp"

namespace vew
{
	class Camera;

	// A viewport that encapsulates a rendering bounds and takes a camera.
	// Canvas space is in pixels, top left is origin, +x is right, +y is down (screen space).
	// View space is in world relative to the viewer, origin is at viewer position within world, +x is right, +y is forward, +z is up (world space relative to camera).
	class Viewport
	{
	public:
		Viewport();

		// Gets the currently used camera.
		Camera * getCamera();

		// Sets the currently used camera.
		void setCamera(Camera * camera);

		// Sets the bounds in canvas space but as a fraction of the total screen.
		void setBounds(Rectd bounds);

		// Returns the bounds in pixels.
		Rectd getPixelBounds() const;

		// Returns a normalized position in view space from a position in screen space.
		Vector3d canvasSpaceToViewSpace(Vector2d position) const;

		// Returns a position in screen space from a position in view space.
		Vector2d viewSpaceToCanvasSpace(Vector3d position) const;

		// Internal to vew. Sets the size of the canvas.
		void setCanvasSize(Vector2d size);

		// Internal to vew. Renders the viewport.
		void render();

	private:
		void updateCameraAspectRatio();

		Camera * camera;
		Rectd bounds;
		Vector2d canvasSize;
	};
}