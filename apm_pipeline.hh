#pragma once

#include <memory>
#include <vector>
#include <cstdint>
#include "modules/audio_processing/include/audio_processing.h"

namespace telequick_core {

class ApmPipeline {
public:
    ApmPipeline(int sample_rate_hz = 16000, int num_channels = 1);
    ~ApmPipeline();

    void enable_noise_suppression(webrtc::AudioProcessing::Config::NoiseSuppression::Level level);
    void enable_echo_cancellation();
    void enable_voice_activity_detection();
    void enable_auto_gain_control();

    // Processes a 10ms chunk of 16-bit PCM audio. Typical chunk size is 160 samples for 16kHz audio.
    // Returns true if voice activity was detected (if VAD is enabled), and modifies the buffer in-place (NS/AEC).
    bool process_capture_chunk(int16_t* audio_frame, size_t num_frames);

    // Processes remote audio for Acoustic Echo Cancellation reference.
    void process_render_chunk(int16_t* audio_frame, size_t num_frames);

private:
    std::unique_ptr<webrtc::AudioProcessing> apm_;
    int sample_rate_hz_;
    int num_channels_;
    webrtc::AudioProcessing::Config config_;
};

} // namespace telequick_core
