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

    Ini * hekateIni = new Ini();

    IniSection * configSection = new IniSection(SECTION, "config");
    configSection->options.push_back(new IniOption("autoboot", "1"));
    configSection->options.push_back(new IniOption("autoboot_list", "0"));
    configSection->options.push_back(new IniOption("bootwait", "5"));
    configSection->options.push_back(new IniOption("customlogo", "1"));
    configSection->options.push_back(new IniOption("verification", "1"));
    configSection->options.push_back(new IniOption("backlight", "100"));
    configSection->options.push_back(new IniOption("autohosoff", "0"));
    configSection->options.push_back(new IniOption("autonogc", "1"));
    hekateIni->sections.push_back(configSection);

    hekateIni->sections.push_back(new IniSection(HEKATE_CAPTION, "CFW"));

    IniSection * cfwSection = new IniSection(SECTION, "CFW");
    cfwSection->options.push_back(new IniOption("fss0", "atmosphere/fusee-secondary.bin"));
    cfwSection->options.push_back(new IniOption("kip1patch", "nosigchk"));
    cfwSection->options.push_back(new IniOption("atmosphere", "1"));
    cfwSection->options.push_back(new IniOption("logopath", "bootloader/bootlogo.bmp"));
    hekateIni->sections.push_back(cfwSection);

    hekateIni->sections.push_back(new IniSection(HEKATE_CAPTION, "Stock"));

    IniSection * stockSection = new IniSection(SECTION, "Stock");
    stockSection->options.push_back(new IniOption("fss0", "atmosphere/fusee-secondary.bin"));
    stockSection->options.push_back(new IniOption("stock", "1"));
    hekateIni->sections.push_back(stockSection);

    if (hekateIni->writeToFile("sdmc:/example.ini")) {
        cout << "Ini file writen to: sdmc:/example.ini\n";
    }

    delete hekateIni;

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