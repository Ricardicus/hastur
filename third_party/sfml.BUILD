load("@rules_cc//cc:defs.bzl", "cc_library", "objc_library")

# SFML has copied the generated files into their source tree and patched them.
# The files are generated w/ very different options from us, so we can't just
# force them to use our glad even if we patch their files to look for standard
# glad types.
# See: external/sfml/extlibs/headers/glad/include/glad/gl.h,
#      external/sfml/extlibs/headers/glad/include/glad/wgl.h
#
# TODO(robinlinden): Spend more time on making SFML use our glad.
cc_library(
    name = "sf_glad",
    hdrs = glob(["extlibs/headers/glad/include/glad/**/*.h"]),
    strip_include_prefix = "extlibs/headers/glad/include/",
)

SFML_DEFINES = [
    "SFML_STATIC",
    "UNICODE",
    "_UNICODE",
]

cc_library(
    name = "system",
    srcs = glob(["src/SFML/System/*.cpp"]) + select({
        "@platforms//os:linux": glob([
            "src/SFML/System/Unix/**/*.cpp",
            "src/SFML/System/Unix/**/*.hpp",
        ]),
        "@platforms//os:macos": glob([
            "src/SFML/System/Unix/**/*.cpp",
            "src/SFML/System/Unix/**/*.hpp",
        ]),
        "@platforms//os:windows": glob([
            "src/SFML/System/Win32/**/*.cpp",
            "src/SFML/System/Win32/**/*.hpp",
        ]),
    }),
    hdrs = glob([
        "include/SFML/*",
        "include/SFML/System/*",
    ]),
    copts = ["-Iexternal/sfml/src/"],
    defines = SFML_DEFINES,
    linkopts = select({
        "@platforms//os:linux": [
            "-pthread",
        ],
        "@platforms//os:macos": [
            "-pthread",
        ],
        "@platforms//os:windows": [
            "-DEFAULTLIB:winmm",
        ],
    }),
    strip_include_prefix = "include/",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "window",
    srcs = glob(
        include = [
            "src/SFML/Window/*.cpp",
            "src/SFML/Window/*.hpp",
        ],
        exclude = [
            "src/SFML/Window/EGLCheck.cpp",
            "src/SFML/Window/EGLCheck.hpp",
            "src/SFML/Window/EglContext.cpp",
            "src/SFML/Window/EglContext.hpp",
        ],
    ) + select({
        "@platforms//os:linux": glob([
            "src/SFML/Window/Unix/*.cpp",
            "src/SFML/Window/Unix/*.hpp",
        ]),
        "@platforms//os:windows": glob([
            "src/SFML/Window/Win32/*.cpp",
            "src/SFML/Window/Win32/*.hpp",
        ]),
    }),
    hdrs = glob(["include/SFML/Window/*"]),
    copts = ["-Iexternal/sfml/src/"],
    defines = SFML_DEFINES,
    linkopts = select({
        "@platforms//os:linux": ["-lX11"],
        "@platforms//os:windows": [
            "-DEFAULTLIB:advapi32",
            "-DEFAULTLIB:gdi32",
            "-DEFAULTLIB:opengl32",
            "-DEFAULTLIB:user32",
            "-DEFAULTLIB:winmm",
        ],
    }),
    strip_include_prefix = "include/",
    target_compatible_with = select({
        "@platforms//os:macos": ["@platforms//:incompatible"],
        "//conditions:default": [],
    }),
    visibility = ["//visibility:public"],
    deps = [
        ":sf_glad",
        ":system",
        "@vulkan",
    ] + select({
        "@platforms//os:linux": [
            "@udev-zero",
            "@xcursor",
            "@xrandr",
        ],
        "@platforms//os:windows": [],
    }),
)

objc_library(
    name = "window_macos",
    srcs = glob(
        include = [
            "src/SFML/Window/*.cpp",
            "src/SFML/Window/*.hpp",
            "src/SFML/Window/OSX/*.cpp",
            "src/SFML/Window/OSX/*.h",
            "src/SFML/Window/OSX/*.hpp",
        ],
        exclude = [
            "src/SFML/Window/EGLCheck.cpp",
            "src/SFML/Window/EGLCheck.hpp",
            "src/SFML/Window/EglContext.cpp",
            "src/SFML/Window/EglContext.hpp",
        ],
    ),
    hdrs = glob(["include/SFML/Window/*"]),
    copts = [
        "-Iexternal/sfml/src/",
        "-frtti",
    ],
    defines = SFML_DEFINES,
    includes = ["include/"],
    non_arc_srcs = glob([
        "src/SFML/Window/OSX/*.m",
        "src/SFML/Window/OSX/*.mm",
    ]),
    sdk_frameworks = [
        "AppKit",
        "Carbon",
        "Foundation",
        "IOKit",
    ],
    target_compatible_with = select({
        "@platforms//os:macos": [],
        "//conditions:default": ["@platforms//:incompatible"],
    }),
    visibility = ["//visibility:public"],
    deps = [
        ":sf_glad",
        ":system",
    ],
)

cc_library(
    name = "graphics",
    srcs = glob(
        include = [
            "src/SFML/Graphics/*.cpp",
            "src/SFML/Graphics/*.hpp",
        ],
    ),
    hdrs = glob(["include/SFML/Graphics/*"]),
    copts = ["-Iexternal/sfml/src/"],
    defines = SFML_DEFINES,
    includes = ["include/"],
    linkopts = select({
        "@platforms//os:linux": ["-lX11"],
        "@platforms//os:macos": [],
        "@platforms//os:windows": [],
    }),
    strip_include_prefix = "include/",
    visibility = ["//visibility:public"],
    deps = [
        ":sf_glad",
        ":system",
        ":window",
        "@freetype2",
        "@stb//:image",
        "@stb//:image_write",
    ],
)
