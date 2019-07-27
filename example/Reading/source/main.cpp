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

#include <iostream>
#include <fstream>
#include <switch.h>
#include <SimpleIniParser.hpp>

using namespace simpleIniParser;
using namespace std;

int main(int argc, char **argv) {
    consoleInit(NULL);

    Result rc = romfsInit();
    if (R_FAILED(rc)) {
        cout << "Unable to initialize romfs.\n";
    }
    else {
        Ini * hekateIni = Ini::parseFile("romfs:/hekate_ipl.ini");

        cout << "Reading through an INI file.\n";
        cout << "=====================================================\n\n";

        for (auto const& section : hekateIni->sections) {
            switch (section->type) {
                case SECTION:
                    cout << "Type: Section | Value: \"" << section->value << "\"\n";
                    cout << "-----------------------------------------------------\n";
                    break;

                case SEMICOLON_COMMENT:
                    cout << "Type: Semicolon Comment | Value: \"" << section->value << "\"\n";
                    cout << "-----------------------------------------------------\n";
                    break;

                case HASHTAG_COMMENT:
                    cout << "Type: Hashtag Comment | Value: \"" << section->value << "\"\n";
                    cout << "-----------------------------------------------------\n";
                    break;

                case HEKATE_CAPTION:
                    cout << "Type: Hekate Caption | Value: \"" << section->value << "\"\n";
                    cout << "-----------------------------------------------------\n";
                    break;

                default:
                    break;
            }

            for (auto const& option : section->options) {
                cout << "Key: \"" << option->key << "\" | Value: \"" << option->value << "\"\n";
            }
            
            cout << "\n";
        }

        cout << "\nGet a specific option from a specific section.\n";
        cout << "=====================================================\n\n";
        IniOption * option = hekateIni->findSection("config")->findFirstOption("aUtOnOgC", false);
        cout << "Key: \"" << option->key << "\" | Value: \"" << option->value << "\"\n\n";

        delete hekateIni;
    }

    cout << "\nPress any key to close.\n";

    while(appletMainLoop())
    {
        hidScanInput();
        if (hidKeysDown(CONTROLLER_P1_AUTO))
            break;

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}