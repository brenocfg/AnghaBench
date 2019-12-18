#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int USHORT ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/ * HFONT ;
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ANSI_CHARSET ; 
 int /*<<< orphan*/  CLIP_DEFAULT_PRECIS ; 
 int /*<<< orphan*/ * CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFontA (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpCharacterFontData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpCharacterOnScreen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXED_PITCH ; 
 int /*<<< orphan*/  FW_NORMAL ; 
 int /*<<< orphan*/  GetDeviceCaps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int HEIGHT ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int MulDiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NONANTIALIASED_QUALITY ; 
 int /*<<< orphan*/  OUT_DEFAULT_PRECIS ; 
 int /*<<< orphan*/  PlotCharacter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _getch () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  system (char*) ; 

__attribute__((used)) static void DumpFont(LPSTR FontName, INT FontSize, INT XOffset, INT YOffset)
{
    int iHeight;
    HDC hDC = NULL;
    HFONT hFont = NULL;

    DWORD BmpBits[HEIGHT];
    USHORT c;

    hDC = CreateCompatibleDC(NULL);
    if (!hDC)
    {
        fprintf(stderr, "CreateCompatibleDC failed with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    iHeight = -MulDiv(FontSize, GetDeviceCaps(hDC, LOGPIXELSY), 72);
    hFont = CreateFontA(iHeight, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                        ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                        NONANTIALIASED_QUALITY, FIXED_PITCH, FontName);
    if (!hFont)
    {
        fprintf(stderr, "CreateFont failed with error %lu!\n", GetLastError());
        goto Cleanup;
    }

    for (c = 0; c < 256; c++)
    {
        PlotCharacter(hDC, hFont, XOffset, YOffset, (CHAR)c, BmpBits);

#ifdef DUMP_CHAR_ON_SCREEN
        DumpCharacterOnScreen(BmpBits);
        fprintf(stdout, "\nPress any key to continue...\n");
        _getch();
        system("cls");
#else
        DumpCharacterFontData(BmpBits);
#endif
    }

Cleanup:
    if (hFont)
        DeleteObject(hFont);

    if (hDC)
        DeleteDC(hDC);
}