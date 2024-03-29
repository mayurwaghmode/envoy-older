load(
    "//bazel:envoy_build_system.bzl",
    "envoy_package",
)
load("@rules_python//python:defs.bzl", "py_binary")
load("@base_pip3//:requirements.bzl", "requirement")

licenses(["notice"])  # Apache 2

envoy_package()

exports_files([
    "google-vrp/envoy-edge.yaml",
])

py_binary(
    name = "configgen",
    srcs = ["configgen.py"],
    data = glob([
        "*.yaml",
    ]),
    deps = [
        requirement("jinja2"),
    ],
)

filegroup(
    name = "configs",
    srcs = glob(
        [
            "**/*.yaml",
        ],
        exclude = [
            "using_deprecated_config.yaml",
            "**/*.template.yaml",
            "freebind/freebind.yaml",
            "envoy-demo.yaml",
        ],
    ) + select({
        "//bazel:apple": ["envoy-demo.yaml"],
        "//bazel:windows_x86_64": [],
        "//conditions:default": [
            "envoy-demo.yaml",
            "freebind/freebind.yaml",
        ],
    }),
)

genrule(
    name = "example_configs",
    srcs = [
        ":configs",
        "//examples:configs",
        "//examples:certs",
        "//examples:lua",
        "//examples/wasm-cc:configs",
        "//docs:configs",
        "//docs:proto_examples",
        "//test/config/integration/certs",
    ],
    outs = ["example_configs.tar"],
    cmd = (
        "$(location configgen.sh) $(location configgen) $(@D) " +
        "$(locations :configs) " +
        "$(locations //examples:configs) " +
        "$(locations //examples:certs) " +
        "$(locations //examples:lua) " +
        "$(locations //examples/wasm-cc:configs) " +
        "$(locations //docs:configs) " +
        "$(locations //docs:proto_examples) " +
        "$(locations //test/config/integration/certs)"
    ),
    tools = [
        "configgen.sh",
        ":configgen",
    ],
)

py_binary(
    name = "example_configs_validation",
    srcs = ["example_configs_validation.py"],
    args = (
        "$(locations :configs) ",
        "$(locations //examples:configs) ",
        "$(locations //docs:configs) ",
    ),
    data = [
        ":configs",
        "//docs:configs",
        "//examples:configs",
    ],
    deps = [
        "//tools/config_validation:validate_fragment",
    ],
)
