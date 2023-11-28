// SPDX-FileCopyrightText: 2023 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#ifndef TYPE_SFML_H_
#define TYPE_SFML_H_

#include "type/type.h"

#include <SFML/Graphics/Font.hpp>

#include <map>
#include <memory>
#include <optional>
#include <string_view>
#include <utility>

namespace type {

class SfmlFont : public IFont {
public:
    explicit SfmlFont(sf::Font const &font) : font_{font} {}

    Size measure(std::string_view text, Px font_size) const override;

    sf::Font const &sf_font() const { return font_; }

private:
    sf::Font font_{};
};

class SfmlType : public IType {
public:
    std::optional<std::shared_ptr<IFont const>> font(std::string_view name) const override;

private:
    mutable std::map<std::string, std::shared_ptr<SfmlFont>, std::less<>> font_cache_;
};

} // namespace type

#endif
