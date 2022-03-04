filegroup(
    name = "clang_tidy_config_default",
    data = [".clang-tidy"],
)

label_flag(
    name = "clang_tidy_config",
    build_setting_default = ":clang_tidy_config_default",
    visibility = ["//visibility:public"],
)
