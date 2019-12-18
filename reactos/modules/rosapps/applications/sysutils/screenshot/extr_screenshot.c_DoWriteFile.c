#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bmfh ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_8__ {int biSizeImage; void* bfSize; void* bfOffBits; scalar_t__ bfReserved2; scalar_t__ bfReserved1; int /*<<< orphan*/  bfType; } ;
struct TYPE_7__ {TYPE_1__* lpbi; TYPE_3__* lpvBits; } ;
struct TYPE_6__ {TYPE_3__ bmiHeader; } ;
typedef  TYPE_2__* PSCREENSHOT ;
typedef  int /*<<< orphan*/  LPTSTR ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;
typedef  int /*<<< orphan*/  BITMAPINFOHEADER ;
typedef  TYPE_3__ BITMAPFILEHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFile (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  FILE_CURRENT ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 void* SetFilePointer (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 scalar_t__ WriteFile (scalar_t__,TYPE_3__*,int,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
DoWriteFile(PSCREENSHOT pScrSht,
            LPTSTR pstrFileName)
{
    BITMAPFILEHEADER bmfh;
    BOOL bSuccess;
    DWORD dwBytesWritten;
    HANDLE hFile;
    //INT PalEntries;

    hFile = CreateFile(pstrFileName,
                       GENERIC_WRITE,
                       0,
                       NULL,
                       CREATE_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL);

    if (hFile == INVALID_HANDLE_VALUE)
        return FALSE;

    /* write the BITMAPFILEHEADER to file */
    bmfh.bfType = *(WORD *)"BM";  // 0x4D 0x42
    bmfh.bfReserved1 = 0;
    bmfh.bfReserved2 = 0;
    bSuccess = WriteFile(hFile,
                         &bmfh,
                         sizeof(bmfh),
                         &dwBytesWritten,
                         NULL);
    if ((!bSuccess) || (dwBytesWritten < sizeof(bmfh)))
        goto fail;

    /* write the BITMAPINFOHEADER to file */
    bSuccess = WriteFile(hFile,
                         &pScrSht->lpbi->bmiHeader,
                         sizeof(BITMAPINFOHEADER),
                         &dwBytesWritten,
                         NULL);
    if ((!bSuccess) || (dwBytesWritten < sizeof(BITMAPINFOHEADER)))
        goto fail;

    /* calculate the size of the pallete * /
    if (pScrSht->lpbi->bmiHeader.biCompression == BI_BITFIELDS)
        PalEntries = 3;
    else
    {
        if (pScrSht->lpbi->bmiHeader.biBitCount <= 8)
            PalEntries = (INT)(1 << pScrSht->lpbi->bmiHeader.biBitCount);
        else
            PalEntries = 0;
    }
    if (pScrSht->lpbi->bmiHeader.biClrUsed)
        PalEntries = pScrSht->lpbi->bmiHeader.biClrUsed;

    / * write pallete to file * /
    if (PalEntries != 0)
    {
        bSuccess = WriteFile(hFile,
                             &pScrSht->lpbi->bmiColors,
                             PalEntries * sizeof(RGBQUAD),
                             &dwBytesWritten,
                             NULL);
        if ((!bSuccess) || (dwBytesWritten < PalEntries * sizeof(RGBQUAD)))
            goto fail;
    }
*/
    /* save the current file position at the bginning of the bitmap bits */
    bmfh.bfOffBits = SetFilePointer(hFile, 0, 0, FILE_CURRENT);

    /* write the bitmap bits to file */
    bSuccess = WriteFile(hFile,
                         pScrSht->lpvBits,
                         pScrSht->lpbi->bmiHeader.biSizeImage,
                         &dwBytesWritten,
                         NULL);
    if ((!bSuccess) || (dwBytesWritten < pScrSht->lpbi->bmiHeader.biSizeImage))
        goto fail;

    /* save the current file position at the final file size */
    bmfh.bfSize = SetFilePointer(hFile, 0, 0, FILE_CURRENT);

    /* rewrite the updated file headers */
    SetFilePointer(hFile, 0, 0, FILE_BEGIN);
    bSuccess = WriteFile(hFile,
                         &bmfh,
                         sizeof(bmfh),
                         &dwBytesWritten,
                         NULL);
    if ((!bSuccess) || (dwBytesWritten < sizeof(bmfh)))
        goto fail;

    return TRUE;

fail:
    GetError();
    if (hFile) CloseHandle(hFile);
    DeleteFile(pstrFileName);
    return FALSE;

}