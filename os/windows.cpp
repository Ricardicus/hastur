// SPDX-FileCopyrightText: 2021-2022 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#include "os/os.h"

#include <WinSdkVer.h>
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#ifdef WINVER
#undef WINVER
#endif
// GetScaleFactorForMonitor was introduced in Windows 8.1.
#define _WIN32_WINNT _WIN32_WINNT_WINBLUE
#define WINVER _WIN32_WINNT

// Must be included first because Windows headers don't include what they use.
#include <Windows.h>

#include <Knownfolders.h>
#include <Objbase.h>
#include <Shlobj.h>
#include <shellscalingapi.h>

#include <charconv>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cwchar>

namespace os {

std::vector<std::string> font_paths() {
    PWSTR bad_font_path{nullptr};
    SHGetKnownFolderPath(FOLDERID_Fonts, 0, nullptr, &bad_font_path);
    auto bad_font_path_len = static_cast<int>(std::wcslen(bad_font_path));
    auto chars_needed = WideCharToMultiByte(CP_UTF8, 0, bad_font_path, bad_font_path_len, nullptr, 0, nullptr, nullptr);
    std::string font_path;
    font_path.resize(chars_needed);
    WideCharToMultiByte(CP_UTF8, 0, bad_font_path, bad_font_path_len, font_path.data(), chars_needed, nullptr, nullptr);
    CoTaskMemFree(bad_font_path);
    return {font_path};
}

unsigned active_window_scale_factor() {
    // NOLINTNEXTLINE(concurrency-mt-unsafe): We never modify the environment variables.
    if (auto const *env_var = std::getenv("HST_SCALE")) {
        if (int result{}; std::from_chars(env_var, env_var + std::strlen(env_var), result).ec == std::errc{}) {
            return result;
        }
    }

    DEVICE_SCALE_FACTOR scale_factor{};
    if (GetScaleFactorForMonitor(MonitorFromWindow(GetActiveWindow(), MONITOR_DEFAULTTONEAREST), &scale_factor)
            != S_OK) {
        return 1;
    }

    return static_cast<unsigned>(std::lround(static_cast<float>(scale_factor) / 100.f));
}

} // namespace os
