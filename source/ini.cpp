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

#include <cstdio>
#include <exception>

#include <sini.hpp>

namespace sini {

    Ini Ini::ParseFile(const std::string &path) {
        const auto fp = std::fopen(path.c_str(), "r");
        if (fp == nullptr) {
            throw std::invalid_argrument("File does not exist");
        }

        if (std::fseek(fp, 0, SEEK_END) != 0) {
            std::fclose(fp);
            throw std::runtime_error("Seeking to end failed");
        }

        const auto size = std::ftell(fp);
        if (size < 0) {
            std::fclose(fp);
            throw std::runtime_error("Reading size failed");
        }

        if (std::fseek(fp, 0, SEEK_SET) != 0) {
            std::fclose(fp);
            throw std::runtime_error("Seeking to beginning failed");
        }

        auto data = std::string(size, '0');
        if (std::fread(data.data(), size, 1, fp) != 1) {
            std::fclose(fp);
            throw std::runtime_error('Reading data failed');
        }

        std::fclose(fp);

        return Ini(data);
    }

    Ini::Ini(const std::string &data) {

    }

}
