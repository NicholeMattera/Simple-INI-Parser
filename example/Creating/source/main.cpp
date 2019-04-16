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