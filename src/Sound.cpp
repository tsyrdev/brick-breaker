#include "Sound.hpp"

Sound::Sound(std::string filepath) {
    if (SDL_LoadWAV(filepath.c_str(), &m_audioSpec, &m_waveStart, &m_waveLength) == nullptr)
        std::cout << "Sound Loading Error: " << SDL_GetError();
}
Sound::~Sound() {
    SDL_FreeWAV(m_waveStart); 
    SDL_CloseAudioDevice(m_device); 
}
void Sound::PlaySound() {
    int status = SDL_QueueAudio(m_device, m_waveStart, m_waveLength); 
    if (status < 0)
        std::cout << "Sound Queueing Error: " << SDL_GetError(); 
    SDL_PauseAudioDevice(m_device, 0); 
}
void Sound::StopSound() {
    SDL_PauseAudioDevice(m_device, 1);
}
void Sound::SetUpDevice() {
    m_device = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE); 
    if (m_device == 0) 
        std::cout << "Device Opening Error: " << SDL_GetError(); 
}
