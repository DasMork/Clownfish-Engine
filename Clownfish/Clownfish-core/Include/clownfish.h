#pragma once

#include "utils\timer.h"
#include "graphics\window.h"
#include "input\input.h"
#include "maths\maths.h"
#include "graphics\shader.h"
#include "graphics\buffers\buffer.h"
#include "graphics\buffers\indexbuffer.h"
#include "graphics\buffers/vertextarray.h"

#include "graphics\Renderable2D.h"
#include "graphics\simple2drenderer.h"
#include "graphics\BatchRenderer2D.h"

#include "graphics\sprite.h"
#include "graphics\static_sprite.h"
#include "graphics\layers\group.h"
#include "graphics\layers\layer.h"
#include "graphics\texture.h"
#include "graphics\label.h"

#include "graphics\fontmanager.h"
#include "audio\audiomanager.h"

namespace clownfish
{
	 class Clownfish
	{

	private:
		graphics::Window* m_Window;
		Timer* m_Timer;
		int m_FramesperSecond, m_UpdatesPerSecond;

	public:


		virtual void start()
		{
			init();
			run();
		}

	protected:
		Clownfish()
			: m_FramesperSecond(0), m_UpdatesPerSecond(0)
		{

		}
		virtual ~Clownfish()
		{
			delete m_Timer;
			delete m_Window;
		}
		graphics::Window* CFcreateWindow(const char* name, int width, int height, bool fullscreen = false)
		{
			m_Window = new graphics::Window(name, width, height, fullscreen);
			return m_Window;
		}


		//Runs once upon initialization
		virtual void init() = 0;

		//Runs once per second
		virtual void tick() {}

		//Runs 60 times per second
		virtual void update()  {}

		//Runs as fast as possible
		virtual void render() = 0;


		const unsigned int getFPS() const { return m_FramesperSecond; }
		const unsigned int getUPS() const { return m_UpdatesPerSecond; }
	private:
		void run()
		{
			m_Timer = new Timer();
			float timer = 0;
			float updateTimer = 0;
			float updateTick = 1.0f/60.0f;
			unsigned int frames = 0;
			unsigned int updates = 0;

			

			while (!m_Window->closed())
			{
				m_Window->clear();
				if (m_Timer->elapsed() - updateTimer > updateTick)
				{
					updates++;
					update();
					updateTimer += updateTick;
				}

				frames++;
				render();
				m_Window->update();
				if (m_Timer->elapsed() - timer > 1.0f)
				{
					m_FramesperSecond = frames;
					m_UpdatesPerSecond = updates;
					timer += 1.0f;
					frames = 0;
					updates = 0;
					tick();
				}
			}
		}
	};

}