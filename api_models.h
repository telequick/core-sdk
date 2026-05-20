#pragma once

#include "serde_lite.h"
#include <string>
#include <vector>
#include <cstdint>

using namespace telequick_core;

namespace telequick::api {

enum class MethodID : uint32_t {
    ORIGINATE = 1430677891,
    ORIGINATE_BULK = 721069100,
    ABORT_BULK = 3861915064,
    TERMINATE = 3834253405,
    STREAM_EVENTS = 959835745,
    SET_INBOUND_ROUTING = 1933986897,
    GET_INCOMING_CALLS = 1161946746,
    ANSWER_INCOMING_CALL = 2990157256,
    GET_ACTIVE_BUCKETS = 2624504207,
    GET_BUCKET_CALLS = 1217351135,
    EXECUTE_BUCKET_ACTION = 4030863293,
    EXECUTE_DIALPLAN = 80147304,
    BARGE = 3854301714,
    AUDIO_FRAME = 2991054320
};

enum class ErrorCode : int32_t {
    SUCCESS=0, ERR_INVALID_TRUNK=1, ERR_INVALID_DESTINATION=2, ERR_RATE_LIMITED=3, ERR_CIRCUIT_BREAKER=4, ERR_INTERNAL_ERROR=5, ERR_VALIDATION_FAILED=6, ERR_UNAUTHORIZED=7
};
enum class DialplanAction : int32_t {
    HANGUP=0, PARK=1, MUSIC_ON_HOLD=2, PLAYBACK=3, UNPARK_AND_BRIDGE=4, ANSWER=5, AI_BIDIRECTIONAL_STREAM=6, TRANSFER=7, MUTE=8, UNMUTE=9, HOLD=10, UNHOLD=11, SEND_DTMF=12,
    // 13 = SUPERVISE (gateway-only, never offered to SDK callers).
    // 14 = LOOPBACK (synthetic engine-side echo for `tq loopback`).
    LOOPBACK=14
};
enum class InboundRule : int32_t {
    REJECT=0, PLAY_AND_HANGUP=1, NOTIFY_AND_HANGUP=2, HANDLE_AI=3
};
enum class EventType : int32_t {
    UNKNOWN=0, CHANNEL_CREATE=1, CHANNEL_ANSWER=2, CHANNEL_HANGUP_COMPLETE=3, CHANNEL_HOLD=4, CHANNEL_RESUME=5
};
struct OriginateRequest {
    std::string trunk_id;
    std::string to;
    std::string call_from;
    std::string ai_websocket_url;
    std::string ai_quic_url;
    std::string tenant_id;
    int32_t max_duration_ms;
    std::string call_sid;
    DialplanAction default_app;
    std::string default_app_args;
    bool auto_barge_in;
    int32_t barge_in_patience_ms;
    std::string client_id;
    // Mirror the engine-side OriginateRequest (telequick/api/telequick_types.hh)
    // — version-1 fields appended in the same order so the serde envelope
    // round-trips between SDK and engine. Engine reads compat_version=0 so
    // older SDKs that don't write these still deserialize cleanly (the
    // engine sees zeroed fields and falls back to its own defaults).
    uint32_t session_id = 0;
    std::string agent_config_key;
    std::string traceparent;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(1, 0);
        w.write_string(trunk_id);
        w.write_string(to);
        w.write_string(call_from);
        w.write_string(ai_websocket_url);
        w.write_string(ai_quic_url);
        w.write_string(tenant_id);
        w.write_pod<int32_t>(max_duration_ms);
        w.write_string(call_sid);
        w.write_pod<int32_t>(static_cast<int32_t>(default_app));
        w.write_string(default_app_args);
        w.write_pod<bool>(auto_barge_in);
        w.write_pod<int32_t>(barge_in_patience_ms);
        w.write_string(client_id);
        w.write_pod<uint32_t>(session_id);
        w.write_string(agent_config_key);
        w.write_string(traceparent);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        trunk_id = r.read_string();
        to = r.read_string();
        call_from = r.read_string();
        ai_websocket_url = r.read_string();
        ai_quic_url = r.read_string();
        tenant_id = r.read_string();
        max_duration_ms = r.read_pod<int32_t>();
        call_sid = r.read_string();
        default_app = static_cast<DialplanAction>(r.read_pod<int32_t>());
        default_app_args = r.read_string();
        auto_barge_in = r.read_pod<bool>();
        barge_in_patience_ms = r.read_pod<int32_t>();
        client_id = r.read_string();
        // Trailing v1 fields. skip_to_envelope_end handles the case where an
        // older peer didn't include them (envelope length stops reads early).
        session_id = r.read_pod<uint32_t>();
        agent_config_key = r.read_string();
        traceparent = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct AudioFrame {
    std::string call_sid;
    std::string payload;
    std::string codec;
    uint64_t sequence_number;
    bool end_of_stream;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(call_sid);
        w.write_string(payload);
        w.write_string(codec);
        w.write_pod<uint64_t>(sequence_number);
        w.write_pod<bool>(end_of_stream);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        call_sid = r.read_string();
        payload = r.read_string();
        codec = r.read_string();
        sequence_number = r.read_pod<uint64_t>();
        end_of_stream = r.read_pod<bool>();
        r.skip_to_envelope_end(_env);
    }
};

struct Empty {

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        r.skip_to_envelope_end(_env);
    }
};

struct BargeRequest {
    std::string call_sid;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(call_sid);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        call_sid = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct OriginateResponse {
    std::string call_sid;
    std::string status;
    std::string error_message;
    ErrorCode error_code;
    int64_t timestamp_ms;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(call_sid);
        w.write_string(status);
        w.write_string(error_message);
        w.write_pod<int32_t>(static_cast<int32_t>(error_code));
        w.write_pod<int64_t>(timestamp_ms);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        call_sid = r.read_string();
        status = r.read_string();
        error_message = r.read_string();
        error_code = static_cast<ErrorCode>(r.read_pod<int32_t>());
        timestamp_ms = r.read_pod<int64_t>();
        r.skip_to_envelope_end(_env);
    }
};

struct BulkRequest {
    std::string csv_url;
    std::string template_trunk_id;
    std::string template_to;
    std::string template_call_from;
    std::string template_ai_websocket_url;
    std::string template_ai_quic_url;
    std::string template_tenant_id;
    int32_t template_max_duration_ms;
    DialplanAction template_default_app;
    std::string template_default_app_args;
    int32_t calls_per_second;
    int32_t max_concurrent_calls;
    std::string campaign_id;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(csv_url);
        w.write_string(template_trunk_id);
        w.write_string(template_to);
        w.write_string(template_call_from);
        w.write_string(template_ai_websocket_url);
        w.write_string(template_ai_quic_url);
        w.write_string(template_tenant_id);
        w.write_pod<int32_t>(template_max_duration_ms);
        w.write_pod<int32_t>(static_cast<int32_t>(template_default_app));
        w.write_string(template_default_app_args);
        w.write_pod<int32_t>(calls_per_second);
        w.write_pod<int32_t>(max_concurrent_calls);
        w.write_string(campaign_id);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        csv_url = r.read_string();
        template_trunk_id = r.read_string();
        template_to = r.read_string();
        template_call_from = r.read_string();
        template_ai_websocket_url = r.read_string();
        template_ai_quic_url = r.read_string();
        template_tenant_id = r.read_string();
        template_max_duration_ms = r.read_pod<int32_t>();
        template_default_app = static_cast<DialplanAction>(r.read_pod<int32_t>());
        template_default_app_args = r.read_string();
        calls_per_second = r.read_pod<int32_t>();
        max_concurrent_calls = r.read_pod<int32_t>();
        campaign_id = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct BulkResponse {
    std::string status;
    int32_t loaded_numbers;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(status);
        w.write_pod<int32_t>(loaded_numbers);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        status = r.read_string();
        loaded_numbers = r.read_pod<int32_t>();
        r.skip_to_envelope_end(_env);
    }
};

struct AbortBulkRequest {
    std::string campaign_id;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(campaign_id);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        campaign_id = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct TerminateRequest {
    std::string call_sid;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(call_sid);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        call_sid = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct TerminateResponse {
    std::string call_sid;
    std::string status;
    std::string error_message;
    ErrorCode error_code;
    int64_t timestamp_ms;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(call_sid);
        w.write_string(status);
        w.write_string(error_message);
        w.write_pod<int32_t>(static_cast<int32_t>(error_code));
        w.write_pod<int64_t>(timestamp_ms);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        call_sid = r.read_string();
        status = r.read_string();
        error_message = r.read_string();
        error_code = static_cast<ErrorCode>(r.read_pod<int32_t>());
        timestamp_ms = r.read_pod<int64_t>();
        r.skip_to_envelope_end(_env);
    }
};

struct SetInboundRoutingRequest {
    std::string trunk_id;
    InboundRule rule;
    std::string audio_url;
    std::string webhook_url;
    std::string ai_websocket_url;
    std::string ai_quic_url;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(trunk_id);
        w.write_pod<int32_t>(static_cast<int32_t>(rule));
        w.write_string(audio_url);
        w.write_string(webhook_url);
        w.write_string(ai_websocket_url);
        w.write_string(ai_quic_url);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        trunk_id = r.read_string();
        rule = static_cast<InboundRule>(r.read_pod<int32_t>());
        audio_url = r.read_string();
        webhook_url = r.read_string();
        ai_websocket_url = r.read_string();
        ai_quic_url = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct EventStreamRequest {
    std::string client_id;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(client_id);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        client_id = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct CallEvent {
    std::string call_sid;
    EventType event_type;
    std::string status;
    int64_t start_timestamp_ms;
    int32_t q850_cause;
    std::string recording_url;
    int32_t duration_seconds;
    int64_t answer_timestamp_ms;
    int64_t end_timestamp_ms;
    uint32_t packets_sent;
    uint32_t packets_received;
    uint32_t packets_lost;
    uint64_t bytes_sent;
    double jitter_ms;
    double estimated_mos;
    std::string trunk_id;
    std::string tenant_id;
    std::string codec;
    int64_t timestamp_ms;
    std::string client_id;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(call_sid);
        w.write_pod<int32_t>(static_cast<int32_t>(event_type));
        w.write_string(status);
        w.write_pod<int64_t>(start_timestamp_ms);
        w.write_pod<int32_t>(q850_cause);
        w.write_string(recording_url);
        w.write_pod<int32_t>(duration_seconds);
        w.write_pod<int64_t>(answer_timestamp_ms);
        w.write_pod<int64_t>(end_timestamp_ms);
        w.write_pod<uint32_t>(packets_sent);
        w.write_pod<uint32_t>(packets_received);
        w.write_pod<uint32_t>(packets_lost);
        w.write_pod<uint64_t>(bytes_sent);
        w.write_pod<double>(jitter_ms);
        w.write_pod<double>(estimated_mos);
        w.write_string(trunk_id);
        w.write_string(tenant_id);
        w.write_string(codec);
        w.write_pod<int64_t>(timestamp_ms);
        w.write_string(client_id);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        call_sid = r.read_string();
        event_type = static_cast<EventType>(r.read_pod<int32_t>());
        status = r.read_string();
        start_timestamp_ms = r.read_pod<int64_t>();
        q850_cause = r.read_pod<int32_t>();
        recording_url = r.read_string();
        duration_seconds = r.read_pod<int32_t>();
        answer_timestamp_ms = r.read_pod<int64_t>();
        end_timestamp_ms = r.read_pod<int64_t>();
        packets_sent = r.read_pod<uint32_t>();
        packets_received = r.read_pod<uint32_t>();
        packets_lost = r.read_pod<uint32_t>();
        bytes_sent = r.read_pod<uint64_t>();
        jitter_ms = r.read_pod<double>();
        estimated_mos = r.read_pod<double>();
        trunk_id = r.read_string();
        tenant_id = r.read_string();
        codec = r.read_string();
        timestamp_ms = r.read_pod<int64_t>();
        client_id = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct GetIncomingCallsRequest {
    std::string trunk_id;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(trunk_id);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        trunk_id = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct IncomingCallInfo {
    std::string call_sid;
    std::string call_from;
    int64_t start_timestamp_ms;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(call_sid);
        w.write_string(call_from);
        w.write_pod<int64_t>(start_timestamp_ms);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        call_sid = r.read_string();
        call_from = r.read_string();
        start_timestamp_ms = r.read_pod<int64_t>();
        r.skip_to_envelope_end(_env);
    }
};

struct GetIncomingCallsResponse {
    std::vector<IncomingCallInfo> calls;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        r.skip_to_envelope_end(_env);
    }
};

struct AnswerIncomingCallRequest {
    std::string call_sid;
    std::string ai_websocket_url;
    std::string ai_quic_url;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(call_sid);
        w.write_string(ai_websocket_url);
        w.write_string(ai_quic_url);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        call_sid = r.read_string();
        ai_websocket_url = r.read_string();
        ai_quic_url = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct AnswerIncomingCallResponse {
    std::string call_sid;
    std::string status;
    std::string error_message;
    ErrorCode error_code;
    int64_t timestamp_ms;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(call_sid);
        w.write_string(status);
        w.write_string(error_message);
        w.write_pod<int32_t>(static_cast<int32_t>(error_code));
        w.write_pod<int64_t>(timestamp_ms);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        call_sid = r.read_string();
        status = r.read_string();
        error_message = r.read_string();
        error_code = static_cast<ErrorCode>(r.read_pod<int32_t>());
        timestamp_ms = r.read_pod<int64_t>();
        r.skip_to_envelope_end(_env);
    }
};

struct BucketInfo {
    std::string bucket_id;
    int32_t pending_count;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(bucket_id);
        w.write_pod<int32_t>(pending_count);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        bucket_id = r.read_string();
        pending_count = r.read_pod<int32_t>();
        r.skip_to_envelope_end(_env);
    }
};

struct ListBucketsResponse {
    std::vector<BucketInfo> buckets;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        r.skip_to_envelope_end(_env);
    }
};

struct BucketRequest {
    std::string bucket_id;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(bucket_id);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        bucket_id = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct BucketCallList {
    std::string call_sids;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(call_sids);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        call_sids = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct BucketActionRequest {
    std::string bucket_id;
    int32_t action;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(bucket_id);
        w.write_pod<int32_t>(action);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        bucket_id = r.read_string();
        action = r.read_pod<int32_t>();
        r.skip_to_envelope_end(_env);
    }
};

struct BucketActionResponse {
    int32_t processed_count;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_pod<int32_t>(processed_count);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        processed_count = r.read_pod<int32_t>();
        r.skip_to_envelope_end(_env);
    }
};

struct ExecuteDialplanRequest {
    std::string call_sid;
    DialplanAction action;
    std::string app_args;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(call_sid);
        w.write_pod<int32_t>(static_cast<int32_t>(action));
        w.write_string(app_args);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        call_sid = r.read_string();
        action = static_cast<DialplanAction>(r.read_pod<int32_t>());
        app_args = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct ExecuteDialplanResponse {
    std::string status;
    std::string error_message;
    ErrorCode error_code;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(status);
        w.write_string(error_message);
        w.write_pod<int32_t>(static_cast<int32_t>(error_code));
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        status = r.read_string();
        error_message = r.read_string();
        error_code = static_cast<ErrorCode>(r.read_pod<int32_t>());
        r.skip_to_envelope_end(_env);
    }
};

// 2026-05-18 — WT direct-media allocation (mirror of
// telequick/api/telequick_types.hh::AllocateWtRequest/Response).
// SDK calls this AFTER Originate has minted the call_sid; the response
// carries the runtime host:port + media_token the SDK uses to dial WT
// directly.
struct AllocateWtRequest {
    std::string call_sid;
    std::string agent_id;
    std::string tenant_id;
    std::string trunk_id;
    std::string realm;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(call_sid);
        w.write_string(agent_id);
        w.write_string(tenant_id);
        w.write_string(trunk_id);
        w.write_string(realm);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        call_sid  = r.read_string();
        agent_id  = r.read_string();
        tenant_id = r.read_string();
        trunk_id  = r.read_string();
        realm     = r.read_string();
        r.skip_to_envelope_end(_env);
    }
};

struct AllocateWtResponse {
    std::string host;
    uint16_t    port;
    std::string node_id;
    std::string media_token;
    std::string status;
    std::string error_message;
    ErrorCode   error_code;
    int64_t     timestamp_ms;

    void serialize(SerdeWriter& w) const {
        auto _env = w.begin_envelope(0, 0);
        w.write_string(host);
        w.write_pod<uint16_t>(port);
        w.write_string(node_id);
        w.write_string(media_token);
        w.write_string(status);
        w.write_string(error_message);
        w.write_pod<int32_t>(static_cast<int32_t>(error_code));
        w.write_pod<int64_t>(timestamp_ms);
        w.end_envelope(_env);
    }

    void deserialize(SerdeReader& r) {
        auto _env = r.read_envelope_header();
        host          = r.read_string();
        port          = r.read_pod<uint16_t>();
        node_id       = r.read_string();
        media_token   = r.read_string();
        status        = r.read_string();
        error_message = r.read_string();
        error_code    = static_cast<ErrorCode>(r.read_pod<int32_t>());
        timestamp_ms  = r.read_pod<int64_t>();
        r.skip_to_envelope_end(_env);
    }
};

} // namespace telequick::api
