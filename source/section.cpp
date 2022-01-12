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

#include <stdexcept>
#include <type_traits>

#include <sini.hpp>

namespace sini {
    template<typename ValueType>
    Option<ValueType> Section::getOption(size_t index) {
        if (index >= _options.size()) {
            throw std::out_of_range("Index out of range");
        }

        auto option = _options[index];
        return std::visit([](auto&& arg) -> Option<ValueType> {
            using OptionValueType = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<OptionValueType, ValueType>) {
                return arg;
            } else {
                throw std::invalid_argument("Option does not exist");
            }
        });
    }
    
    template<typename ValueType>
    std::vector<Option<ValueType>> Section::getOptions(const std::string &key) {
        std::vector<Option<ValueType>> matchOptions;
        for (auto& option: _options) {
            std::visit([matchOptions, key](auto&& arg) {
                using OptionValueType = std::decay_t<decltype(arg)>;
                if constexpr (!std::is_same_v<OptionValueType, ValueType>) {
                    return;
                }

                if (arg.key != key) {
                    return;
                }

                matchOptions.push_back(arg);
            });
        }

        return matchOptions;
    }
}
