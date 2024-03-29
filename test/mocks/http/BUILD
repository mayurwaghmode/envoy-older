load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_mock",
    "envoy_cc_test",
    "envoy_package",
)

licenses(["notice"])  # Apache 2

envoy_package()

envoy_cc_mock(
    name = "alternate_protocols_cache_mocks",
    srcs = ["alternate_protocols_cache.cc"],
    hdrs = ["alternate_protocols_cache.h"],
    deps = [
        "//envoy/http:alternate_protocols_cache_interface",
    ],
)

envoy_cc_mock(
    name = "api_listener_mocks",
    srcs = ["api_listener.cc"],
    hdrs = ["api_listener.h"],
    deps = [
        "//envoy/http:api_listener_interface",
    ],
)

envoy_cc_mock(
    name = "conn_pool_mocks",
    srcs = ["conn_pool.cc"],
    hdrs = ["conn_pool.h"],
    deps = [
        "//envoy/http:conn_pool_interface",
        "//test/mocks:common_lib",
        "//test/mocks/upstream:host_mocks",
    ],
)

envoy_cc_mock(
    name = "http_mocks",
    srcs = ["mocks.cc"],
    hdrs = ["mocks.h"],
    external_deps = [
        "abseil_strings",
    ],
    deps = [
        ":conn_pool_mocks",
        ":stream_decoder_mock",
        ":stream_encoder_mock",
        ":stream_mock",
        "//envoy/access_log:access_log_interface",
        "//envoy/buffer:buffer_interface",
        "//envoy/event:dispatcher_interface",
        "//envoy/http:async_client_interface",
        "//envoy/http:codec_interface",
        "//envoy/http:conn_pool_interface",
        "//envoy/http:filter_interface",
        "//envoy/ssl:connection_interface",
        "//envoy/tracing:http_tracer_interface",
        "//source/common/http:conn_manager_config_interface",
        "//source/common/http:filter_manager_lib",
        "//source/common/http:header_map_lib",
        "//test/mocks/event:event_mocks",
        "//test/mocks/router:router_mocks",
        "//test/mocks/stream_info:stream_info_mocks",
        "//test/mocks/tracing:tracing_mocks",
        "//test/mocks/upstream:host_mocks",
    ],
)

envoy_cc_mock(
    name = "stream_mock",
    srcs = ["stream.cc"],
    hdrs = ["stream.h"],
    deps = [
        "//envoy/http:codec_interface",
    ],
)

envoy_cc_mock(
    name = "stateful_session_mock",
    srcs = ["stateful_session.cc"],
    hdrs = ["stateful_session.h"],
    deps = [
        "//envoy/http:stateful_session_interface",
    ],
)

envoy_cc_mock(
    name = "stream_decoder_mock",
    srcs = ["stream_decoder.cc"],
    hdrs = ["stream_decoder.h"],
    deps = [
        "//envoy/http:codec_interface",
    ],
)

envoy_cc_mock(
    name = "stream_encoder_mock",
    srcs = ["stream_encoder.cc"],
    hdrs = ["stream_encoder.h"],
    deps = [
        ":stream_mock",
        "//envoy/http:codec_interface",
        "//source/common/http:header_utility_lib",
    ],
)

envoy_cc_test(
    name = "http_mocks_test",
    srcs = ["mocks_test.cc"],
    deps = [
        ":http_mocks",
        "//envoy/http:header_map_interface",
        "//test/test_common:utility_lib",
    ],
)

envoy_cc_mock(
    name = "stream_reset_handler_mock",
    hdrs = ["stream_reset_handler.h"],
    deps = [
        "//envoy/http:stream_reset_handler_interface",
    ],
)
