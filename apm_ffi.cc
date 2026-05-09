#include "apm_pipeline.hh"
#include "g711_lite.h"
#include <cstdlib>
#include <vector>

using namespace telequick_core;

extern "C" {

__attribute__((visibility("default")))
void* telequick_apm_create(int sample_rate_hz, int num_channels) {
    auto* apm = new ApmPipeline(sample_rate_hz, num_channels);
    apm->enable_noise_suppression(webrtc::AudioProcessing::Config::NoiseSuppression::kHigh);
    apm->enable_auto_gain_control();
    apm->enable_voice_activity_detection();
    apm->enable_echo_cancellation();
    return apm;
}

__attribute__((visibility("default")))
void telequick_apm_destroy(void* apm_ptr) {
    delete static_cast<ApmPipeline*>(apm_ptr);
}

// Processes a chunk of audio, returning 1 if voice is detected, 0 otherwise.
__attribute__((visibility("default")))
int32_t telequick_apm_process_capture_ulaw(void* apm_ptr, uint8_t* buffer, size_t num_frames) {
    std::vector<int16_t> pcm_buf(num_frames);
    G711Lite::decode_ulaw_avx2(buffer, pcm_buf.data(), num_frames);
    return static_cast<ApmPipeline*>(apm_ptr)->process_capture_chunk(pcm_buf.data(), num_frames) ? 1 : 0;
}

__attribute__((visibility("default")))
int32_t telequick_apm_process_capture_alaw(void* apm_ptr, uint8_t* buffer, size_t num_frames) {
    std::vector<int16_t> pcm_buf(num_frames);
    G711Lite::decode_alaw_avx2(buffer, pcm_buf.data(), num_frames);
    return static_cast<ApmPipeline*>(apm_ptr)->process_capture_chunk(pcm_buf.data(), num_frames) ? 1 : 0;
}

__attribute__((visibility("default")))
void telequick_apm_process_render_ulaw(void* apm_ptr, uint8_t* buffer, size_t num_frames) {
    std::vector<int16_t> pcm_buf(num_frames);
    G711Lite::decode_ulaw_avx2(buffer, pcm_buf.data(), num_frames);
    static_cast<ApmPipeline*>(apm_ptr)->process_render_chunk(pcm_buf.data(), num_frames);
}

__attribute__((visibility("default")))
void telequick_apm_process_render_alaw(void* apm_ptr, uint8_t* buffer, size_t num_frames) {
    std::vector<int16_t> pcm_buf(num_frames);
    G711Lite::decode_alaw_avx2(buffer, pcm_buf.data(), num_frames);
    static_cast<ApmPipeline*>(apm_ptr)->process_render_chunk(pcm_buf.data(), num_frames);
}

} // extern "C"
