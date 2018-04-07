#pragma once
#include <string>
#include <iostream>

#include "..\..\ext\gorilla-audio\ga.h"
#include "..\..\ext\gorilla-audio\gau.h"
namespace clownfish {
	namespace audio
	{

		class AudioClip
		{
		private:
			ga_Sound* m_Sound;
			ga_Handle* m_Handle;
			float m_Volume;
			bool m_Playing;
			gc_int32 m_Position;


			std::string m_Name;
			std::string m_Filename;

		public:
			AudioClip(const std::string& name, const std::string& filename);
			~AudioClip();
			void play();
			void loop();
			void pause();
			void resume();
			void stop();

			void setVolume(float gain);
			inline const float getVolume()const { return m_Volume; }
			inline const bool isPlaying() const { return m_Playing; }

			inline const std::string& getName() const { return m_Name; }
			inline const std::string& getFilename() const { return m_Filename; }


			friend void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);
			friend void loopOnFinish(ga_Handle* in_handle, void* in_context);
		};

	}
}