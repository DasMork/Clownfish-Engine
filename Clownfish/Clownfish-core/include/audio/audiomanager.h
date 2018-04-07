#pragma once
#include "audioclip.h"
#include <vector>

#include "..\..\ext\gorilla-audio\ga.h"
#include "..\..\ext\gorilla-audio\gau.h"


namespace clownfish {
	namespace audio
	{

		class AudioManager
		{

			friend class AudioClip;

		private:
			static gau_Manager* m_Manager;
			static ga_Mixer* m_Mixer;

			static std::vector<AudioClip*> m_AudioClips;

		public:
			static void init();
			static void add(AudioClip* clip);
			static AudioClip* get(const std::string& name);

			static void update();
			static void clean();
		private:
			AudioManager(){}
		};



	}
}