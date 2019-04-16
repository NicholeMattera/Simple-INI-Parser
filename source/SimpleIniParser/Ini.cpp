/*
 * SimpleIniParser
 * Copyright (c) 2019 Steven Mattera
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

#include <fstream>
#include <iostream>
#include "Ini.hpp"
#include "IniOption.hpp"
#include "Trim.hpp"

using namespace std;

namespace simpleIniParser {
    Ini::~Ini() {
        for (IniSection * section : sections) {
            if (section != nullptr) {
                delete section;
                section = nullptr;
            }
        }
        sections.clear();
    }

    string Ini::build() {
        string result;

        for (IniSection * section : sections) {
            result += section->build() + "\n";
        }

        return result;
    }

    IniSection * Ini::findSection(string name) {
        auto it = find_if(sections.begin(), sections.end(), [&name](const IniSection * obj) { return obj->value == name; });
        if (it == sections.end())
            return nullptr;

        return (*it);
    }

    bool Ini::writeToFile(string path) {
        ofstream file(path);
        if (!file.is_open())
            return false;

        file << build();

        file.flush();
        file.close();

        return true;
    }

    Ini * Ini::parseFile(string path) {
        ifstream file(path);
        if (!file.is_open())
            return nullptr;

        Ini * ini = new Ini();
        string line;
        while (getline(file, line)) {
            trim(line);

            if (line.size() == 0)
                continue;

            IniSection * section = IniSection::parse(line);
            if (section != nullptr) {
                ini->sections.push_back(section);
            }
            else if (ini->sections.size() != 0 && ini->sections.back()->type == SECTION) {
                IniOption * option = IniOption::parse(line);

                if (option != nullptr)
                    ini->sections.back()->options.push_back(option);
            }
        }

        file.close();

        return ini;
    }
}
