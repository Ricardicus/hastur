load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "xrandr",
    srcs = glob(["src/*.c"]) + ["src/Xrandrint.h"],
    hdrs = ["include/X11/extensions/Xrandr.h"],
    # TODO(robinlinden): Make nicer.
    copts = [
        "-Iexternal/xrandr+/src/",
        "-Iexternal/xrandr+/include/X11/extensions/",
    ],
    linkopts = ["-lX11"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        "@xext",
        "@xrender",
    ],
)
