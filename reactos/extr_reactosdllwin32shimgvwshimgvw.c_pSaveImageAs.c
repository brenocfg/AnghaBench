#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  szSaveFileName ;
typedef  int /*<<< orphan*/  sfn ;
struct TYPE_12__ {int lStructSize; int nMaxFile; int Flags; size_t nFilterIndex; int /*<<< orphan*/  Clsid; int /*<<< orphan*/  FormatID; int /*<<< orphan*/  FilenameExtension; int /*<<< orphan*/  FormatDescription; struct TYPE_12__* lpstrFilter; struct TYPE_12__* lpstrFile; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  hwndOwner; } ;
typedef  TYPE_1__ WCHAR ;
typedef  size_t UINT ;
typedef  TYPE_1__ OPENFILENAMEW ;
typedef  TYPE_1__ ImageCodecInfo ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  ANIME_TIMER_ID ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GdipGetImageEncoders (size_t,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  GdipGetImageEncodersSize (size_t*,size_t*) ; 
 int /*<<< orphan*/  GdipGetImageRawFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GdipSaveImageToFile (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GetSaveFileNameW (TYPE_1__*) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KillTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int OFN_HIDEREADONLY ; 
 int OFN_OVERWRITEPROMPT ; 
 scalar_t__ Ok ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StringCbPrintfExW (TYPE_1__*,size_t,TYPE_1__**,size_t*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hDispWnd ; 
 int /*<<< orphan*/  hInstance ; 
 int /*<<< orphan*/  image ; 
 scalar_t__ m_pDelayItem ; 
 TYPE_1__* malloc (size_t) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pSaveImageAs(HWND hwnd)
{
    OPENFILENAMEW sfn;
    ImageCodecInfo *codecInfo;
    WCHAR szSaveFileName[MAX_PATH];
    WCHAR *szFilterMask;
    GUID rawFormat;
    UINT num;
    UINT size;
    size_t sizeRemain;
    UINT j;
    WCHAR *c;

    GdipGetImageEncodersSize(&num, &size);
    codecInfo = malloc(size);
    if (!codecInfo)
    {
        DPRINT1("malloc() failed in pSaveImageAs()\n");
        return;
    }

    GdipGetImageEncoders(num, size, codecInfo);
    GdipGetImageRawFormat(image, &rawFormat);

    sizeRemain = 0;

    for (j = 0; j < num; ++j)
    {
        // Every pair needs space for the Description, twice the Extensions, 1 char for the space, 2 for the braces and 2 for the NULL terminators.
        sizeRemain = sizeRemain + (((wcslen(codecInfo[j].FormatDescription) + (wcslen(codecInfo[j].FilenameExtension) * 2) + 5) * sizeof(WCHAR)));
    }

    /* Add two more chars for the last terminator */
    sizeRemain = sizeRemain + (sizeof(WCHAR) * 2);

    szFilterMask = malloc(sizeRemain);
    if (!szFilterMask)
    {
        DPRINT1("cannot allocate memory for filter mask in pSaveImageAs()");
        free(codecInfo);
        return;
    }

    ZeroMemory(szSaveFileName, sizeof(szSaveFileName));
    ZeroMemory(szFilterMask, sizeRemain);
    ZeroMemory(&sfn, sizeof(sfn));
    sfn.lStructSize = sizeof(sfn);
    sfn.hwndOwner   = hwnd;
    sfn.hInstance   = hInstance;
    sfn.lpstrFile   = szSaveFileName;
    sfn.lpstrFilter = szFilterMask;
    sfn.nMaxFile    = MAX_PATH;
    sfn.Flags       = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;

    c = szFilterMask;

    for (j = 0; j < num; ++j)
    {
        StringCbPrintfExW(c, sizeRemain, &c, &sizeRemain, 0, L"%ls (%ls)", codecInfo[j].FormatDescription, codecInfo[j].FilenameExtension);

        /* Skip the NULL character */
        c++;
        sizeRemain -= sizeof(*c);

        StringCbPrintfExW(c, sizeRemain, &c, &sizeRemain, 0, L"%ls", codecInfo[j].FilenameExtension);

        /* Skip the NULL character */
        c++;
        sizeRemain -= sizeof(*c);

        if (IsEqualGUID(&rawFormat, &codecInfo[j].FormatID) != FALSE)
        {
            sfn.nFilterIndex = j + 1;
        }
    }

    if (GetSaveFileNameW(&sfn))
    {
        if (m_pDelayItem)
        {
            /* save animation */
            KillTimer(hDispWnd, ANIME_TIMER_ID);

            DPRINT1("FIXME: save animation\n");
            if (GdipSaveImageToFile(image, szSaveFileName, &codecInfo[sfn.nFilterIndex - 1].Clsid, NULL) != Ok)
            {
                DPRINT1("GdipSaveImageToFile() failed\n");
            }

            SetTimer(hDispWnd, ANIME_TIMER_ID, 0, NULL);
        }
        else
        {
            /* save non-animation */
            if (GdipSaveImageToFile(image, szSaveFileName, &codecInfo[sfn.nFilterIndex - 1].Clsid, NULL) != Ok)
            {
                DPRINT1("GdipSaveImageToFile() failed\n");
            }
        }
    }

    free(szFilterMask);
    free(codecInfo);
}