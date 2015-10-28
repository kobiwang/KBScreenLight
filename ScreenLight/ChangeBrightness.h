#ifndef GAMMARAMP_H_
#define GAMMARAMP_H_

#include <windows.h>

class ChangeBrightness 
{
private:
        HMODULE hGDI32;
        HDC hScreenDC;
        typedef BOOL (WINAPI *Type_SetDeviceGammaRamp)(HDC hDC, LPVOID lpRamp);

        Type_SetDeviceGammaRamp pSetDeviceGammaRamp;

        BOOL LoadLibrary();
        void FreeLibrary();
        BOOL LoadLibraryIfNeeded();
        BOOL SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp);

public:
        ChangeBrightness();
        ~ChangeBrightness();
        BOOL SetBrightness(HDC hDC, WORD wBrightness);
};

#endif