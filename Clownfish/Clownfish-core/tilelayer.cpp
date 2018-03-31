#include "tilelayer.h"
#include "..\..\Clownfish\Clownfish-core\src\graphics\BatchRenderer2D.h"

namespace clownfish {
	namespace graphics {


		TileLayer::TileLayer(Shader* shader)
			: Layer(new BatchRenderer2D(), shader, maths::mat4::othographic(-16, 16, -9, 9, -1,1))
		{

		}

		TileLayer::~TileLayer()
		{

		}
	}
}