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

#include <cstdint>
#include <string>

namespace sini {

    enum class OptionType : std::uint8_t {
        Option,
        Section,
        HashComment,
        SemicolonComment,
        HekateCaption,
    };

    template<typename ValueType>
    class Option {
        public:
            OptionType optionType;
            std::string key;
            ValueType value;

            Option(OptionType optionType, const std::string &key, const ValueType &value) : optionType(optionType), key(key), value(value) {}

    };

    template<typename ValueType>
    Option<ValueType> CreateOption(const std::string &key, const ValueType &value) {
        return Option<ValueType>(OptionType::Option, key, value);
    }

    Option<std::string> CreateHashComment(const std::string &comment) {
        return Option<std::string>(OptionType::HashComment, "", comment);
    }

    Option<std::string> CreateSemicolonComment(const std::string &comment) {
        return Option<std::string>(OptionType::SemicolonComment, "", comment);
    }

    Option<std::string> CreateHekateCaption(const std::string &caption) {
        return Option<std::string>(OptionType::HekateCaption, "", caption);
    }

}
