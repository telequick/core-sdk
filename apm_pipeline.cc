#include "apm_pipeline.hh"
#include <iostream>

using namespace telequick_core;

ApmPipeline::ApmPipeline(int sample_rate_hz, int num_channels)
    : sample_rate_hz_(sample_rate_hz), num_channels_(num_channels) 
{
    webrtc::Config webrtc_config;
    apm_ = std::unique_ptr<webrtc::AudioProcessing>(webrtc::AudioProcessingBuilder().Create(webrtc_config));
    
    // Core structural requirements (Acoustic Echo Cancellation / Routing)
    apm_->ApplyConfig(config_);
}

ApmPipeline::~ApmPipeline() = default;

void ApmPipeline::enable_noise_suppression(webrtc::AudioProcessing::Config::NoiseSuppression::Level level) {
    config_.noise_suppression.enabled = true;
    config_.noise_suppression.level = level;
    apm_->ApplyConfig(config_);
}

void ApmPipeline::enable_voice_activity_detection() {
    config_.voice_detection.enabled = true;
    apm_->ApplyConfig(config_);
}

void ApmPipeline::enable_auto_gain_control() {
    config_.gain_controller1.enabled = true;
    config_.gain_controller1.mode = webrtc::AudioProcessing::Config::GainController1::kAdaptiveDigital;
    // Turn on modern AGC2 Adaptive Digital alongside if available
    config_.gain_controller2.enabled = true;
    config_.gain_controller2.adaptive_digital.enabled = true;
    apm_->ApplyConfig(config_);
}

void ApmPipeline::enable_echo_cancellation() {
    config_.echo_canceller.enabled = true;
    config_.echo_canceller.mobile_mode = false;
    apm_->ApplyConfig(config_);
}

bool ApmPipeline::process_capture_chunk(int16_t* audio_frame, size_t num_frames) {
    webrtc::StreamConfig config(sample_rate_hz_, num_channels_);
    
    int err = apm_->ProcessStream(audio_frame, config, config, audio_frame);
    if (err != 0) {
        std::cerr << "WebRTC APM ProcessStream explicitly failed with code: " << err << std::endl;
        return false;
    }

    bool vad = false;
    auto stats = apm_->GetStatistics();
    if (stats.voice_detected.has_value()) {
        vad = stats.voice_detected.value();
    }
    
    return vad;
}

void ApmPipeline::process_render_chunk(int16_t* audio_frame, size_t num_frames) {
    webrtc::StreamConfig config(sample_rate_hz_, num_channels_);
    apm_->ProcessReverseStream(audio_frame, config, config, audio_frame);
}
