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
typedef  size_t WORD ;
struct TYPE_8__ {int /*<<< orphan*/  Coverage; int /*<<< orphan*/  DeltaGlyphID; int /*<<< orphan*/  SubstFormat; } ;
struct TYPE_7__ {int /*<<< orphan*/ * Substitute; int /*<<< orphan*/  GlyphCount; } ;
struct TYPE_6__ {int /*<<< orphan*/  SubTableCount; } ;
typedef  TYPE_1__ OT_LookupTable ;
typedef  size_t INT ;
typedef  TYPE_2__ GSUB_SingleSubstFormat2 ;
typedef  TYPE_3__ GSUB_SingleSubstFormat1 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t GET_BE_WORD (int /*<<< orphan*/ ) ; 
 size_t GSUB_E_NOGLYPH ; 
 scalar_t__ GSUB_get_subtable (TYPE_1__ const*,int) ; 
 int GSUB_is_glyph_covered (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static INT GSUB_apply_SingleSubst(const OT_LookupTable *look, WORD *glyphs, INT glyph_index, INT write_dir, INT *glyph_count)
{
    int j;
    TRACE("Single Substitution Subtable\n");

    for (j = 0; j < GET_BE_WORD(look->SubTableCount); j++)
    {
        const GSUB_SingleSubstFormat1 *ssf1 = (const GSUB_SingleSubstFormat1*)GSUB_get_subtable(look, j);
        if (GET_BE_WORD(ssf1->SubstFormat) == 1)
        {
            int offset = GET_BE_WORD(ssf1->Coverage);
            TRACE("  subtype 1, delta %i\n", GET_BE_WORD(ssf1->DeltaGlyphID));
            if (GSUB_is_glyph_covered((const BYTE*)ssf1+offset, glyphs[glyph_index]) != -1)
            {
                TRACE("  Glyph 0x%x ->",glyphs[glyph_index]);
                glyphs[glyph_index] = glyphs[glyph_index] + GET_BE_WORD(ssf1->DeltaGlyphID);
                TRACE(" 0x%x\n",glyphs[glyph_index]);
                return glyph_index + write_dir;
            }
        }
        else
        {
            const GSUB_SingleSubstFormat2 *ssf2;
            INT index;
            INT offset;

            ssf2 = (const GSUB_SingleSubstFormat2 *)ssf1;
            offset = GET_BE_WORD(ssf1->Coverage);
            TRACE("  subtype 2,  glyph count %i\n", GET_BE_WORD(ssf2->GlyphCount));
            index = GSUB_is_glyph_covered((const BYTE*)ssf2+offset, glyphs[glyph_index]);
            TRACE("  Coverage index %i\n",index);
            if (index != -1)
            {
                if (glyphs[glyph_index] == GET_BE_WORD(ssf2->Substitute[index]))
                    return GSUB_E_NOGLYPH;

                TRACE("    Glyph is 0x%x ->",glyphs[glyph_index]);
                glyphs[glyph_index] = GET_BE_WORD(ssf2->Substitute[index]);
                TRACE("0x%x\n",glyphs[glyph_index]);
                return glyph_index + write_dir;
            }
        }
    }
    return GSUB_E_NOGLYPH;
}