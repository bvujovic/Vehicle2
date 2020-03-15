#pragma once

#include <Arduino.h>
#include <FS.h>

#define DEBUG true

#if DEBUG
// Test printline
#define tprintln(caption, obj) \
    {                          \
        Serial.print(caption); \
        Serial.println(obj);   \
    }
#else
#define tprintln(caption, obj) ;
#endif

// Klasa koja sadrzi razne "utillity" metode.
class Utils
{
public:
    // Koliko ima slobodnih kilobajta memorije.
    static int GetFreeMemKB() { return ESP.getFreeHeap() / 1024; }

    // Prikaz parametara ESPa: memorija, flash, fajlovi, CPU takt
    static void PrintBoardStatus()
    {
        SPIFFS.begin();
        FSInfo fs_info;
        SPIFFS.info(fs_info);

        float fileTotalKB = (float)fs_info.totalBytes / 1024.0;
        float fileUsedKB = (float)fs_info.usedBytes / 1024.0;

        float flashChipSize = (float)ESP.getFlashChipSize() / 1024.0 / 1024.0;
        float realFlashChipSize = (float)ESP.getFlashChipRealSize() / 1024.0 / 1024.0;
        float flashFreq = (float)ESP.getFlashChipSpeed() / 1000.0 / 1000.0;
        FlashMode_t ideMode = ESP.getFlashChipMode();

        Serial.printf("\n#####################\n");

        Serial.printf("__________________________\n\n");
        Serial.println("Firmware: ");
        Serial.printf("    Chip Id: %08X\n", ESP.getChipId());
        Serial.print("    Core version: ");
        Serial.println(ESP.getCoreVersion());
        Serial.print("    SDK version: ");
        Serial.println(ESP.getSdkVersion());
        Serial.print("    Boot version: ");
        Serial.println(ESP.getBootVersion());
        Serial.print("    Boot mode: ");
        Serial.println(ESP.getBootMode());

        Serial.printf("__________________________\n\n");

        Serial.println("Flash chip information: ");
        Serial.printf("    Flash chip Id: %08X (for example: Id=001640E0  Manuf=E0, Device=4016 (swap bytes))\n", ESP.getFlashChipId());
        Serial.printf("    Sketch thinks Flash RAM is size: ");
        Serial.print(flashChipSize);
        Serial.println(" MB");
        Serial.print("    Actual size based on chip Id: ");
        Serial.print(realFlashChipSize);
        Serial.println(" MB ... given by (2^( \"Device\" - 1) / 8 / 1024");
        Serial.print("    Flash frequency: ");
        Serial.print(flashFreq);
        Serial.println(" MHz");
        Serial.printf("    Flash write mode: %s\n", (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT" : ideMode == FM_DIO ? "DIO" : ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));

        Serial.printf("__________________________\n\n");

        Serial.println("File system (SPIFFS): ");
        Serial.print("    Total KB: ");
        Serial.print(fileTotalKB);
        Serial.println(" KB");
        Serial.print("    Used KB: ");
        Serial.print(fileUsedKB);
        Serial.println(" KB");
        Serial.printf("    Block size: %d\n", fs_info.blockSize);
        Serial.printf("    Page size: %d\n", fs_info.pageSize);
        Serial.printf("    Maximum open files: %d\n", fs_info.maxOpenFiles);
        Serial.printf("    Maximum path length: %d\n\n", fs_info.maxPathLength);

        Dir dir = SPIFFS.openDir("/");
        Serial.println("SPIFFS directory {/} :");
        while (dir.next())
        {
            Serial.print("  ");
            Serial.println(dir.fileName());
        }

        Serial.printf("__________________________\n\n");

        Serial.printf("CPU frequency: %u MHz\n\n", ESP.getCpuFreqMHz());
        Serial.print("#####################");
    }
};