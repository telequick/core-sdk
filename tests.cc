#include "api_models.h"
#include <iostream>
#include <cassert>

using namespace telequick_core;

using namespace telequick::api;

void test_originate_request() {
    OriginateRequest req1;
    OriginateRequest req2;
    req1.trunk_id = "test_value_trunk_id";
    req1.to = "test_value_to";
    req1.call_from = "test_value_call_from";
    req1.ai_websocket_url = "test_value_ai_websocket_url";
    req1.ai_quic_url = "test_value_ai_quic_url";
    req1.tenant_id = "test_value_tenant_id";
    req1.max_duration_ms = 42;
    req1.call_sid = "test_value_call_sid";
    req1.default_app = static_cast<DialplanAction>(0);
    req1.default_app_args = "test_value_default_app_args";
    req1.auto_barge_in = true;
    req1.barge_in_patience_ms = 42;
    req1.client_id = "test_value_client_id";
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.trunk_id == req2.trunk_id);
    assert(req1.to == req2.to);
    assert(req1.call_from == req2.call_from);
    assert(req1.ai_websocket_url == req2.ai_websocket_url);
    assert(req1.ai_quic_url == req2.ai_quic_url);
    assert(req1.tenant_id == req2.tenant_id);
    assert(req1.max_duration_ms == req2.max_duration_ms);
    assert(req1.call_sid == req2.call_sid);
    assert(req1.default_app == req2.default_app);
    assert(req1.default_app_args == req2.default_app_args);
    assert(req1.auto_barge_in == req2.auto_barge_in);
    assert(req1.barge_in_patience_ms == req2.barge_in_patience_ms);
    assert(req1.client_id == req2.client_id);
    std::cout << "test_originate_request PASSED" << std::endl;
}

void test_audio_frame() {
    AudioFrame req1;
    AudioFrame req2;
    req1.call_sid = "test_value_call_sid";
    req1.payload = "test_value_payload";
    req1.codec = "test_value_codec";
    req1.sequence_number = 42;
    req1.end_of_stream = true;
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.call_sid == req2.call_sid);
    assert(req1.payload == req2.payload);
    assert(req1.codec == req2.codec);
    assert(req1.sequence_number == req2.sequence_number);
    assert(req1.end_of_stream == req2.end_of_stream);
    std::cout << "test_audio_frame PASSED" << std::endl;
}

void test_empty() {
    Empty req1;
    Empty req2;
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    std::cout << "test_empty PASSED" << std::endl;
}

void test_barge_request() {
    BargeRequest req1;
    BargeRequest req2;
    req1.call_sid = "test_value_call_sid";
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.call_sid == req2.call_sid);
    std::cout << "test_barge_request PASSED" << std::endl;
}

void test_originate_response() {
    OriginateResponse req1;
    OriginateResponse req2;
    req1.call_sid = "test_value_call_sid";
    req1.status = "test_value_status";
    req1.error_message = "test_value_error_message";
    req1.error_code = static_cast<ErrorCode>(0);
    req1.timestamp_ms = 42;
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.call_sid == req2.call_sid);
    assert(req1.status == req2.status);
    assert(req1.error_message == req2.error_message);
    assert(req1.error_code == req2.error_code);
    assert(req1.timestamp_ms == req2.timestamp_ms);
    std::cout << "test_originate_response PASSED" << std::endl;
}

void test_bulk_request() {
    BulkRequest req1;
    BulkRequest req2;
    req1.csv_url = "test_value_csv_url";
    req1.template_trunk_id = "test_value_template_trunk_id";
    req1.template_to = "test_value_template_to";
    req1.template_call_from = "test_value_template_call_from";
    req1.template_ai_websocket_url = "test_value_template_ai_websocket_url";
    req1.template_ai_quic_url = "test_value_template_ai_quic_url";
    req1.template_tenant_id = "test_value_template_tenant_id";
    req1.template_max_duration_ms = 42;
    req1.template_default_app = static_cast<DialplanAction>(0);
    req1.template_default_app_args = "test_value_template_default_app_args";
    req1.calls_per_second = 42;
    req1.max_concurrent_calls = 42;
    req1.campaign_id = "test_value_campaign_id";
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.csv_url == req2.csv_url);
    assert(req1.template_trunk_id == req2.template_trunk_id);
    assert(req1.template_to == req2.template_to);
    assert(req1.template_call_from == req2.template_call_from);
    assert(req1.template_ai_websocket_url == req2.template_ai_websocket_url);
    assert(req1.template_ai_quic_url == req2.template_ai_quic_url);
    assert(req1.template_tenant_id == req2.template_tenant_id);
    assert(req1.template_max_duration_ms == req2.template_max_duration_ms);
    assert(req1.template_default_app == req2.template_default_app);
    assert(req1.template_default_app_args == req2.template_default_app_args);
    assert(req1.calls_per_second == req2.calls_per_second);
    assert(req1.max_concurrent_calls == req2.max_concurrent_calls);
    assert(req1.campaign_id == req2.campaign_id);
    std::cout << "test_bulk_request PASSED" << std::endl;
}

void test_bulk_response() {
    BulkResponse req1;
    BulkResponse req2;
    req1.status = "test_value_status";
    req1.loaded_numbers = 42;
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.status == req2.status);
    assert(req1.loaded_numbers == req2.loaded_numbers);
    std::cout << "test_bulk_response PASSED" << std::endl;
}

void test_abort_bulk_request() {
    AbortBulkRequest req1;
    AbortBulkRequest req2;
    req1.campaign_id = "test_value_campaign_id";
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.campaign_id == req2.campaign_id);
    std::cout << "test_abort_bulk_request PASSED" << std::endl;
}

void test_terminate_request() {
    TerminateRequest req1;
    TerminateRequest req2;
    req1.call_sid = "test_value_call_sid";
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.call_sid == req2.call_sid);
    std::cout << "test_terminate_request PASSED" << std::endl;
}

void test_terminate_response() {
    TerminateResponse req1;
    TerminateResponse req2;
    req1.call_sid = "test_value_call_sid";
    req1.status = "test_value_status";
    req1.error_message = "test_value_error_message";
    req1.error_code = static_cast<ErrorCode>(0);
    req1.timestamp_ms = 42;
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.call_sid == req2.call_sid);
    assert(req1.status == req2.status);
    assert(req1.error_message == req2.error_message);
    assert(req1.error_code == req2.error_code);
    assert(req1.timestamp_ms == req2.timestamp_ms);
    std::cout << "test_terminate_response PASSED" << std::endl;
}

void test_set_inbound_routing_request() {
    SetInboundRoutingRequest req1;
    SetInboundRoutingRequest req2;
    req1.trunk_id = "test_value_trunk_id";
    req1.rule = static_cast<InboundRule>(0);
    req1.audio_url = "test_value_audio_url";
    req1.webhook_url = "test_value_webhook_url";
    req1.ai_websocket_url = "test_value_ai_websocket_url";
    req1.ai_quic_url = "test_value_ai_quic_url";
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.trunk_id == req2.trunk_id);
    assert(req1.rule == req2.rule);
    assert(req1.audio_url == req2.audio_url);
    assert(req1.webhook_url == req2.webhook_url);
    assert(req1.ai_websocket_url == req2.ai_websocket_url);
    assert(req1.ai_quic_url == req2.ai_quic_url);
    std::cout << "test_set_inbound_routing_request PASSED" << std::endl;
}

void test_event_stream_request() {
    EventStreamRequest req1;
    EventStreamRequest req2;
    req1.client_id = "test_value_client_id";
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.client_id == req2.client_id);
    std::cout << "test_event_stream_request PASSED" << std::endl;
}

void test_call_event() {
    CallEvent req1;
    CallEvent req2;
    req1.call_sid = "test_value_call_sid";
    req1.event_type = static_cast<EventType>(0);
    req1.status = "test_value_status";
    req1.start_timestamp_ms = 42;
    req1.q850_cause = 42;
    req1.recording_url = "test_value_recording_url";
    req1.duration_seconds = 42;
    req1.answer_timestamp_ms = 42;
    req1.end_timestamp_ms = 42;
    req1.packets_sent = 42;
    req1.packets_received = 42;
    req1.packets_lost = 42;
    req1.bytes_sent = 42;
    req1.jitter_ms = 42;
    req1.estimated_mos = 42;
    req1.trunk_id = "test_value_trunk_id";
    req1.tenant_id = "test_value_tenant_id";
    req1.codec = "test_value_codec";
    req1.timestamp_ms = 42;
    req1.client_id = "test_value_client_id";
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.call_sid == req2.call_sid);
    assert(req1.event_type == req2.event_type);
    assert(req1.status == req2.status);
    assert(req1.start_timestamp_ms == req2.start_timestamp_ms);
    assert(req1.q850_cause == req2.q850_cause);
    assert(req1.recording_url == req2.recording_url);
    assert(req1.duration_seconds == req2.duration_seconds);
    assert(req1.answer_timestamp_ms == req2.answer_timestamp_ms);
    assert(req1.end_timestamp_ms == req2.end_timestamp_ms);
    assert(req1.packets_sent == req2.packets_sent);
    assert(req1.packets_received == req2.packets_received);
    assert(req1.packets_lost == req2.packets_lost);
    assert(req1.bytes_sent == req2.bytes_sent);
    assert(req1.jitter_ms == req2.jitter_ms);
    assert(req1.estimated_mos == req2.estimated_mos);
    assert(req1.trunk_id == req2.trunk_id);
    assert(req1.tenant_id == req2.tenant_id);
    assert(req1.codec == req2.codec);
    assert(req1.timestamp_ms == req2.timestamp_ms);
    assert(req1.client_id == req2.client_id);
    std::cout << "test_call_event PASSED" << std::endl;
}

void test_get_incoming_calls_request() {
    GetIncomingCallsRequest req1;
    GetIncomingCallsRequest req2;
    req1.trunk_id = "test_value_trunk_id";
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.trunk_id == req2.trunk_id);
    std::cout << "test_get_incoming_calls_request PASSED" << std::endl;
}

void test_incoming_call_info() {
    IncomingCallInfo req1;
    IncomingCallInfo req2;
    req1.call_sid = "test_value_call_sid";
    req1.call_from = "test_value_call_from";
    req1.start_timestamp_ms = 42;
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.call_sid == req2.call_sid);
    assert(req1.call_from == req2.call_from);
    assert(req1.start_timestamp_ms == req2.start_timestamp_ms);
    std::cout << "test_incoming_call_info PASSED" << std::endl;
}

void test_get_incoming_calls_response() {
    GetIncomingCallsResponse req1;
    GetIncomingCallsResponse req2;
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    std::cout << "test_get_incoming_calls_response PASSED" << std::endl;
}

void test_answer_incoming_call_request() {
    AnswerIncomingCallRequest req1;
    AnswerIncomingCallRequest req2;
    req1.call_sid = "test_value_call_sid";
    req1.ai_websocket_url = "test_value_ai_websocket_url";
    req1.ai_quic_url = "test_value_ai_quic_url";
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.call_sid == req2.call_sid);
    assert(req1.ai_websocket_url == req2.ai_websocket_url);
    assert(req1.ai_quic_url == req2.ai_quic_url);
    std::cout << "test_answer_incoming_call_request PASSED" << std::endl;
}

void test_answer_incoming_call_response() {
    AnswerIncomingCallResponse req1;
    AnswerIncomingCallResponse req2;
    req1.call_sid = "test_value_call_sid";
    req1.status = "test_value_status";
    req1.error_message = "test_value_error_message";
    req1.error_code = static_cast<ErrorCode>(0);
    req1.timestamp_ms = 42;
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.call_sid == req2.call_sid);
    assert(req1.status == req2.status);
    assert(req1.error_message == req2.error_message);
    assert(req1.error_code == req2.error_code);
    assert(req1.timestamp_ms == req2.timestamp_ms);
    std::cout << "test_answer_incoming_call_response PASSED" << std::endl;
}

void test_bucket_info() {
    BucketInfo req1;
    BucketInfo req2;
    req1.bucket_id = "test_value_bucket_id";
    req1.pending_count = 42;
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.bucket_id == req2.bucket_id);
    assert(req1.pending_count == req2.pending_count);
    std::cout << "test_bucket_info PASSED" << std::endl;
}

void test_list_buckets_response() {
    ListBucketsResponse req1;
    ListBucketsResponse req2;
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    std::cout << "test_list_buckets_response PASSED" << std::endl;
}

void test_bucket_request() {
    BucketRequest req1;
    BucketRequest req2;
    req1.bucket_id = "test_value_bucket_id";
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.bucket_id == req2.bucket_id);
    std::cout << "test_bucket_request PASSED" << std::endl;
}

void test_bucket_call_list() {
    BucketCallList req1;
    BucketCallList req2;
    req1.call_sids = "test_value_call_sids";
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.call_sids == req2.call_sids);
    std::cout << "test_bucket_call_list PASSED" << std::endl;
}

void test_bucket_action_request() {
    BucketActionRequest req1;
    BucketActionRequest req2;
    req1.bucket_id = "test_value_bucket_id";
    req1.action = 42;
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.bucket_id == req2.bucket_id);
    assert(req1.action == req2.action);
    std::cout << "test_bucket_action_request PASSED" << std::endl;
}

void test_bucket_action_response() {
    BucketActionResponse req1;
    BucketActionResponse req2;
    req1.processed_count = 42;
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.processed_count == req2.processed_count);
    std::cout << "test_bucket_action_response PASSED" << std::endl;
}

void test_execute_dialplan_request() {
    ExecuteDialplanRequest req1;
    ExecuteDialplanRequest req2;
    req1.call_sid = "test_value_call_sid";
    req1.action = static_cast<DialplanAction>(0);
    req1.app_args = "test_value_app_args";
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.call_sid == req2.call_sid);
    assert(req1.action == req2.action);
    assert(req1.app_args == req2.app_args);
    std::cout << "test_execute_dialplan_request PASSED" << std::endl;
}

void test_execute_dialplan_response() {
    ExecuteDialplanResponse req1;
    ExecuteDialplanResponse req2;
    req1.status = "test_value_status";
    req1.error_message = "test_value_error_message";
    req1.error_code = static_cast<ErrorCode>(0);
    SerdeWriter writer; req1.serialize(writer);
    auto buf = writer.buffer();
    SerdeReader reader(buf.data(), buf.size());
    req2.deserialize(reader);
    assert(req1.status == req2.status);
    assert(req1.error_message == req2.error_message);
    assert(req1.error_code == req2.error_code);
    std::cout << "test_execute_dialplan_response PASSED" << std::endl;
}

int main() {
    test_originate_request();
    test_audio_frame();
    test_empty();
    test_barge_request();
    test_originate_response();
    test_bulk_request();
    test_bulk_response();
    test_abort_bulk_request();
    test_terminate_request();
    test_terminate_response();
    test_set_inbound_routing_request();
    test_event_stream_request();
    test_call_event();
    test_get_incoming_calls_request();
    test_incoming_call_info();
    test_get_incoming_calls_response();
    test_answer_incoming_call_request();
    test_answer_incoming_call_response();
    test_bucket_info();
    test_list_buckets_response();
    test_bucket_request();
    test_bucket_call_list();
    test_bucket_action_request();
    test_bucket_action_response();
    test_execute_dialplan_request();
    test_execute_dialplan_response();
    std::cout << "All Serde tests passed successfully." << std::endl;
    return 0;
}