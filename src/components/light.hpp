#include <components/component.hpp>
#include <math/vector.hpp>

namespace vew
{
	class Light : public Component
	{
	public:
		Vector3d getColor() const;

		void setColor(Vector3d color);

	private:
		Vector3d color;
	};
}