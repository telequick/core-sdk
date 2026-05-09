#include "api_models.h"
#include <cstdlib>
#include <cstring>

using namespace telequick_core;

using namespace telequick::api;

extern "C" {

struct telequick_buffer { uint8_t* data; size_t length; };

__attribute__((visibility("default"))) void telequick_free_buffer(telequick_buffer buf) { if(buf.data) free(buf.data); }
__attribute__((visibility("default"))) void telequick_free_string(char* str) { if(str) free((void*)str); }

// Thread-local staging for the next originate's traceparent. SDK bindings
// call telequick_rpc_set_traceparent() right before telequick_rpc_originate_request()
// so the originate picks it up — keeps the existing positional FFI ABI
// stable (no breaking change) while letting language bindings opt into
// trace context propagation incrementally. Cleared after every originate
// so a stale value from a previous call can't bleed into a fresh one.
static thread_local std::string g_pending_traceparent;

__attribute__((visibility("default"))) void telequick_rpc_set_traceparent(const char* tp) {
    g_pending_traceparent = tp ? tp : "";
}

__attribute__((visibility("default"))) telequick_buffer telequick_rpc_originate_request(const char* _trunk_id, const char* _to, const char* _call_from, const char* _ai_websocket_url, const char* _ai_quic_url, const char* _tenant_id, int32_t _max_duration_ms, const char* _call_sid, DialplanAction _default_app, const char* _default_app_args, int32_t _auto_barge_in, int32_t _barge_in_patience_ms, const char* _client_id) {
    OriginateRequest req;
    req.trunk_id = _trunk_id ? _trunk_id : "";
    req.to = _to ? _to : "";
    req.call_from = _call_from ? _call_from : "";
    req.ai_websocket_url = _ai_websocket_url ? _ai_websocket_url : "";
    req.ai_quic_url = _ai_quic_url ? _ai_quic_url : "";
    req.tenant_id = _tenant_id ? _tenant_id : "";
    req.max_duration_ms = _max_duration_ms;
    req.call_sid = _call_sid ? _call_sid : "";
    req.default_app = static_cast<DialplanAction>(_default_app);
    req.default_app_args = _default_app_args ? _default_app_args : "";
    req.auto_barge_in = _auto_barge_in != 0;
    req.barge_in_patience_ms = _barge_in_patience_ms;
    req.client_id = _client_id ? _client_id : "";
    // Drain the thread-local staging slot — empty string is the "no
    // traceparent" sentinel and the engine treats it identically to a
    // missing field (falls back to deriving trace_id from call_sid).
    req.traceparent = std::move(g_pending_traceparent);
    g_pending_traceparent.clear();
    SerdeWriter w; req.serialize(w);
    uint32_t total_len = w.buffer().size() + 8;
    uint32_t method_id = 1430677891;
    telequick_buffer buf; buf.length = total_len;
    buf.data = (uint8_t*)malloc(buf.length);
    std::memcpy(buf.data, &total_len, 4);
    std::memcpy(buf.data + 4, &method_id, 4);
    std::memcpy(buf.data + 8, w.buffer().data(), w.buffer().size());
    return buf;
}

struct C_OriginateRequest {
    char* trunk_id;
    char* to;
    char* call_from;
    char* ai_websocket_url;
    char* ai_quic_url;
    char* tenant_id;
    int32_t max_duration_ms;
    char* call_sid;
    DialplanAction default_app;
    char* default_app_args;
    int32_t auto_barge_in;
    int32_t barge_in_patience_ms;
    char* client_id;
    // traceparent appended at the END of the struct so existing language
    // bindings that don't read past `client_id` continue to work unchanged
    // — only bindings that opt in see this field. ABI-stable: appending
    // is safe because the C ABI lays out fields in declaration order.
    char* traceparent;
};
__attribute__((visibility("default"))) C_OriginateRequest telequick_deserialize_originate_request(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); OriginateRequest req; req.deserialize(r);
    C_OriginateRequest c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.trunk_id = strdup(req.trunk_id.c_str());
    c_req.to = strdup(req.to.c_str());
    c_req.call_from = strdup(req.call_from.c_str());
    c_req.ai_websocket_url = strdup(req.ai_websocket_url.c_str());
    c_req.ai_quic_url = strdup(req.ai_quic_url.c_str());
    c_req.tenant_id = strdup(req.tenant_id.c_str());
    c_req.max_duration_ms = req.max_duration_ms;
    c_req.call_sid = strdup(req.call_sid.c_str());
    c_req.default_app = req.default_app;
    c_req.default_app_args = strdup(req.default_app_args.c_str());
    c_req.auto_barge_in = req.auto_barge_in;
    c_req.barge_in_patience_ms = req.barge_in_patience_ms;
    c_req.client_id = strdup(req.client_id.c_str());
    c_req.traceparent = strdup(req.traceparent.c_str());
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_serialize_audio_frame(const char* _call_sid, const char* _payload, const char* _codec, uint64_t _sequence_number, int32_t _end_of_stream) {
    AudioFrame req;
    req.call_sid = _call_sid ? _call_sid : "";
    req.payload = _payload ? _payload : "";
    req.codec = _codec ? _codec : "";
    req.sequence_number = _sequence_number;
    req.end_of_stream = _end_of_stream != 0;
    SerdeWriter w; req.serialize(w);
    telequick_buffer buf; buf.length = w.buffer().size();
    buf.data = (uint8_t*)malloc(buf.length); std::memcpy(buf.data, w.buffer().data(), buf.length); return buf;
}

struct C_AudioFrame {
    char* call_sid;
    char* payload;
    char* codec;
    uint64_t sequence_number;
    int32_t end_of_stream;
};
__attribute__((visibility("default"))) C_AudioFrame telequick_deserialize_audio_frame(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); AudioFrame req; req.deserialize(r);
    C_AudioFrame c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.call_sid = strdup(req.call_sid.c_str());
    c_req.payload = strdup(req.payload.c_str());
    c_req.codec = strdup(req.codec.c_str());
    c_req.sequence_number = req.sequence_number;
    c_req.end_of_stream = req.end_of_stream;
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_rpc_empty() {
    Empty req;
    SerdeWriter w; req.serialize(w);
    uint32_t total_len = w.buffer().size() + 8;
    uint32_t method_id = 2624504207;
    telequick_buffer buf; buf.length = total_len;
    buf.data = (uint8_t*)malloc(buf.length);
    std::memcpy(buf.data, &total_len, 4);
    std::memcpy(buf.data + 4, &method_id, 4);
    std::memcpy(buf.data + 8, w.buffer().data(), w.buffer().size());
    return buf;
}

struct C_Empty {
};
__attribute__((visibility("default"))) C_Empty telequick_deserialize_empty(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); Empty req; req.deserialize(r);
    C_Empty c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_rpc_barge_request(const char* _call_sid) {
    BargeRequest req;
    req.call_sid = _call_sid ? _call_sid : "";
    SerdeWriter w; req.serialize(w);
    uint32_t total_len = w.buffer().size() + 8;
    uint32_t method_id = 3854301714;
    telequick_buffer buf; buf.length = total_len;
    buf.data = (uint8_t*)malloc(buf.length);
    std::memcpy(buf.data, &total_len, 4);
    std::memcpy(buf.data + 4, &method_id, 4);
    std::memcpy(buf.data + 8, w.buffer().data(), w.buffer().size());
    return buf;
}

struct C_BargeRequest {
    char* call_sid;
};
__attribute__((visibility("default"))) C_BargeRequest telequick_deserialize_barge_request(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); BargeRequest req; req.deserialize(r);
    C_BargeRequest c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.call_sid = strdup(req.call_sid.c_str());
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_serialize_originate_response(const char* _call_sid, const char* _status, const char* _error_message, ErrorCode _error_code, int64_t _timestamp_ms) {
    OriginateResponse req;
    req.call_sid = _call_sid ? _call_sid : "";
    req.status = _status ? _status : "";
    req.error_message = _error_message ? _error_message : "";
    req.error_code = static_cast<ErrorCode>(_error_code);
    req.timestamp_ms = _timestamp_ms;
    SerdeWriter w; req.serialize(w);
    telequick_buffer buf; buf.length = w.buffer().size();
    buf.data = (uint8_t*)malloc(buf.length); std::memcpy(buf.data, w.buffer().data(), buf.length); return buf;
}

struct C_OriginateResponse {
    char* call_sid;
    char* status;
    char* error_message;
    ErrorCode error_code;
    int64_t timestamp_ms;
};
__attribute__((visibility("default"))) C_OriginateResponse telequick_deserialize_originate_response(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); OriginateResponse req; req.deserialize(r);
    C_OriginateResponse c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.call_sid = strdup(req.call_sid.c_str());
    c_req.status = strdup(req.status.c_str());
    c_req.error_message = strdup(req.error_message.c_str());
    c_req.error_code = req.error_code;
    c_req.timestamp_ms = req.timestamp_ms;
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_rpc_bulk_request(const char* _csv_url, const char* _template_trunk_id, const char* _template_to, const char* _template_call_from, const char* _template_ai_websocket_url, const char* _template_ai_quic_url, const char* _template_tenant_id, int32_t _template_max_duration_ms, DialplanAction _template_default_app, const char* _template_default_app_args, int32_t _calls_per_second, int32_t _max_concurrent_calls, const char* _campaign_id) {
    BulkRequest req;
    req.csv_url = _csv_url ? _csv_url : "";
    req.template_trunk_id = _template_trunk_id ? _template_trunk_id : "";
    req.template_to = _template_to ? _template_to : "";
    req.template_call_from = _template_call_from ? _template_call_from : "";
    req.template_ai_websocket_url = _template_ai_websocket_url ? _template_ai_websocket_url : "";
    req.template_ai_quic_url = _template_ai_quic_url ? _template_ai_quic_url : "";
    req.template_tenant_id = _template_tenant_id ? _template_tenant_id : "";
    req.template_max_duration_ms = _template_max_duration_ms;
    req.template_default_app = static_cast<DialplanAction>(_template_default_app);
    req.template_default_app_args = _template_default_app_args ? _template_default_app_args : "";
    req.calls_per_second = _calls_per_second;
    req.max_concurrent_calls = _max_concurrent_calls;
    req.campaign_id = _campaign_id ? _campaign_id : "";
    SerdeWriter w; req.serialize(w);
    uint32_t total_len = w.buffer().size() + 8;
    uint32_t method_id = 721069100;
    telequick_buffer buf; buf.length = total_len;
    buf.data = (uint8_t*)malloc(buf.length);
    std::memcpy(buf.data, &total_len, 4);
    std::memcpy(buf.data + 4, &method_id, 4);
    std::memcpy(buf.data + 8, w.buffer().data(), w.buffer().size());
    return buf;
}

struct C_BulkRequest {
    char* csv_url;
    char* template_trunk_id;
    char* template_to;
    char* template_call_from;
    char* template_ai_websocket_url;
    char* template_ai_quic_url;
    char* template_tenant_id;
    int32_t template_max_duration_ms;
    DialplanAction template_default_app;
    char* template_default_app_args;
    int32_t calls_per_second;
    int32_t max_concurrent_calls;
    char* campaign_id;
};
__attribute__((visibility("default"))) C_BulkRequest telequick_deserialize_bulk_request(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); BulkRequest req; req.deserialize(r);
    C_BulkRequest c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.csv_url = strdup(req.csv_url.c_str());
    c_req.template_trunk_id = strdup(req.template_trunk_id.c_str());
    c_req.template_to = strdup(req.template_to.c_str());
    c_req.template_call_from = strdup(req.template_call_from.c_str());
    c_req.template_ai_websocket_url = strdup(req.template_ai_websocket_url.c_str());
    c_req.template_ai_quic_url = strdup(req.template_ai_quic_url.c_str());
    c_req.template_tenant_id = strdup(req.template_tenant_id.c_str());
    c_req.template_max_duration_ms = req.template_max_duration_ms;
    c_req.template_default_app = req.template_default_app;
    c_req.template_default_app_args = strdup(req.template_default_app_args.c_str());
    c_req.calls_per_second = req.calls_per_second;
    c_req.max_concurrent_calls = req.max_concurrent_calls;
    c_req.campaign_id = strdup(req.campaign_id.c_str());
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_serialize_bulk_response(const char* _status, int32_t _loaded_numbers) {
    BulkResponse req;
    req.status = _status ? _status : "";
    req.loaded_numbers = _loaded_numbers;
    SerdeWriter w; req.serialize(w);
    telequick_buffer buf; buf.length = w.buffer().size();
    buf.data = (uint8_t*)malloc(buf.length); std::memcpy(buf.data, w.buffer().data(), buf.length); return buf;
}

struct C_BulkResponse {
    char* status;
    int32_t loaded_numbers;
};
__attribute__((visibility("default"))) C_BulkResponse telequick_deserialize_bulk_response(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); BulkResponse req; req.deserialize(r);
    C_BulkResponse c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.status = strdup(req.status.c_str());
    c_req.loaded_numbers = req.loaded_numbers;
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_rpc_abort_bulk_request(const char* _campaign_id) {
    AbortBulkRequest req;
    req.campaign_id = _campaign_id ? _campaign_id : "";
    SerdeWriter w; req.serialize(w);
    uint32_t total_len = w.buffer().size() + 8;
    uint32_t method_id = 3861915064;
    telequick_buffer buf; buf.length = total_len;
    buf.data = (uint8_t*)malloc(buf.length);
    std::memcpy(buf.data, &total_len, 4);
    std::memcpy(buf.data + 4, &method_id, 4);
    std::memcpy(buf.data + 8, w.buffer().data(), w.buffer().size());
    return buf;
}

struct C_AbortBulkRequest {
    char* campaign_id;
};
__attribute__((visibility("default"))) C_AbortBulkRequest telequick_deserialize_abort_bulk_request(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); AbortBulkRequest req; req.deserialize(r);
    C_AbortBulkRequest c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.campaign_id = strdup(req.campaign_id.c_str());
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_rpc_terminate_request(const char* _call_sid) {
    TerminateRequest req;
    req.call_sid = _call_sid ? _call_sid : "";
    SerdeWriter w; req.serialize(w);
    uint32_t total_len = w.buffer().size() + 8;
    uint32_t method_id = 3834253405;
    telequick_buffer buf; buf.length = total_len;
    buf.data = (uint8_t*)malloc(buf.length);
    std::memcpy(buf.data, &total_len, 4);
    std::memcpy(buf.data + 4, &method_id, 4);
    std::memcpy(buf.data + 8, w.buffer().data(), w.buffer().size());
    return buf;
}

struct C_TerminateRequest {
    char* call_sid;
};
__attribute__((visibility("default"))) C_TerminateRequest telequick_deserialize_terminate_request(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); TerminateRequest req; req.deserialize(r);
    C_TerminateRequest c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.call_sid = strdup(req.call_sid.c_str());
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_serialize_terminate_response(const char* _call_sid, const char* _status, const char* _error_message, ErrorCode _error_code, int64_t _timestamp_ms) {
    TerminateResponse req;
    req.call_sid = _call_sid ? _call_sid : "";
    req.status = _status ? _status : "";
    req.error_message = _error_message ? _error_message : "";
    req.error_code = static_cast<ErrorCode>(_error_code);
    req.timestamp_ms = _timestamp_ms;
    SerdeWriter w; req.serialize(w);
    telequick_buffer buf; buf.length = w.buffer().size();
    buf.data = (uint8_t*)malloc(buf.length); std::memcpy(buf.data, w.buffer().data(), buf.length); return buf;
}

struct C_TerminateResponse {
    char* call_sid;
    char* status;
    char* error_message;
    ErrorCode error_code;
    int64_t timestamp_ms;
};
__attribute__((visibility("default"))) C_TerminateResponse telequick_deserialize_terminate_response(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); TerminateResponse req; req.deserialize(r);
    C_TerminateResponse c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.call_sid = strdup(req.call_sid.c_str());
    c_req.status = strdup(req.status.c_str());
    c_req.error_message = strdup(req.error_message.c_str());
    c_req.error_code = req.error_code;
    c_req.timestamp_ms = req.timestamp_ms;
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_rpc_set_inbound_routing_request(const char* _trunk_id, InboundRule _rule, const char* _audio_url, const char* _webhook_url, const char* _ai_websocket_url, const char* _ai_quic_url) {
    SetInboundRoutingRequest req;
    req.trunk_id = _trunk_id ? _trunk_id : "";
    req.rule = static_cast<InboundRule>(_rule);
    req.audio_url = _audio_url ? _audio_url : "";
    req.webhook_url = _webhook_url ? _webhook_url : "";
    req.ai_websocket_url = _ai_websocket_url ? _ai_websocket_url : "";
    req.ai_quic_url = _ai_quic_url ? _ai_quic_url : "";
    SerdeWriter w; req.serialize(w);
    uint32_t total_len = w.buffer().size() + 8;
    uint32_t method_id = 1933986897;
    telequick_buffer buf; buf.length = total_len;
    buf.data = (uint8_t*)malloc(buf.length);
    std::memcpy(buf.data, &total_len, 4);
    std::memcpy(buf.data + 4, &method_id, 4);
    std::memcpy(buf.data + 8, w.buffer().data(), w.buffer().size());
    return buf;
}

struct C_SetInboundRoutingRequest {
    char* trunk_id;
    InboundRule rule;
    char* audio_url;
    char* webhook_url;
    char* ai_websocket_url;
    char* ai_quic_url;
};
__attribute__((visibility("default"))) C_SetInboundRoutingRequest telequick_deserialize_set_inbound_routing_request(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); SetInboundRoutingRequest req; req.deserialize(r);
    C_SetInboundRoutingRequest c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.trunk_id = strdup(req.trunk_id.c_str());
    c_req.rule = req.rule;
    c_req.audio_url = strdup(req.audio_url.c_str());
    c_req.webhook_url = strdup(req.webhook_url.c_str());
    c_req.ai_websocket_url = strdup(req.ai_websocket_url.c_str());
    c_req.ai_quic_url = strdup(req.ai_quic_url.c_str());
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_rpc_event_stream_request(const char* _client_id) {
    EventStreamRequest req;
    req.client_id = _client_id ? _client_id : "";
    SerdeWriter w; req.serialize(w);
    uint32_t total_len = w.buffer().size() + 8;
    uint32_t method_id = 959835745;
    telequick_buffer buf; buf.length = total_len;
    buf.data = (uint8_t*)malloc(buf.length);
    std::memcpy(buf.data, &total_len, 4);
    std::memcpy(buf.data + 4, &method_id, 4);
    std::memcpy(buf.data + 8, w.buffer().data(), w.buffer().size());
    return buf;
}

struct C_EventStreamRequest {
    char* client_id;
};
__attribute__((visibility("default"))) C_EventStreamRequest telequick_deserialize_event_stream_request(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); EventStreamRequest req; req.deserialize(r);
    C_EventStreamRequest c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.client_id = strdup(req.client_id.c_str());
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_serialize_call_event(const char* _call_sid, EventType _event_type, const char* _status, int64_t _start_timestamp_ms, int32_t _q850_cause, const char* _recording_url, int32_t _duration_seconds, int64_t _answer_timestamp_ms, int64_t _end_timestamp_ms, uint32_t _packets_sent, uint32_t _packets_received, uint32_t _packets_lost, uint64_t _bytes_sent, double _jitter_ms, double _estimated_mos, const char* _trunk_id, const char* _tenant_id, const char* _codec, int64_t _timestamp_ms, const char* _client_id) {
    CallEvent req;
    req.call_sid = _call_sid ? _call_sid : "";
    req.event_type = static_cast<EventType>(_event_type);
    req.status = _status ? _status : "";
    req.start_timestamp_ms = _start_timestamp_ms;
    req.q850_cause = _q850_cause;
    req.recording_url = _recording_url ? _recording_url : "";
    req.duration_seconds = _duration_seconds;
    req.answer_timestamp_ms = _answer_timestamp_ms;
    req.end_timestamp_ms = _end_timestamp_ms;
    req.packets_sent = _packets_sent;
    req.packets_received = _packets_received;
    req.packets_lost = _packets_lost;
    req.bytes_sent = _bytes_sent;
    req.jitter_ms = _jitter_ms;
    req.estimated_mos = _estimated_mos;
    req.trunk_id = _trunk_id ? _trunk_id : "";
    req.tenant_id = _tenant_id ? _tenant_id : "";
    req.codec = _codec ? _codec : "";
    req.timestamp_ms = _timestamp_ms;
    req.client_id = _client_id ? _client_id : "";
    SerdeWriter w; req.serialize(w);
    telequick_buffer buf; buf.length = w.buffer().size();
    buf.data = (uint8_t*)malloc(buf.length); std::memcpy(buf.data, w.buffer().data(), buf.length); return buf;
}

struct C_CallEvent {
    char* call_sid;
    EventType event_type;
    char* status;
    int64_t start_timestamp_ms;
    int32_t q850_cause;
    char* recording_url;
    int32_t duration_seconds;
    int64_t answer_timestamp_ms;
    int64_t end_timestamp_ms;
    uint32_t packets_sent;
    uint32_t packets_received;
    uint32_t packets_lost;
    uint64_t bytes_sent;
    double jitter_ms;
    double estimated_mos;
    char* trunk_id;
    char* tenant_id;
    char* codec;
    int64_t timestamp_ms;
    char* client_id;
};
__attribute__((visibility("default"))) C_CallEvent telequick_deserialize_call_event(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); CallEvent req; req.deserialize(r);
    C_CallEvent c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.call_sid = strdup(req.call_sid.c_str());
    c_req.event_type = req.event_type;
    c_req.status = strdup(req.status.c_str());
    c_req.start_timestamp_ms = req.start_timestamp_ms;
    c_req.q850_cause = req.q850_cause;
    c_req.recording_url = strdup(req.recording_url.c_str());
    c_req.duration_seconds = req.duration_seconds;
    c_req.answer_timestamp_ms = req.answer_timestamp_ms;
    c_req.end_timestamp_ms = req.end_timestamp_ms;
    c_req.packets_sent = req.packets_sent;
    c_req.packets_received = req.packets_received;
    c_req.packets_lost = req.packets_lost;
    c_req.bytes_sent = req.bytes_sent;
    c_req.jitter_ms = req.jitter_ms;
    c_req.estimated_mos = req.estimated_mos;
    c_req.trunk_id = strdup(req.trunk_id.c_str());
    c_req.tenant_id = strdup(req.tenant_id.c_str());
    c_req.codec = strdup(req.codec.c_str());
    c_req.timestamp_ms = req.timestamp_ms;
    c_req.client_id = strdup(req.client_id.c_str());
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_rpc_get_incoming_calls_request(const char* _trunk_id) {
    GetIncomingCallsRequest req;
    req.trunk_id = _trunk_id ? _trunk_id : "";
    SerdeWriter w; req.serialize(w);
    uint32_t total_len = w.buffer().size() + 8;
    uint32_t method_id = 1161946746;
    telequick_buffer buf; buf.length = total_len;
    buf.data = (uint8_t*)malloc(buf.length);
    std::memcpy(buf.data, &total_len, 4);
    std::memcpy(buf.data + 4, &method_id, 4);
    std::memcpy(buf.data + 8, w.buffer().data(), w.buffer().size());
    return buf;
}

struct C_GetIncomingCallsRequest {
    char* trunk_id;
};
__attribute__((visibility("default"))) C_GetIncomingCallsRequest telequick_deserialize_get_incoming_calls_request(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); GetIncomingCallsRequest req; req.deserialize(r);
    C_GetIncomingCallsRequest c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.trunk_id = strdup(req.trunk_id.c_str());
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_serialize_incoming_call_info(const char* _call_sid, const char* _call_from, int64_t _start_timestamp_ms) {
    IncomingCallInfo req;
    req.call_sid = _call_sid ? _call_sid : "";
    req.call_from = _call_from ? _call_from : "";
    req.start_timestamp_ms = _start_timestamp_ms;
    SerdeWriter w; req.serialize(w);
    telequick_buffer buf; buf.length = w.buffer().size();
    buf.data = (uint8_t*)malloc(buf.length); std::memcpy(buf.data, w.buffer().data(), buf.length); return buf;
}

struct C_IncomingCallInfo {
    char* call_sid;
    char* call_from;
    int64_t start_timestamp_ms;
};
__attribute__((visibility("default"))) C_IncomingCallInfo telequick_deserialize_incoming_call_info(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); IncomingCallInfo req; req.deserialize(r);
    C_IncomingCallInfo c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.call_sid = strdup(req.call_sid.c_str());
    c_req.call_from = strdup(req.call_from.c_str());
    c_req.start_timestamp_ms = req.start_timestamp_ms;
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_serialize_get_incoming_calls_response(std::vector<IncomingCallInfo> _calls) {
    GetIncomingCallsResponse req;
    SerdeWriter w; req.serialize(w);
    telequick_buffer buf; buf.length = w.buffer().size();
    buf.data = (uint8_t*)malloc(buf.length); std::memcpy(buf.data, w.buffer().data(), buf.length); return buf;
}

struct C_GetIncomingCallsResponse {
    std::vector<IncomingCallInfo> calls;
};
__attribute__((visibility("default"))) C_GetIncomingCallsResponse telequick_deserialize_get_incoming_calls_response(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); GetIncomingCallsResponse req; req.deserialize(r);
    C_GetIncomingCallsResponse c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_rpc_answer_incoming_call_request(const char* _call_sid, const char* _ai_websocket_url, const char* _ai_quic_url) {
    AnswerIncomingCallRequest req;
    req.call_sid = _call_sid ? _call_sid : "";
    req.ai_websocket_url = _ai_websocket_url ? _ai_websocket_url : "";
    req.ai_quic_url = _ai_quic_url ? _ai_quic_url : "";
    SerdeWriter w; req.serialize(w);
    uint32_t total_len = w.buffer().size() + 8;
    uint32_t method_id = 2990157256;
    telequick_buffer buf; buf.length = total_len;
    buf.data = (uint8_t*)malloc(buf.length);
    std::memcpy(buf.data, &total_len, 4);
    std::memcpy(buf.data + 4, &method_id, 4);
    std::memcpy(buf.data + 8, w.buffer().data(), w.buffer().size());
    return buf;
}

struct C_AnswerIncomingCallRequest {
    char* call_sid;
    char* ai_websocket_url;
    char* ai_quic_url;
};
__attribute__((visibility("default"))) C_AnswerIncomingCallRequest telequick_deserialize_answer_incoming_call_request(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); AnswerIncomingCallRequest req; req.deserialize(r);
    C_AnswerIncomingCallRequest c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.call_sid = strdup(req.call_sid.c_str());
    c_req.ai_websocket_url = strdup(req.ai_websocket_url.c_str());
    c_req.ai_quic_url = strdup(req.ai_quic_url.c_str());
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_serialize_answer_incoming_call_response(const char* _call_sid, const char* _status, const char* _error_message, ErrorCode _error_code, int64_t _timestamp_ms) {
    AnswerIncomingCallResponse req;
    req.call_sid = _call_sid ? _call_sid : "";
    req.status = _status ? _status : "";
    req.error_message = _error_message ? _error_message : "";
    req.error_code = static_cast<ErrorCode>(_error_code);
    req.timestamp_ms = _timestamp_ms;
    SerdeWriter w; req.serialize(w);
    telequick_buffer buf; buf.length = w.buffer().size();
    buf.data = (uint8_t*)malloc(buf.length); std::memcpy(buf.data, w.buffer().data(), buf.length); return buf;
}

struct C_AnswerIncomingCallResponse {
    char* call_sid;
    char* status;
    char* error_message;
    ErrorCode error_code;
    int64_t timestamp_ms;
};
__attribute__((visibility("default"))) C_AnswerIncomingCallResponse telequick_deserialize_answer_incoming_call_response(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); AnswerIncomingCallResponse req; req.deserialize(r);
    C_AnswerIncomingCallResponse c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.call_sid = strdup(req.call_sid.c_str());
    c_req.status = strdup(req.status.c_str());
    c_req.error_message = strdup(req.error_message.c_str());
    c_req.error_code = req.error_code;
    c_req.timestamp_ms = req.timestamp_ms;
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_serialize_bucket_info(const char* _bucket_id, int32_t _pending_count) {
    BucketInfo req;
    req.bucket_id = _bucket_id ? _bucket_id : "";
    req.pending_count = _pending_count;
    SerdeWriter w; req.serialize(w);
    telequick_buffer buf; buf.length = w.buffer().size();
    buf.data = (uint8_t*)malloc(buf.length); std::memcpy(buf.data, w.buffer().data(), buf.length); return buf;
}

struct C_BucketInfo {
    char* bucket_id;
    int32_t pending_count;
};
__attribute__((visibility("default"))) C_BucketInfo telequick_deserialize_bucket_info(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); BucketInfo req; req.deserialize(r);
    C_BucketInfo c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.bucket_id = strdup(req.bucket_id.c_str());
    c_req.pending_count = req.pending_count;
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_serialize_list_buckets_response(std::vector<BucketInfo> _buckets) {
    ListBucketsResponse req;
    SerdeWriter w; req.serialize(w);
    telequick_buffer buf; buf.length = w.buffer().size();
    buf.data = (uint8_t*)malloc(buf.length); std::memcpy(buf.data, w.buffer().data(), buf.length); return buf;
}

struct C_ListBucketsResponse {
    std::vector<BucketInfo> buckets;
};
__attribute__((visibility("default"))) C_ListBucketsResponse telequick_deserialize_list_buckets_response(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); ListBucketsResponse req; req.deserialize(r);
    C_ListBucketsResponse c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_rpc_bucket_request(const char* _bucket_id) {
    BucketRequest req;
    req.bucket_id = _bucket_id ? _bucket_id : "";
    SerdeWriter w; req.serialize(w);
    uint32_t total_len = w.buffer().size() + 8;
    uint32_t method_id = 1217351135;
    telequick_buffer buf; buf.length = total_len;
    buf.data = (uint8_t*)malloc(buf.length);
    std::memcpy(buf.data, &total_len, 4);
    std::memcpy(buf.data + 4, &method_id, 4);
    std::memcpy(buf.data + 8, w.buffer().data(), w.buffer().size());
    return buf;
}

struct C_BucketRequest {
    char* bucket_id;
};
__attribute__((visibility("default"))) C_BucketRequest telequick_deserialize_bucket_request(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); BucketRequest req; req.deserialize(r);
    C_BucketRequest c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.bucket_id = strdup(req.bucket_id.c_str());
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_serialize_bucket_call_list(const char* _call_sids) {
    BucketCallList req;
    req.call_sids = _call_sids ? _call_sids : "";
    SerdeWriter w; req.serialize(w);
    telequick_buffer buf; buf.length = w.buffer().size();
    buf.data = (uint8_t*)malloc(buf.length); std::memcpy(buf.data, w.buffer().data(), buf.length); return buf;
}

struct C_BucketCallList {
    char* call_sids;
};
__attribute__((visibility("default"))) C_BucketCallList telequick_deserialize_bucket_call_list(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); BucketCallList req; req.deserialize(r);
    C_BucketCallList c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.call_sids = strdup(req.call_sids.c_str());
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_rpc_bucket_action_request(const char* _bucket_id, int32_t _action) {
    BucketActionRequest req;
    req.bucket_id = _bucket_id ? _bucket_id : "";
    req.action = _action;
    SerdeWriter w; req.serialize(w);
    uint32_t total_len = w.buffer().size() + 8;
    uint32_t method_id = 4030863293;
    telequick_buffer buf; buf.length = total_len;
    buf.data = (uint8_t*)malloc(buf.length);
    std::memcpy(buf.data, &total_len, 4);
    std::memcpy(buf.data + 4, &method_id, 4);
    std::memcpy(buf.data + 8, w.buffer().data(), w.buffer().size());
    return buf;
}

struct C_BucketActionRequest {
    char* bucket_id;
    int32_t action;
};
__attribute__((visibility("default"))) C_BucketActionRequest telequick_deserialize_bucket_action_request(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); BucketActionRequest req; req.deserialize(r);
    C_BucketActionRequest c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.bucket_id = strdup(req.bucket_id.c_str());
    c_req.action = req.action;
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_serialize_bucket_action_response(int32_t _processed_count) {
    BucketActionResponse req;
    req.processed_count = _processed_count;
    SerdeWriter w; req.serialize(w);
    telequick_buffer buf; buf.length = w.buffer().size();
    buf.data = (uint8_t*)malloc(buf.length); std::memcpy(buf.data, w.buffer().data(), buf.length); return buf;
}

struct C_BucketActionResponse {
    int32_t processed_count;
};
__attribute__((visibility("default"))) C_BucketActionResponse telequick_deserialize_bucket_action_response(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); BucketActionResponse req; req.deserialize(r);
    C_BucketActionResponse c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.processed_count = req.processed_count;
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_rpc_execute_dialplan_request(const char* _call_sid, DialplanAction _action, const char* _app_args) {
    ExecuteDialplanRequest req;
    req.call_sid = _call_sid ? _call_sid : "";
    req.action = static_cast<DialplanAction>(_action);
    req.app_args = _app_args ? _app_args : "";
    SerdeWriter w; req.serialize(w);
    uint32_t total_len = w.buffer().size() + 8;
    uint32_t method_id = 80147304;
    telequick_buffer buf; buf.length = total_len;
    buf.data = (uint8_t*)malloc(buf.length);
    std::memcpy(buf.data, &total_len, 4);
    std::memcpy(buf.data + 4, &method_id, 4);
    std::memcpy(buf.data + 8, w.buffer().data(), w.buffer().size());
    return buf;
}

struct C_ExecuteDialplanRequest {
    char* call_sid;
    DialplanAction action;
    char* app_args;
};
__attribute__((visibility("default"))) C_ExecuteDialplanRequest telequick_deserialize_execute_dialplan_request(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); ExecuteDialplanRequest req; req.deserialize(r);
    C_ExecuteDialplanRequest c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.call_sid = strdup(req.call_sid.c_str());
    c_req.action = req.action;
    c_req.app_args = strdup(req.app_args.c_str());
    return c_req;
}

__attribute__((visibility("default"))) telequick_buffer telequick_serialize_execute_dialplan_response(const char* _status, const char* _error_message, ErrorCode _error_code) {
    ExecuteDialplanResponse req;
    req.status = _status ? _status : "";
    req.error_message = _error_message ? _error_message : "";
    req.error_code = static_cast<ErrorCode>(_error_code);
    SerdeWriter w; req.serialize(w);
    telequick_buffer buf; buf.length = w.buffer().size();
    buf.data = (uint8_t*)malloc(buf.length); std::memcpy(buf.data, w.buffer().data(), buf.length); return buf;
}

struct C_ExecuteDialplanResponse {
    char* status;
    char* error_message;
    ErrorCode error_code;
};
__attribute__((visibility("default"))) C_ExecuteDialplanResponse telequick_deserialize_execute_dialplan_response(const uint8_t* buffer, size_t length) {
    SerdeReader r(buffer, length); ExecuteDialplanResponse req; req.deserialize(r);
    C_ExecuteDialplanResponse c_req;
#ifdef _MSC_VER
    #define strdup _strdup
#endif
    c_req.status = strdup(req.status.c_str());
    c_req.error_message = strdup(req.error_message.c_str());
    c_req.error_code = req.error_code;
    return c_req;
}

} // extern "C"
