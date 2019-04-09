// SimpleIniParser
// Copyright (C) 2019 Steven Mattera
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

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
        IniOption * option = hekateIni->findSection("config")->findFirstOption("autonogc");
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