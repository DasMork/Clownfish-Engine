#pragma once
#include "Renderable3D.h"
#include <GL\glew.h>
#include "..\maths\maths.h"

namespace clownfish {
	namespace graphics
	{

		class Renderer3D
		{
		public:
			virtual void begin() {}
			virtual void end() {}

			virtual void submit(const Renderable3D* renderable) = 0;
			virtual void flush() = 0;

		};



	}
}