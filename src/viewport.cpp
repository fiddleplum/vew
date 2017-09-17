#include "viewport.hpp"
#include "camera.hpp"
#include <emscripten/bind.h>
#include <emscripten/emscripten.h>
#include <GLES2/gl2.h>

namespace vew
{
	Viewport::Viewport()
	{
		camera = nullptr;
		bounds = Rectd({0, 0}, {1, 1});
		canvasSize = {1, 1};
	}

	Camera* Viewport::getCamera()
	{
		return camera;
	}

	// Sets the currently used camera.
	void Viewport::setCamera(Camera* camera)
	{
		this->camera = camera;
		updateCameraAspectRatio();
	}

	void Viewport::setBounds(Rectd bounds)
	{
		this->bounds = bounds;
		updateCameraAspectRatio();
	}

	Rectd Viewport::getPixelBounds() const
	{
		return Rectd(bounds.min.scale(canvasSize), bounds.max.scale(canvasSize));
	}

	Vector3d Viewport::canvasSpaceToViewSpace(Vector2d position) const
	{
		Rectd pixelBounds = getPixelBounds();
		Vector3d positionInNormalSpace = {2.0 * (position[0] - pixelBounds.min[0]) / (pixelBounds.max[0] - pixelBounds.min[0]) - 1.0, 1.0 - 2.0 * (position[1] - pixelBounds.min[1]) / (pixelBounds.max[1] - pixelBounds.min[1]), -1};
		return Vector3d::zero();
		// TODO
	}

	Vector2d Viewport::viewSpaceToCanvasSpace(Vector3d position) const
	{
		// TODO
		return Vector2d::zero();
	}

	void Viewport::setCanvasSize(Vector2d size)
	{
		canvasSize = size;
		updateCameraAspectRatio();
	}

	void Viewport::render()
	{
		if(camera != nullptr)
		{
			Vector2d boundsSize = bounds.getSize();
			glViewport(canvasSize[0] * bounds.min[0], canvasSize[1] * bounds.min[1], canvasSize[0] * boundsSize[0], canvasSize[1] * boundsSize[1]);
		}
	}
	
	void Viewport::updateCameraAspectRatio()
	{
		if(camera != nullptr)
		{
			Rectd pixelBounds = getPixelBounds();
			camera->setAspectRatio((double)(pixelBounds.max[0] - pixelBounds.min[0]) / (pixelBounds.max[1] - pixelBounds.min[1]));
		}
	}
}

// Binding Code
EMSCRIPTEN_BINDINGS(vew_Viewport)
{
	emscripten::class_<vew::Viewport>("Viewport")
	.constructor<>()
	.function("getCamera", &vew::Viewport::getCamera, emscripten::allow_raw_pointers())
	.function("setCamera", &vew::Viewport::setCamera, emscripten::allow_raw_pointers())
	.function("setBounds", &vew::Viewport::setBounds)
	.function("getPixelBounds", &vew::Viewport::getPixelBounds)
	.function("canvasSpaceToViewSpace", &vew::Viewport::canvasSpaceToViewSpace)
	.function("viewSpaceToCanvasSpace", &vew::Viewport::viewSpaceToCanvasSpace);
}