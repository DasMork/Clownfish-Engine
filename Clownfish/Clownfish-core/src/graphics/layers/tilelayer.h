#pragma once

#include "layer.h"



namespace clownfish {
	namespace graphics {

		class TileLayer : public Layer
		{

		public:
			TileLayer(Shader* shader);
			~TileLayer();

		};

	}
}