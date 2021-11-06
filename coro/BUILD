load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "coro",
    hdrs = ["generator.h"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "generator_test",
    size = "small",
    srcs = ["generator_test.cpp"],
    deps = [
        ":coro",
        "//etest",
    ],
)
