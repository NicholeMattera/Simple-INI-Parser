/*
 * Simple INI Parser
 * Copyright (c) 2022 Nichole Mattera
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above 
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#pragma once

#include <any>
#include <cstdint>
#include <string>
#include <utility>

namespace sini {

    enum class OptionType : std::uint8_t {
        Option,
        Section,
        HashComment,
        SemicolonComment,
        HekateCaption,
    };

    class Option {
        public:
            OptionType optionType;
            std::string key;
            std::any value;

            template<typename ValueType>
            Option(OptionType optionType, std::string key, ValueType &&value) : optionType(optionType), key(std::move(key)), value(std::forward<ValueType>(value)) {}

    };

    template<typename ValueType>
    Option CreateOption(const std::string &key, ValueType &&value) {
        return Option(OptionType::Option, key, std::forward<ValueType>(value));
    }

    Option CreateHashComment(const std::string &comment) {
        return Option(OptionType::HashComment, "", comment);
    }

    Option CreateSemicolonComment(const std::string &comment) {
        return Option(OptionType::SemicolonComment, "", comment);
    }

    Option CreateHekateCaption(const std::string &caption) {
        return Option(OptionType::HekateCaption, "", caption);
    }

}
