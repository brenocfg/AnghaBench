#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int WCHAR ;
struct TYPE_13__ {scalar_t__ fRTL; scalar_t__ fLogicalOrder; } ;
struct TYPE_12__ {int fCanGlyphAlone; } ;
struct TYPE_10__ {void* uJustification; } ;
struct TYPE_11__ {TYPE_1__ sva; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  TYPE_2__ SCRIPT_GLYPHPROP ;
typedef  TYPE_3__ SCRIPT_CHARPROP ;
typedef  TYPE_4__ SCRIPT_ANALYSIS ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  OpenType_GDEF_UpdateGlyphProps (int /*<<< orphan*/ *,int const*,int const,int*,int const,TYPE_2__*) ; 
 void* SCRIPT_JUSTIFY_ARABIC_ALEF ; 
 void* SCRIPT_JUSTIFY_ARABIC_BA ; 
 void* SCRIPT_JUSTIFY_ARABIC_BARA ; 
 void* SCRIPT_JUSTIFY_ARABIC_BLANK ; 
 void* SCRIPT_JUSTIFY_ARABIC_HA ; 
 void* SCRIPT_JUSTIFY_ARABIC_KASHIDA ; 
 void* SCRIPT_JUSTIFY_ARABIC_NORMAL ; 
 void* SCRIPT_JUSTIFY_ARABIC_RA ; 
 void* SCRIPT_JUSTIFY_ARABIC_SEEN ; 
 void* SCRIPT_JUSTIFY_ARABIC_SEEN_M ; 
 void* SCRIPT_JUSTIFY_NONE ; 
 int USP10_FindGlyphInLogClust (int*,int const,int) ; 
 int /*<<< orphan*/  UpdateClustersFromGlyphProp (int const,int const,int*,TYPE_2__*) ; 
 int* heap_alloc (int const) ; 
 int /*<<< orphan*/  heap_free (int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void ShapeCharGlyphProp_Arabic( HDC hdc, ScriptCache *psc, SCRIPT_ANALYSIS *psa, const WCHAR* pwcChars, const INT cChars, const WORD* pwGlyphs, const INT cGlyphs, WORD *pwLogClust, SCRIPT_CHARPROP *pCharProp, SCRIPT_GLYPHPROP *pGlyphProp )
{
    int i,k;
    int initGlyph, finaGlyph;
    INT dirR, dirL;
    BYTE *spaces;

    spaces = heap_alloc(cGlyphs);
    memset(spaces,0,cGlyphs);

    if (psa->fLogicalOrder && psa->fRTL)
    {
        initGlyph = 0;
        finaGlyph = cGlyphs-1;
        dirR = -1;
        dirL = 1;
    }
    else
    {
        initGlyph = cGlyphs-1;
        finaGlyph = 0;
        dirR = 1;
        dirL = -1;
    }

    for (i = 0; i < cGlyphs; i++)
    {
        for (k = 0; k < cChars; k++)
            if (pwLogClust[k] == i)
            {
                if (pwcChars[k] == 0x0020)
                    spaces[i] = 1;
            }
    }

    for (i = 0; i < cGlyphs; i++)
    {
        int char_index[20];
        int char_count = 0;
        BOOL isInit, isFinal;

        k = USP10_FindGlyphInLogClust(pwLogClust, cChars, i);
        if (k>=0)
        {
            for (; k < cChars && pwLogClust[k] == i; k++)
                char_index[char_count++] = k;
        }

        isInit = (i == initGlyph || (i+dirR > 0 && i+dirR < cGlyphs && spaces[i+dirR]));
        isFinal = (i == finaGlyph || (i+dirL > 0 && i+dirL < cGlyphs && spaces[i+dirL]));

        if (char_count == 0)
            continue;

        if (char_count == 1)
        {
            if (pwcChars[char_index[0]] == 0x0020)  /* space */
            {
                pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_ARABIC_BLANK;
                pCharProp[char_index[0]].fCanGlyphAlone = 1;
            }
            else if (pwcChars[char_index[0]] == 0x0640)  /* kashida */
                pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_ARABIC_KASHIDA;
            else if (pwcChars[char_index[0]] == 0x0633)  /* SEEN */
            {
                if (!isInit && !isFinal)
                    pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_ARABIC_SEEN_M;
                else if (isInit)
                    pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_ARABIC_SEEN;
                else
                    pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_NONE;
            }
            else if (!isInit)
            {
                if (pwcChars[char_index[0]] == 0x0628 ) /* BA */
                    pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_ARABIC_BA;
                else if (pwcChars[char_index[0]] == 0x0631 ) /* RA */
                    pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_ARABIC_RA;
                else if (pwcChars[char_index[0]] == 0x0647 ) /* HA */
                    pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_ARABIC_HA;
                else if ((pwcChars[char_index[0]] == 0x0627 || pwcChars[char_index[0]] == 0x0625 || pwcChars[char_index[0]] == 0x0623 || pwcChars[char_index[0]] == 0x0622) ) /* alef-like */
                    pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_ARABIC_ALEF;
                else
                    pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_NONE;
            }
            else if (!isInit && !isFinal)
                pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_ARABIC_NORMAL;
            else
                pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_NONE;
        }
        else if (char_count == 2)
        {
            if ((pwcChars[char_index[0]] == 0x0628 && pwcChars[char_index[1]]== 0x0631) ||  (pwcChars[char_index[0]] == 0x0631 && pwcChars[char_index[1]]== 0x0628)) /* BA+RA */
                pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_ARABIC_BARA;
            else if (!isInit)
                pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_ARABIC_NORMAL;
            else
                pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_NONE;
        }
        else if (!isInit && !isFinal)
            pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_ARABIC_NORMAL;
        else
            pGlyphProp[i].sva.uJustification = SCRIPT_JUSTIFY_NONE;
    }

    OpenType_GDEF_UpdateGlyphProps(psc, pwGlyphs, cGlyphs, pwLogClust, cChars, pGlyphProp);
    UpdateClustersFromGlyphProp(cGlyphs, cChars, pwLogClust, pGlyphProp);
    heap_free(spaces);
}