#include "audiomanager.h"

namespace clownfish{namespace audio
{
	gau_Manager* AudioManager::m_Manager = nullptr;
	ga_Mixer* AudioManager::m_Mixer = nullptr;

	std::vector<AudioClip*> AudioManager::m_AudioClips;

	void AudioManager::init()
	{
		gc_initialize(0);
		m_Manager = gau_manager_create();
		m_Mixer = gau_manager_mixer(m_Manager);
	}
	void AudioManager::add(AudioClip* clip)
	{
		m_AudioClips.push_back(clip);
	}
	AudioClip* AudioManager::get(const std::string& name)
	{
		for (AudioClip* clip : m_AudioClips)
		{
			if (clip->getName() == name)
				return clip;
		}
		return nullptr;
	}

	void AudioManager::update()
	{
		gau_manager_update(AudioManager::m_Manager);
	}
	void AudioManager::clean()
	{
		for (int i = 0; i < m_AudioClips.size(); i++)
		{
			delete m_AudioClips[i];
		}

		gau_manager_destroy(m_Manager);
		gc_shutdown();
	}
} }