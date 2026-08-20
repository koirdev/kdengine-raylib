#include "raylib.h"
#include "config.h"
#include <stdio.h>
#include <Python.h>
#define PY_SSIZE_T_CLEAN

void rsplash();

int main(void)
{
    // Python Init Start ---
    Py_Initialize();

    PyRun_SimpleString(
    "import os, sys\n"
    "print('cwd=', os.getcwd())\n"
    "print('sys.path[0]=', sys.path[0])\n"
);

    PyRun_SimpleString("import sys, os; sys.path.insert(0, os.path.join(os.getcwd(),'src'))");
    PyObject *pythonFileName = PyUnicode_FromString("os_info");
    PyObject *pythonModule = PyImport_Import(pythonFileName);
    Py_DECREF(pythonFileName);

    PyObject *pythonOsName = PyObject_GetAttrString(pythonModule, "OS_NAME");
    PyObject *pythonPlatform = PyObject_GetAttrString(pythonModule, "PLATFORM_SYS");
    PyObject *pythonRelease = PyObject_GetAttrString(pythonModule, "PLATFORM_RELEASE");
    PyObject *pythonPlatformVersion = PyObject_GetAttrString(pythonModule, "PLATFORM_VERSION");
    PyObject *pythonArch = PyObject_GetAttrString(pythonModule, "PLATFORM_ARCH");

    const char *pythonOsNameVar = PyUnicode_AsUTF8(pythonOsName);
    const char *pythonPlatformVar = PyUnicode_AsUTF8(pythonPlatform);
    const char *pythonReleaseVar = PyUnicode_AsUTF8(pythonRelease);
    const char *pythonPlatformVersionVar = PyUnicode_AsUTF8(pythonPlatformVersion);
    const char *pythonArchVar = PyUnicode_AsUTF8(pythonArch);

    if (!pythonModule) {
        PyErr_Print();
        Py_Finalize();
        return 1;
    }

    // Python Init End ---

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "KD Engine Raylib");
    InitAudioDevice();              // Initialize audio device
    Music music = LoadMusicStream("assets/music/wotw - intro number 63.mod");
    PlayMusicStream(music);

    Image shirLogoImg = LoadImage("assets/images/shirLogo.png");     // Loaded in CPU memory (RAM)
    ImageResize(&shirLogoImg, 430, 170);
    Texture2D shirLogoTexture = LoadTextureFromImage(shirLogoImg);          // Image converted to texture, GPU memory (VRAM)
    
    SetTargetFPS(FPS);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground((Color){84, 26, 145});
        
        DrawTexture(shirLogoTexture, 420, 0, WHITE);
        // Debug info (if DEBUG_MODE variable is 1).
        if (DEBUG_MODE == 1) {
            int fpsCounter = GetFPS();
            DrawText(TextFormat("FPS: %d\nScreen Width: %d\nScreen Height: %d\nGame version: %s\nEngine version: %s\nraylib version: %s\n\nPython modules (Python version: %s):\nos Name: %s\nplatform System: %s\nplatform Release: %s\nplatform Version: %s\nplatform Architecture: %s\n", fpsCounter, SCREEN_WIDTH, SCREEN_HEIGHT, GAME_VERSION, ENGINE_VERSION, RAYLIB_VERSION, pythonOsNameVar, pythonPlatformVar, pythonReleaseVar, pythonPlatformVersionVar, pythonArchVar), 0, 0, 25, WHITE);
        }

        EndDrawing();

    }
    UnloadImage(shirLogoImg); 
    UnloadTexture(shirLogoTexture);

    CloseWindow();


    return 0;
}