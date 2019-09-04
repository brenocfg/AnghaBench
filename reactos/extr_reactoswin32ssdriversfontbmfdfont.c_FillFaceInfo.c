#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* WCHAR ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int ulVersion; int cjEntrySize; int /*<<< orphan*/  flInfo; void* wPixWidth; int /*<<< orphan*/ * pCharTable; void* wC; void* wB; void* wA; void* wAscent; void* wPixHeight; void* wDescent; void* wWidthBytes; void* wcBreakChar; void* wcDefaultChar; void* wcLastChar; void* wcFirstChar; scalar_t__ cGlyphs; TYPE_1__* pFontInfo; } ;
struct TYPE_5__ {int /*<<< orphan*/  dfReserved; int /*<<< orphan*/ * dfCharTable; int /*<<< orphan*/  dfCspace; int /*<<< orphan*/  dfBspace; int /*<<< orphan*/  dfAspace; int /*<<< orphan*/  dfFlags; int /*<<< orphan*/  dfAscent; int /*<<< orphan*/  dfWidthBytes; int /*<<< orphan*/  dfPixWidth; int /*<<< orphan*/  dfPixHeight; scalar_t__ dfBreakChar; scalar_t__ dfFirstChar; scalar_t__ dfDefaultChar; scalar_t__ dfLastChar; int /*<<< orphan*/  dfVersion; } ;
typedef  TYPE_1__* PFONTINFO16 ;
typedef  TYPE_2__* PBMFD_FACE ;
typedef  int /*<<< orphan*/  GLYPHENTRY30 ;
typedef  int /*<<< orphan*/  GLYPHENTRY20 ;
typedef  int DWORD ;
typedef  scalar_t__ CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int DFF_16COLOR ; 
 int DFF_1COLOR ; 
 int DFF_256COLOR ; 
 int DFF_FIXED ; 
 int DFF_RGBCOLOR ; 
 int /*<<< orphan*/  EngMultiByteToUnicodeN (void**,int,int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  FM_INFO_1BPP ; 
 int /*<<< orphan*/  FM_INFO_24BPP ; 
 int /*<<< orphan*/  FM_INFO_4BPP ; 
 int /*<<< orphan*/  FM_INFO_8BPP ; 
 int /*<<< orphan*/  FM_INFO_CONSTANT_WIDTH ; 
 int /*<<< orphan*/  FM_INFO_MASK ; 
 void* GETVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOL
FillFaceInfo(
    PBMFD_FACE pface,
    PFONTINFO16 pFontInfo)
{
    CHAR ansi[4];
    WCHAR unicode[4];
    ULONG written;
    DWORD dfFlags;

    pface->pFontInfo = pFontInfo;
    pface->ulVersion = GETVAL(pFontInfo->dfVersion);
    pface->cGlyphs = pFontInfo->dfLastChar - pFontInfo->dfFirstChar + 1;

    /* Convert chars to unicode */
    ansi[0] = pFontInfo->dfFirstChar;
    ansi[1] = pFontInfo->dfLastChar;
    ansi[2] = pFontInfo->dfFirstChar + pFontInfo->dfDefaultChar;
    ansi[3] = pFontInfo->dfFirstChar + pFontInfo->dfBreakChar;
    EngMultiByteToUnicodeN(unicode, 4 * sizeof(WCHAR), &written, ansi, 4);
    pface->wcFirstChar = unicode[0];
    pface->wcLastChar = unicode[1];
    pface->wcDefaultChar = unicode[2];
    pface->wcBreakChar = unicode[3];

    /* Copy some values */
    pface->wPixHeight = GETVAL(pFontInfo->dfPixHeight);
    pface->wPixWidth = GETVAL(pFontInfo->dfPixWidth);
    pface->wWidthBytes = GETVAL(pFontInfo->dfWidthBytes);
    pface->wAscent = GETVAL(pFontInfo->dfAscent);
    pface->wDescent = pface->wPixHeight - pface->wAscent;

    /* Some version specific members */
    if (pface->ulVersion >= 0x300)
    {
        dfFlags = GETVAL(pFontInfo->dfFlags);
        pface->wA = GETVAL(pFontInfo->dfAspace);
        pface->wB = GETVAL(pFontInfo->dfBspace);
        pface->wC = GETVAL(pFontInfo->dfCspace);
        pface->pCharTable = pFontInfo->dfCharTable;
        pface->cjEntrySize = sizeof(GLYPHENTRY30);
    }
    else
    {
        dfFlags = DFF_1COLOR;
        pface->wA = 0;
        pface->wB = 0;
        pface->wC = 0;
        pface->pCharTable = &pFontInfo->dfReserved + 1;
        pface->cjEntrySize = sizeof(GLYPHENTRY20);
    }

    pface->flInfo = FM_INFO_MASK;

    /* If dfWidth is non-null, we have a fixed width font */
    if (dfFlags & DFF_FIXED || pface->wPixWidth)
        pface->flInfo |= FM_INFO_CONSTANT_WIDTH;

    /* Initialize color depth flags */
    if (dfFlags & DFF_1COLOR)
        pface->flInfo |= FM_INFO_1BPP;
    else if (dfFlags & DFF_16COLOR)
        pface->flInfo |= FM_INFO_4BPP;
    else if (dfFlags & DFF_256COLOR)
        pface->flInfo |= FM_INFO_8BPP;
    else if (dfFlags & DFF_RGBCOLOR)
        pface->flInfo |= FM_INFO_24BPP;

    // TODO: walk through all glyphs and veryfy them and calculate max values

    // FIXME: After this point, the whole font data should be verified!

    return TRUE;
}