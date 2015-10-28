#include "stdafx.h"
#include "ChangeBrightness.h"

ChangeBrightness::ChangeBrightness()
{
    hGDI32 = NULL;
    hScreenDC = NULL;
    pSetDeviceGammaRamp = NULL;
}

ChangeBrightness::~ChangeBrightness()
{
    FreeLibrary();
}
  
BOOL ChangeBrightness::LoadLibrary()
{
    BOOL bReturn = FALSE;

    FreeLibrary();
     
    hGDI32 = ::LoadLibrary(_T("gdi32.dll")); 
    if(hGDI32 != NULL)
    { 
        pSetDeviceGammaRamp = (Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "SetDeviceGammaRamp");   

        if(pSetDeviceGammaRamp == NULL) 
            FreeLibrary(); 
        else
            bReturn = TRUE;
    }

    return bReturn;
}

void ChangeBrightness::FreeLibrary() 
{
    if(hGDI32 != NULL)
    {
        ::FreeLibrary(hGDI32);
        hGDI32 = NULL;
    }
}

BOOL ChangeBrightness::LoadLibraryIfNeeded()
{
    BOOL bReturn = FALSE;

    if(hGDI32 == NULL)
        LoadLibrary();

    if(pSetDeviceGammaRamp != NULL)
        bReturn = TRUE;

    return bReturn;
}
   
   
BOOL ChangeBrightness::SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp)
{ 
    if(LoadLibraryIfNeeded())
        return pSetDeviceGammaRamp(hDC, lpRamp);   
        else
        return FALSE;
}   


BOOL ChangeBrightness::SetBrightness(HDC hDC, WORD wBrightness)
{   
    BOOL bReturn = FALSE;
    HDC hGammaDC = hDC;
      
    if(hDC == NULL)
        hGammaDC = GetDC(NULL);

    if(hGammaDC != NULL)
    {     
        WORD GammaArray[3][256];

        for(int iIndex = 0; iIndex < 256; iIndex++)
        {
            int iArrayValue = iIndex * (wBrightness + 128); 

            if (iArrayValue > 65535)
                iArrayValue = 65535;
   
            GammaArray[0][iIndex] =
            GammaArray[1][iIndex] =
            GammaArray[2][iIndex] = (WORD)iArrayValue;
        }
        bReturn = SetDeviceGammaRamp(hGammaDC, GammaArray);
    }

    if(hDC == NULL)
        ReleaseDC(NULL, hGammaDC);

    return bReturn;
}