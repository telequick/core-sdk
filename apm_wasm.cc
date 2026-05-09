#include <emscripten/bind.h>
#include "apm_pipeline.hh"

using namespace emscripten;
using namespace telequick_core;

class ApmPipelineWasm {
public:
    ApmPipelineWasm(int sample_rate_hz, int num_channels)
        : pipeline_(sample_rate_hz, num_channels) 
    {
        pipeline_.enable_noise_suppression(webrtc::AudioProcessing::Config::NoiseSuppression::kHigh);
        pipeline_.enable_voice_activity_detection();
        pipeline_.enable_echo_cancellation();
    }

    // Pass AudioWorklet Float32Array into PCM directly (usually WebAudio delivers floats [-1.0, 1.0])
    bool process_capture_chunk_float(intptr_t ptr, size_t num_frames) {
        float* float_data = reinterpret_cast<float*>(ptr);
        std::vector<int16_t> pcm_data(num_frames);
        for (size_t i = 0; i < num_frames; ++i) {
            pcm_data[i] = static_cast<int16_t>(float_data[i] * 32767.0f);
        }

        bool has_voice = pipeline_.process_capture_chunk(pcm_data.data(), num_frames);

        for (size_t i = 0; i < num_frames; ++i) {
            float_data[i] = static_cast<float>(pcm_data[i]) / 32767.0f;
        }
        return has_voice;
    }

    void process_render_chunk_float(intptr_t ptr, size_t num_frames) {
        float* float_data = reinterpret_cast<float*>(ptr);
        std::vector<int16_t> pcm_data(num_frames);
        for (size_t i = 0; i < num_frames; ++i) {
            pcm_data[i] = static_cast<int16_t>(float_data[i] * 32767.0f);
        }
        pipeline_.process_render_chunk(pcm_data.data(), num_frames);
    }

private:
    ApmPipeline pipeline_;
};

EMSCRIPTEN_BINDINGS(telequick_apm_module) {
    class_<ApmPipelineWasm>("ApmPipeline")
        .constructor<int, int>()
        .function("process_capture_chunk_float", &ApmPipelineWasm::process_capture_chunk_float)
        .function("process_render_chunk_float", &ApmPipelineWasm::process_render_chunk_float);
}
