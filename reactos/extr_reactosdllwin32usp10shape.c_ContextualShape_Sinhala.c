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
typedef  int /*<<< orphan*/  WORD ;
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  int IndicSyllable ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  DecomposeVowels (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GetGlyphIndicesW (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Indic_ReorderCharacters (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Reorder_Like_Sinhala ; 
 int /*<<< orphan*/  ShapeIndicSyllables (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int,int*,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sinhala_vowels ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_wn (int*,int) ; 
 int* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  sinhala_lex ; 

__attribute__((used)) static void ContextualShape_Sinhala(HDC hdc, ScriptCache *psc, SCRIPT_ANALYSIS *psa, WCHAR* pwcChars, INT cChars, WORD* pwOutGlyphs, INT* pcGlyphs, INT cMaxGlyphs, WORD *pwLogClust)
{
    int cCount = cChars;
    int i;
    WCHAR *input;
    IndicSyllable *syllables = NULL;
    int syllable_count = 0;

    if (*pcGlyphs != cChars)
    {
        ERR("Number of Glyphs and Chars need to match at the beginning\n");
        return;
    }

    input = heap_alloc(3 * cChars * sizeof(*input));

    memcpy(input, pwcChars, cChars * sizeof(WCHAR));

    /* Step 1:  Decompose multi part vowels */
    DecomposeVowels(hdc, input,  &cCount, Sinhala_vowels, pwLogClust, cChars);

    TRACE("New double vowel expanded string %s (%i)\n",debugstr_wn(input,cCount),cCount);

    /* Step 2:  Reorder within Syllables */
    Indic_ReorderCharacters( hdc, psa, psc, input, cCount, &syllables, &syllable_count, sinhala_lex, Reorder_Like_Sinhala, TRUE);
    TRACE("reordered string %s\n",debugstr_wn(input,cCount));

    /* Step 3:  Strip dangling joiners */
    for (i = 0; i < cCount; i++)
    {
        if ((input[i] == 0x200D || input[i] == 0x200C) &&
            (i == 0 || input[i-1] == 0x0020 || i == cCount-1 || input[i+1] == 0x0020))
            input[i] = 0x0020;
    }

    /* Step 4: Base Form application to syllables */
    GetGlyphIndicesW(hdc, input, cCount, pwOutGlyphs, 0);
    *pcGlyphs = cCount;
    ShapeIndicSyllables(hdc, psc, psa, input, cChars, syllables, syllable_count, pwOutGlyphs, pcGlyphs, pwLogClust, sinhala_lex, NULL, TRUE);

    heap_free(input);
    heap_free(syllables);
}