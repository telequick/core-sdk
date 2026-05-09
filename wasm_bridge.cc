#include <emscripten/bind.h>
#include "api_models.h"

using namespace telequick_core;

using namespace emscripten;
using namespace telequick::api;

val rpc_originate_request(const OriginateRequest& req) {
    SerdeWriter w; req.serialize(w);
    const auto& b = w.buffer();
    uint32_t total_len = b.size() + 8;
   uint32_t method_id = 1430677891;
    std::vector<uint8_t> out_buf(total_len);
    std::memcpy(out_buf.data(), &total_len, 4);
    std::memcpy(out_buf.data() + 4, &method_id, 4);
    std::memcpy(out_buf.data() + 8, b.data(), b.size());
    val view = val(typed_memory_view(out_buf.size(), out_buf.data()));
    return val::global("Uint8Array").new_(view);
}
OriginateRequest deserialize_originate_request(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    OriginateRequest req; req.deserialize(r); return req;
}

val serialize_audio_frame(const AudioFrame& req) {
    SerdeWriter w; req.serialize(w);
    const auto& buf = w.buffer();
    val view = val(typed_memory_view(buf.size(), buf.data()));
    return val::global("Uint8Array").new_(view);
}
AudioFrame deserialize_audio_frame(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    AudioFrame req; req.deserialize(r); return req;
}

val rpc_empty(const Empty& req) {
    SerdeWriter w; req.serialize(w);
    const auto& b = w.buffer();
    uint32_t total_len = b.size() + 8;
   uint32_t method_id = 2624504207;
    std::vector<uint8_t> out_buf(total_len);
    std::memcpy(out_buf.data(), &total_len, 4);
    std::memcpy(out_buf.data() + 4, &method_id, 4);
    std::memcpy(out_buf.data() + 8, b.data(), b.size());
    val view = val(typed_memory_view(out_buf.size(), out_buf.data()));
    return val::global("Uint8Array").new_(view);
}
Empty deserialize_empty(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    Empty req; req.deserialize(r); return req;
}

val rpc_barge_request(const BargeRequest& req) {
    SerdeWriter w; req.serialize(w);
    const auto& b = w.buffer();
    uint32_t total_len = b.size() + 8;
   uint32_t method_id = 3854301714;
    std::vector<uint8_t> out_buf(total_len);
    std::memcpy(out_buf.data(), &total_len, 4);
    std::memcpy(out_buf.data() + 4, &method_id, 4);
    std::memcpy(out_buf.data() + 8, b.data(), b.size());
    val view = val(typed_memory_view(out_buf.size(), out_buf.data()));
    return val::global("Uint8Array").new_(view);
}
BargeRequest deserialize_barge_request(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    BargeRequest req; req.deserialize(r); return req;
}

val serialize_originate_response(const OriginateResponse& req) {
    SerdeWriter w; req.serialize(w);
    const auto& buf = w.buffer();
    val view = val(typed_memory_view(buf.size(), buf.data()));
    return val::global("Uint8Array").new_(view);
}
OriginateResponse deserialize_originate_response(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    OriginateResponse req; req.deserialize(r); return req;
}

val rpc_bulk_request(const BulkRequest& req) {
    SerdeWriter w; req.serialize(w);
    const auto& b = w.buffer();
    uint32_t total_len = b.size() + 8;
   uint32_t method_id = 721069100;
    std::vector<uint8_t> out_buf(total_len);
    std::memcpy(out_buf.data(), &total_len, 4);
    std::memcpy(out_buf.data() + 4, &method_id, 4);
    std::memcpy(out_buf.data() + 8, b.data(), b.size());
    val view = val(typed_memory_view(out_buf.size(), out_buf.data()));
    return val::global("Uint8Array").new_(view);
}
BulkRequest deserialize_bulk_request(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    BulkRequest req; req.deserialize(r); return req;
}

val serialize_bulk_response(const BulkResponse& req) {
    SerdeWriter w; req.serialize(w);
    const auto& buf = w.buffer();
    val view = val(typed_memory_view(buf.size(), buf.data()));
    return val::global("Uint8Array").new_(view);
}
BulkResponse deserialize_bulk_response(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    BulkResponse req; req.deserialize(r); return req;
}

val rpc_abort_bulk_request(const AbortBulkRequest& req) {
    SerdeWriter w; req.serialize(w);
    const auto& b = w.buffer();
    uint32_t total_len = b.size() + 8;
   uint32_t method_id = 3861915064;
    std::vector<uint8_t> out_buf(total_len);
    std::memcpy(out_buf.data(), &total_len, 4);
    std::memcpy(out_buf.data() + 4, &method_id, 4);
    std::memcpy(out_buf.data() + 8, b.data(), b.size());
    val view = val(typed_memory_view(out_buf.size(), out_buf.data()));
    return val::global("Uint8Array").new_(view);
}
AbortBulkRequest deserialize_abort_bulk_request(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    AbortBulkRequest req; req.deserialize(r); return req;
}

val rpc_terminate_request(const TerminateRequest& req) {
    SerdeWriter w; req.serialize(w);
    const auto& b = w.buffer();
    uint32_t total_len = b.size() + 8;
   uint32_t method_id = 3834253405;
    std::vector<uint8_t> out_buf(total_len);
    std::memcpy(out_buf.data(), &total_len, 4);
    std::memcpy(out_buf.data() + 4, &method_id, 4);
    std::memcpy(out_buf.data() + 8, b.data(), b.size());
    val view = val(typed_memory_view(out_buf.size(), out_buf.data()));
    return val::global("Uint8Array").new_(view);
}
TerminateRequest deserialize_terminate_request(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    TerminateRequest req; req.deserialize(r); return req;
}

val serialize_terminate_response(const TerminateResponse& req) {
    SerdeWriter w; req.serialize(w);
    const auto& buf = w.buffer();
    val view = val(typed_memory_view(buf.size(), buf.data()));
    return val::global("Uint8Array").new_(view);
}
TerminateResponse deserialize_terminate_response(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    TerminateResponse req; req.deserialize(r); return req;
}

val rpc_set_inbound_routing_request(const SetInboundRoutingRequest& req) {
    SerdeWriter w; req.serialize(w);
    const auto& b = w.buffer();
    uint32_t total_len = b.size() + 8;
   uint32_t method_id = 1933986897;
    std::vector<uint8_t> out_buf(total_len);
    std::memcpy(out_buf.data(), &total_len, 4);
    std::memcpy(out_buf.data() + 4, &method_id, 4);
    std::memcpy(out_buf.data() + 8, b.data(), b.size());
    val view = val(typed_memory_view(out_buf.size(), out_buf.data()));
    return val::global("Uint8Array").new_(view);
}
SetInboundRoutingRequest deserialize_set_inbound_routing_request(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    SetInboundRoutingRequest req; req.deserialize(r); return req;
}

val rpc_event_stream_request(const EventStreamRequest& req) {
    SerdeWriter w; req.serialize(w);
    const auto& b = w.buffer();
    uint32_t total_len = b.size() + 8;
   uint32_t method_id = 959835745;
    std::vector<uint8_t> out_buf(total_len);
    std::memcpy(out_buf.data(), &total_len, 4);
    std::memcpy(out_buf.data() + 4, &method_id, 4);
    std::memcpy(out_buf.data() + 8, b.data(), b.size());
    val view = val(typed_memory_view(out_buf.size(), out_buf.data()));
    return val::global("Uint8Array").new_(view);
}
EventStreamRequest deserialize_event_stream_request(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    EventStreamRequest req; req.deserialize(r); return req;
}

val serialize_call_event(const CallEvent& req) {
    SerdeWriter w; req.serialize(w);
    const auto& buf = w.buffer();
    val view = val(typed_memory_view(buf.size(), buf.data()));
    return val::global("Uint8Array").new_(view);
}
CallEvent deserialize_call_event(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    CallEvent req; req.deserialize(r); return req;
}

val rpc_get_incoming_calls_request(const GetIncomingCallsRequest& req) {
    SerdeWriter w; req.serialize(w);
    const auto& b = w.buffer();
    uint32_t total_len = b.size() + 8;
   uint32_t method_id = 1161946746;
    std::vector<uint8_t> out_buf(total_len);
    std::memcpy(out_buf.data(), &total_len, 4);
    std::memcpy(out_buf.data() + 4, &method_id, 4);
    std::memcpy(out_buf.data() + 8, b.data(), b.size());
    val view = val(typed_memory_view(out_buf.size(), out_buf.data()));
    return val::global("Uint8Array").new_(view);
}
GetIncomingCallsRequest deserialize_get_incoming_calls_request(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    GetIncomingCallsRequest req; req.deserialize(r); return req;
}

val serialize_incoming_call_info(const IncomingCallInfo& req) {
    SerdeWriter w; req.serialize(w);
    const auto& buf = w.buffer();
    val view = val(typed_memory_view(buf.size(), buf.data()));
    return val::global("Uint8Array").new_(view);
}
IncomingCallInfo deserialize_incoming_call_info(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    IncomingCallInfo req; req.deserialize(r); return req;
}

val serialize_get_incoming_calls_response(const GetIncomingCallsResponse& req) {
    SerdeWriter w; req.serialize(w);
    const auto& buf = w.buffer();
    val view = val(typed_memory_view(buf.size(), buf.data()));
    return val::global("Uint8Array").new_(view);
}
GetIncomingCallsResponse deserialize_get_incoming_calls_response(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    GetIncomingCallsResponse req; req.deserialize(r); return req;
}

val rpc_answer_incoming_call_request(const AnswerIncomingCallRequest& req) {
    SerdeWriter w; req.serialize(w);
    const auto& b = w.buffer();
    uint32_t total_len = b.size() + 8;
   uint32_t method_id = 2990157256;
    std::vector<uint8_t> out_buf(total_len);
    std::memcpy(out_buf.data(), &total_len, 4);
    std::memcpy(out_buf.data() + 4, &method_id, 4);
    std::memcpy(out_buf.data() + 8, b.data(), b.size());
    val view = val(typed_memory_view(out_buf.size(), out_buf.data()));
    return val::global("Uint8Array").new_(view);
}
AnswerIncomingCallRequest deserialize_answer_incoming_call_request(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    AnswerIncomingCallRequest req; req.deserialize(r); return req;
}

val serialize_answer_incoming_call_response(const AnswerIncomingCallResponse& req) {
    SerdeWriter w; req.serialize(w);
    const auto& buf = w.buffer();
    val view = val(typed_memory_view(buf.size(), buf.data()));
    return val::global("Uint8Array").new_(view);
}
AnswerIncomingCallResponse deserialize_answer_incoming_call_response(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    AnswerIncomingCallResponse req; req.deserialize(r); return req;
}

val serialize_bucket_info(const BucketInfo& req) {
    SerdeWriter w; req.serialize(w);
    const auto& buf = w.buffer();
    val view = val(typed_memory_view(buf.size(), buf.data()));
    return val::global("Uint8Array").new_(view);
}
BucketInfo deserialize_bucket_info(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    BucketInfo req; req.deserialize(r); return req;
}

val serialize_list_buckets_response(const ListBucketsResponse& req) {
    SerdeWriter w; req.serialize(w);
    const auto& buf = w.buffer();
    val view = val(typed_memory_view(buf.size(), buf.data()));
    return val::global("Uint8Array").new_(view);
}
ListBucketsResponse deserialize_list_buckets_response(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    ListBucketsResponse req; req.deserialize(r); return req;
}

val rpc_bucket_request(const BucketRequest& req) {
    SerdeWriter w; req.serialize(w);
    const auto& b = w.buffer();
    uint32_t total_len = b.size() + 8;
   uint32_t method_id = 1217351135;
    std::vector<uint8_t> out_buf(total_len);
    std::memcpy(out_buf.data(), &total_len, 4);
    std::memcpy(out_buf.data() + 4, &method_id, 4);
    std::memcpy(out_buf.data() + 8, b.data(), b.size());
    val view = val(typed_memory_view(out_buf.size(), out_buf.data()));
    return val::global("Uint8Array").new_(view);
}
BucketRequest deserialize_bucket_request(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    BucketRequest req; req.deserialize(r); return req;
}

val serialize_bucket_call_list(const BucketCallList& req) {
    SerdeWriter w; req.serialize(w);
    const auto& buf = w.buffer();
    val view = val(typed_memory_view(buf.size(), buf.data()));
    return val::global("Uint8Array").new_(view);
}
BucketCallList deserialize_bucket_call_list(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    BucketCallList req; req.deserialize(r); return req;
}

val rpc_bucket_action_request(const BucketActionRequest& req) {
    SerdeWriter w; req.serialize(w);
    const auto& b = w.buffer();
    uint32_t total_len = b.size() + 8;
   uint32_t method_id = 4030863293;
    std::vector<uint8_t> out_buf(total_len);
    std::memcpy(out_buf.data(), &total_len, 4);
    std::memcpy(out_buf.data() + 4, &method_id, 4);
    std::memcpy(out_buf.data() + 8, b.data(), b.size());
    val view = val(typed_memory_view(out_buf.size(), out_buf.data()));
    return val::global("Uint8Array").new_(view);
}
BucketActionRequest deserialize_bucket_action_request(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    BucketActionRequest req; req.deserialize(r); return req;
}

val serialize_bucket_action_response(const BucketActionResponse& req) {
    SerdeWriter w; req.serialize(w);
    const auto& buf = w.buffer();
    val view = val(typed_memory_view(buf.size(), buf.data()));
    return val::global("Uint8Array").new_(view);
}
BucketActionResponse deserialize_bucket_action_response(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    BucketActionResponse req; req.deserialize(r); return req;
}

val rpc_execute_dialplan_request(const ExecuteDialplanRequest& req) {
    SerdeWriter w; req.serialize(w);
    const auto& b = w.buffer();
    uint32_t total_len = b.size() + 8;
   uint32_t method_id = 80147304;
    std::vector<uint8_t> out_buf(total_len);
    std::memcpy(out_buf.data(), &total_len, 4);
    std::memcpy(out_buf.data() + 4, &method_id, 4);
    std::memcpy(out_buf.data() + 8, b.data(), b.size());
    val view = val(typed_memory_view(out_buf.size(), out_buf.data()));
    return val::global("Uint8Array").new_(view);
}
ExecuteDialplanRequest deserialize_execute_dialplan_request(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    ExecuteDialplanRequest req; req.deserialize(r); return req;
}

val serialize_execute_dialplan_response(const ExecuteDialplanResponse& req) {
    SerdeWriter w; req.serialize(w);
    const auto& buf = w.buffer();
    val view = val(typed_memory_view(buf.size(), buf.data()));
    return val::global("Uint8Array").new_(view);
}
ExecuteDialplanResponse deserialize_execute_dialplan_response(const val& bytes_val) {
    std::vector<uint8_t> vec = convertJSArrayToNumberVector<uint8_t>(bytes_val);
    SerdeReader r(vec.data(), vec.size());
    ExecuteDialplanResponse req; req.deserialize(r); return req;
}

EMSCRIPTEN_BINDINGS(telequick_module) {
    enum_<ErrorCode>("ErrorCode")
        .value("SUCCESS", ErrorCode::SUCCESS)
        .value("ERR_INVALID_TRUNK", ErrorCode::ERR_INVALID_TRUNK)
        .value("ERR_INVALID_DESTINATION", ErrorCode::ERR_INVALID_DESTINATION)
        .value("ERR_RATE_LIMITED", ErrorCode::ERR_RATE_LIMITED)
        .value("ERR_CIRCUIT_BREAKER", ErrorCode::ERR_CIRCUIT_BREAKER)
        .value("ERR_INTERNAL_ERROR", ErrorCode::ERR_INTERNAL_ERROR)
        .value("ERR_VALIDATION_FAILED", ErrorCode::ERR_VALIDATION_FAILED)
        .value("ERR_UNAUTHORIZED", ErrorCode::ERR_UNAUTHORIZED)
;
    enum_<DialplanAction>("DialplanAction")
        .value("HANGUP", DialplanAction::HANGUP)
        .value("PARK", DialplanAction::PARK)
        .value("MUSIC_ON_HOLD", DialplanAction::MUSIC_ON_HOLD)
        .value("PLAYBACK", DialplanAction::PLAYBACK)
        .value("UNPARK_AND_BRIDGE", DialplanAction::UNPARK_AND_BRIDGE)
        .value("ANSWER", DialplanAction::ANSWER)
        .value("AI_BIDIRECTIONAL_STREAM", DialplanAction::AI_BIDIRECTIONAL_STREAM)
        // PR4 — call-control verbs reachable via ExecuteDialplan, mirroring
        // the gateway-side enum in telequick/api/telequick_types.hh.
        // Browser-side WASM consumers can now address Transfer/Hold/Unhold/
        // Mute/Unmute/SendDtmf without falling back to numeric literals.
        .value("TRANSFER", DialplanAction::TRANSFER)
        .value("MUTE", DialplanAction::MUTE)
        .value("UNMUTE", DialplanAction::UNMUTE)
        .value("HOLD", DialplanAction::HOLD)
        .value("UNHOLD", DialplanAction::UNHOLD)
        .value("SEND_DTMF", DialplanAction::SEND_DTMF)
;
    enum_<InboundRule>("InboundRule")
        .value("REJECT", InboundRule::REJECT)
        .value("PLAY_AND_HANGUP", InboundRule::PLAY_AND_HANGUP)
        .value("NOTIFY_AND_HANGUP", InboundRule::NOTIFY_AND_HANGUP)
        .value("HANDLE_AI", InboundRule::HANDLE_AI)
;
    enum_<EventType>("EventType")
        .value("UNKNOWN", EventType::UNKNOWN)
        .value("CHANNEL_CREATE", EventType::CHANNEL_CREATE)
        .value("CHANNEL_ANSWER", EventType::CHANNEL_ANSWER)
        .value("CHANNEL_HANGUP_COMPLETE", EventType::CHANNEL_HANGUP_COMPLETE)
        .value("CHANNEL_HOLD", EventType::CHANNEL_HOLD)
        .value("CHANNEL_RESUME", EventType::CHANNEL_RESUME)
;
    enum_<MethodID>("MethodID")
        .value("ORIGINATE", MethodID::ORIGINATE)
        .value("ORIGINATE_BULK", MethodID::ORIGINATE_BULK)
        .value("ABORT_BULK", MethodID::ABORT_BULK)
        .value("TERMINATE", MethodID::TERMINATE)
        .value("STREAM_EVENTS", MethodID::STREAM_EVENTS)
        .value("SET_INBOUND_ROUTING", MethodID::SET_INBOUND_ROUTING)
        .value("GET_INCOMING_CALLS", MethodID::GET_INCOMING_CALLS)
        .value("ANSWER_INCOMING_CALL", MethodID::ANSWER_INCOMING_CALL)
        .value("GET_ACTIVE_BUCKETS", MethodID::GET_ACTIVE_BUCKETS)
        .value("GET_BUCKET_CALLS", MethodID::GET_BUCKET_CALLS)
        .value("EXECUTE_BUCKET_ACTION", MethodID::EXECUTE_BUCKET_ACTION)
        .value("EXECUTE_DIALPLAN", MethodID::EXECUTE_DIALPLAN)
        .value("BARGE", MethodID::BARGE)
        .value("AUDIO_FRAME", MethodID::AUDIO_FRAME)
;
    class_<OriginateRequest>("OriginateRequest")
        .constructor<>()
        .property("trunk_id", &OriginateRequest::trunk_id)
        .property("to", &OriginateRequest::to)
        .property("call_from", &OriginateRequest::call_from)
        .property("ai_websocket_url", &OriginateRequest::ai_websocket_url)
        .property("ai_quic_url", &OriginateRequest::ai_quic_url)
        .property("tenant_id", &OriginateRequest::tenant_id)
        .property("max_duration_ms", &OriginateRequest::max_duration_ms)
        .property("call_sid", &OriginateRequest::call_sid)
        .property("default_app", &OriginateRequest::default_app)
        .property("default_app_args", &OriginateRequest::default_app_args)
        .property("auto_barge_in", &OriginateRequest::auto_barge_in)
        .property("barge_in_patience_ms", &OriginateRequest::barge_in_patience_ms)
        .property("client_id", &OriginateRequest::client_id)
;
    function("rpc_originate_request", &rpc_originate_request);
    function("deserialize_originate_request", &deserialize_originate_request);
    class_<AudioFrame>("AudioFrame")
        .constructor<>()
        .property("call_sid", &AudioFrame::call_sid)
        .property("payload", &AudioFrame::payload)
        .property("codec", &AudioFrame::codec)
        .property("sequence_number", &AudioFrame::sequence_number)
        .property("end_of_stream", &AudioFrame::end_of_stream)
;
    function("serialize_audio_frame", &serialize_audio_frame);
    function("deserialize_audio_frame", &deserialize_audio_frame);
    class_<Empty>("Empty")
        .constructor<>()
;
    function("rpc_empty", &rpc_empty);
    function("deserialize_empty", &deserialize_empty);
    class_<BargeRequest>("BargeRequest")
        .constructor<>()
        .property("call_sid", &BargeRequest::call_sid)
;
    function("rpc_barge_request", &rpc_barge_request);
    function("deserialize_barge_request", &deserialize_barge_request);
    class_<OriginateResponse>("OriginateResponse")
        .constructor<>()
        .property("call_sid", &OriginateResponse::call_sid)
        .property("status", &OriginateResponse::status)
        .property("error_message", &OriginateResponse::error_message)
        .property("error_code", &OriginateResponse::error_code)
        .property("timestamp_ms", &OriginateResponse::timestamp_ms)
;
    function("serialize_originate_response", &serialize_originate_response);
    function("deserialize_originate_response", &deserialize_originate_response);
    class_<BulkRequest>("BulkRequest")
        .constructor<>()
        .property("csv_url", &BulkRequest::csv_url)
        .property("template_trunk_id", &BulkRequest::template_trunk_id)
        .property("template_to", &BulkRequest::template_to)
        .property("template_call_from", &BulkRequest::template_call_from)
        .property("template_ai_websocket_url", &BulkRequest::template_ai_websocket_url)
        .property("template_ai_quic_url", &BulkRequest::template_ai_quic_url)
        .property("template_tenant_id", &BulkRequest::template_tenant_id)
        .property("template_max_duration_ms", &BulkRequest::template_max_duration_ms)
        .property("template_default_app", &BulkRequest::template_default_app)
        .property("template_default_app_args", &BulkRequest::template_default_app_args)
        .property("calls_per_second", &BulkRequest::calls_per_second)
        .property("max_concurrent_calls", &BulkRequest::max_concurrent_calls)
        .property("campaign_id", &BulkRequest::campaign_id)
;
    function("rpc_bulk_request", &rpc_bulk_request);
    function("deserialize_bulk_request", &deserialize_bulk_request);
    class_<BulkResponse>("BulkResponse")
        .constructor<>()
        .property("status", &BulkResponse::status)
        .property("loaded_numbers", &BulkResponse::loaded_numbers)
;
    function("serialize_bulk_response", &serialize_bulk_response);
    function("deserialize_bulk_response", &deserialize_bulk_response);
    class_<AbortBulkRequest>("AbortBulkRequest")
        .constructor<>()
        .property("campaign_id", &AbortBulkRequest::campaign_id)
;
    function("rpc_abort_bulk_request", &rpc_abort_bulk_request);
    function("deserialize_abort_bulk_request", &deserialize_abort_bulk_request);
    class_<TerminateRequest>("TerminateRequest")
        .constructor<>()
        .property("call_sid", &TerminateRequest::call_sid)
;
    function("rpc_terminate_request", &rpc_terminate_request);
    function("deserialize_terminate_request", &deserialize_terminate_request);
    class_<TerminateResponse>("TerminateResponse")
        .constructor<>()
        .property("call_sid", &TerminateResponse::call_sid)
        .property("status", &TerminateResponse::status)
        .property("error_message", &TerminateResponse::error_message)
        .property("error_code", &TerminateResponse::error_code)
        .property("timestamp_ms", &TerminateResponse::timestamp_ms)
;
    function("serialize_terminate_response", &serialize_terminate_response);
    function("deserialize_terminate_response", &deserialize_terminate_response);
    class_<SetInboundRoutingRequest>("SetInboundRoutingRequest")
        .constructor<>()
        .property("trunk_id", &SetInboundRoutingRequest::trunk_id)
        .property("rule", &SetInboundRoutingRequest::rule)
        .property("audio_url", &SetInboundRoutingRequest::audio_url)
        .property("webhook_url", &SetInboundRoutingRequest::webhook_url)
        .property("ai_websocket_url", &SetInboundRoutingRequest::ai_websocket_url)
        .property("ai_quic_url", &SetInboundRoutingRequest::ai_quic_url)
;
    function("rpc_set_inbound_routing_request", &rpc_set_inbound_routing_request);
    function("deserialize_set_inbound_routing_request", &deserialize_set_inbound_routing_request);
    class_<EventStreamRequest>("EventStreamRequest")
        .constructor<>()
        .property("client_id", &EventStreamRequest::client_id)
;
    function("rpc_event_stream_request", &rpc_event_stream_request);
    function("deserialize_event_stream_request", &deserialize_event_stream_request);
    class_<CallEvent>("CallEvent")
        .constructor<>()
        .property("call_sid", &CallEvent::call_sid)
        .property("event_type", &CallEvent::event_type)
        .property("status", &CallEvent::status)
        .property("start_timestamp_ms", &CallEvent::start_timestamp_ms)
        .property("q850_cause", &CallEvent::q850_cause)
        .property("recording_url", &CallEvent::recording_url)
        .property("duration_seconds", &CallEvent::duration_seconds)
        .property("answer_timestamp_ms", &CallEvent::answer_timestamp_ms)
        .property("end_timestamp_ms", &CallEvent::end_timestamp_ms)
        .property("packets_sent", &CallEvent::packets_sent)
        .property("packets_received", &CallEvent::packets_received)
        .property("packets_lost", &CallEvent::packets_lost)
        .property("bytes_sent", &CallEvent::bytes_sent)
        .property("jitter_ms", &CallEvent::jitter_ms)
        .property("estimated_mos", &CallEvent::estimated_mos)
        .property("trunk_id", &CallEvent::trunk_id)
        .property("tenant_id", &CallEvent::tenant_id)
        .property("codec", &CallEvent::codec)
        .property("timestamp_ms", &CallEvent::timestamp_ms)
        .property("client_id", &CallEvent::client_id)
;
    function("serialize_call_event", &serialize_call_event);
    function("deserialize_call_event", &deserialize_call_event);
    class_<GetIncomingCallsRequest>("GetIncomingCallsRequest")
        .constructor<>()
        .property("trunk_id", &GetIncomingCallsRequest::trunk_id)
;
    function("rpc_get_incoming_calls_request", &rpc_get_incoming_calls_request);
    function("deserialize_get_incoming_calls_request", &deserialize_get_incoming_calls_request);
    class_<IncomingCallInfo>("IncomingCallInfo")
        .constructor<>()
        .property("call_sid", &IncomingCallInfo::call_sid)
        .property("call_from", &IncomingCallInfo::call_from)
        .property("start_timestamp_ms", &IncomingCallInfo::start_timestamp_ms)
;
    function("serialize_incoming_call_info", &serialize_incoming_call_info);
    function("deserialize_incoming_call_info", &deserialize_incoming_call_info);
    class_<GetIncomingCallsResponse>("GetIncomingCallsResponse")
        .constructor<>()
;
    function("serialize_get_incoming_calls_response", &serialize_get_incoming_calls_response);
    function("deserialize_get_incoming_calls_response", &deserialize_get_incoming_calls_response);
    class_<AnswerIncomingCallRequest>("AnswerIncomingCallRequest")
        .constructor<>()
        .property("call_sid", &AnswerIncomingCallRequest::call_sid)
        .property("ai_websocket_url", &AnswerIncomingCallRequest::ai_websocket_url)
        .property("ai_quic_url", &AnswerIncomingCallRequest::ai_quic_url)
;
    function("rpc_answer_incoming_call_request", &rpc_answer_incoming_call_request);
    function("deserialize_answer_incoming_call_request", &deserialize_answer_incoming_call_request);
    class_<AnswerIncomingCallResponse>("AnswerIncomingCallResponse")
        .constructor<>()
        .property("call_sid", &AnswerIncomingCallResponse::call_sid)
        .property("status", &AnswerIncomingCallResponse::status)
        .property("error_message", &AnswerIncomingCallResponse::error_message)
        .property("error_code", &AnswerIncomingCallResponse::error_code)
        .property("timestamp_ms", &AnswerIncomingCallResponse::timestamp_ms)
;
    function("serialize_answer_incoming_call_response", &serialize_answer_incoming_call_response);
    function("deserialize_answer_incoming_call_response", &deserialize_answer_incoming_call_response);
    class_<BucketInfo>("BucketInfo")
        .constructor<>()
        .property("bucket_id", &BucketInfo::bucket_id)
        .property("pending_count", &BucketInfo::pending_count)
;
    function("serialize_bucket_info", &serialize_bucket_info);
    function("deserialize_bucket_info", &deserialize_bucket_info);
    class_<ListBucketsResponse>("ListBucketsResponse")
        .constructor<>()
;
    function("serialize_list_buckets_response", &serialize_list_buckets_response);
    function("deserialize_list_buckets_response", &deserialize_list_buckets_response);
    class_<BucketRequest>("BucketRequest")
        .constructor<>()
        .property("bucket_id", &BucketRequest::bucket_id)
;
    function("rpc_bucket_request", &rpc_bucket_request);
    function("deserialize_bucket_request", &deserialize_bucket_request);
    class_<BucketCallList>("BucketCallList")
        .constructor<>()
        .property("call_sids", &BucketCallList::call_sids)
;
    function("serialize_bucket_call_list", &serialize_bucket_call_list);
    function("deserialize_bucket_call_list", &deserialize_bucket_call_list);
    class_<BucketActionRequest>("BucketActionRequest")
        .constructor<>()
        .property("bucket_id", &BucketActionRequest::bucket_id)
        .property("action", &BucketActionRequest::action)
;
    function("rpc_bucket_action_request", &rpc_bucket_action_request);
    function("deserialize_bucket_action_request", &deserialize_bucket_action_request);
    class_<BucketActionResponse>("BucketActionResponse")
        .constructor<>()
        .property("processed_count", &BucketActionResponse::processed_count)
;
    function("serialize_bucket_action_response", &serialize_bucket_action_response);
    function("deserialize_bucket_action_response", &deserialize_bucket_action_response);
    class_<ExecuteDialplanRequest>("ExecuteDialplanRequest")
        .constructor<>()
        .property("call_sid", &ExecuteDialplanRequest::call_sid)
        .property("action", &ExecuteDialplanRequest::action)
        .property("app_args", &ExecuteDialplanRequest::app_args)
;
    function("rpc_execute_dialplan_request", &rpc_execute_dialplan_request);
    function("deserialize_execute_dialplan_request", &deserialize_execute_dialplan_request);
    class_<ExecuteDialplanResponse>("ExecuteDialplanResponse")
        .constructor<>()
        .property("status", &ExecuteDialplanResponse::status)
        .property("error_message", &ExecuteDialplanResponse::error_message)
        .property("error_code", &ExecuteDialplanResponse::error_code)
;
    function("serialize_execute_dialplan_response", &serialize_execute_dialplan_response);
    function("deserialize_execute_dialplan_response", &deserialize_execute_dialplan_response);
}
