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

void copy_file(string srcPath, string destPath);

int main(int argc, char **argv) {
    consoleInit(NULL);

    Result rc = romfsInit();
    if (R_FAILED(rc)) {
        cout << "Unable to initialize romfs.\n";
    }
    else {
        copy_file("romfs:/hekate_ipl.ini", "sdmc:/example1.ini");

        Ini * exampleIni = Ini::parseFile("sdmc:/example1.ini");
        exampleIni->sections.pop_back();
        exampleIni->sections.pop_back();

        exampleIni->findSection("config")->findFirstOption("autoboot")->value = "0";

        exampleIni->writeToFile("sdmc:/example2.ini");

        delete exampleIni;
    }
    cout << "Original file written to: sdmc:/example1.ini\n";
    cout << "Modified file written to: sdmc:/example2.ini\n\n";
    cout << "Press any key to close.\n";

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

void copy_file(string srcPath, string destPath) {
    ifstream src(srcPath, ios::binary);
    ofstream dest(destPath, ios::binary);

    dest << src.rdbuf();

    src.close();
    dest.flush();
    dest.close();
}