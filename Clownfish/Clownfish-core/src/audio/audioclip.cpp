#include "audioclip.h"
#include "audiomanager.h"
#include "..\utils\stringutils.h"


namespace clownfish {
	namespace audio
	{
		static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context);
		static void loopOnFinish(ga_Handle* in_handle, void* in_context);

		AudioClip::AudioClip(const std::string& name, const std::string& filename)
			:m_Name(name), m_Filename(filename)
		{
			std::vector<std::string> split = split_string(m_Filename, '.');
			
			m_Sound = gau_load_sound_file(m_Filename.c_str(), split.back().c_str());
			m_Playing = false;

			if (m_Sound == nullptr)
				std::cout << "[AUDIO] Could not load file!" << m_Filename << std::endl;
				
			
		}
		AudioClip::~AudioClip()
		{
			ga_sound_release(m_Sound);
		}

		void AudioClip::play()
		{
			if (m_Sound == nullptr)
				return;

			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(AudioManager::m_Mixer, m_Sound, &setFlagAndDestroyOnFinish, &quit, NULL);
			m_Handle->clip = this;
			ga_handle_play(m_Handle);
			m_Playing = true;
		}
		void AudioClip::loop()
		{
			if (m_Playing || m_Sound == nullptr)
				return;

			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(AudioManager::m_Mixer, m_Sound, &loopOnFinish, &quit, NULL);
			m_Handle->clip = this;
			ga_handle_play(m_Handle);
			m_Playing = true;


		}
		void AudioClip::pause()
		{
			if (!m_Playing)
				return;

			m_Playing = false;
			ga_handle_stop(m_Handle);
		}
		void AudioClip::resume()
		{
			if (m_Handle == nullptr)
				return;

			m_Playing = true;
			ga_handle_play(m_Handle);
		}
		void AudioClip::stop()
		{
			if (!m_Playing)
				return;

			ga_handle_stop(m_Handle);
			ga_handle_destroy(m_Handle);
			m_Playing = false;

		}

		void AudioClip::setVolume(float volume)
		{
			if (!m_Playing)
			{
				std::cout << "[AUDIO] Cannot set volume if the sound isn't playing!" << std::endl;
			}
			else
			{
			m_Volume = volume;
			ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, volume);
			}

		}



		void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
		{
			AudioClip*clip = (AudioClip*)in_handle->clip;
			clip->stop();
		}
		void loopOnFinish(ga_Handle* in_handle, void* in_context)
		{
			AudioClip*clip = (AudioClip*)in_handle->clip;
			clip->m_Playing = false;
			clip->loop();
			ga_handle_destroy(in_handle);
		}
	}
}