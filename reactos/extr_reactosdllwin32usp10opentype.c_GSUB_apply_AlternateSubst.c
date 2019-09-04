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
typedef  scalar_t__ WORD ;
struct TYPE_8__ {int /*<<< orphan*/ * Alternate; int /*<<< orphan*/  GlyphCount; } ;
struct TYPE_7__ {int /*<<< orphan*/ * AlternateSet; int /*<<< orphan*/  Coverage; } ;
struct TYPE_6__ {int /*<<< orphan*/  SubTableCount; } ;
typedef  TYPE_1__ OT_LookupTable ;
typedef  size_t INT ;
typedef  TYPE_2__ GSUB_AlternateSubstFormat1 ;
typedef  TYPE_3__ GSUB_AlternateSet ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 scalar_t__ GET_BE_WORD (int /*<<< orphan*/ ) ; 
 size_t GSUB_E_NOGLYPH ; 
 scalar_t__ GSUB_get_subtable (TYPE_1__ const*,int) ; 
 size_t GSUB_is_glyph_covered (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static INT GSUB_apply_AlternateSubst(const OT_LookupTable *look, WORD *glyphs, INT glyph_index, INT write_dir, INT *glyph_count)
{
    int j;
    TRACE("Alternate Substitution Subtable\n");

    for (j = 0; j < GET_BE_WORD(look->SubTableCount); j++)
    {
        int offset;
        const GSUB_AlternateSubstFormat1 *asf1;
        INT index;

        asf1 = (const GSUB_AlternateSubstFormat1*)GSUB_get_subtable(look, j);
        offset = GET_BE_WORD(asf1->Coverage);

        index = GSUB_is_glyph_covered((const BYTE*)asf1+offset, glyphs[glyph_index]);
        if (index != -1)
        {
            const GSUB_AlternateSet *as;
            offset =  GET_BE_WORD(asf1->AlternateSet[index]);
            as = (const GSUB_AlternateSet*)((const BYTE*)asf1+offset);
            FIXME("%i alternates, picking index 0\n",GET_BE_WORD(as->GlyphCount));
            if (glyphs[glyph_index] == GET_BE_WORD(as->Alternate[0]))
                return GSUB_E_NOGLYPH;

            TRACE("  Glyph 0x%x ->",glyphs[glyph_index]);
            glyphs[glyph_index] = GET_BE_WORD(as->Alternate[0]);
            TRACE(" 0x%x\n",glyphs[glyph_index]);
            return glyph_index + write_dir;
        }
    }
    return GSUB_E_NOGLYPH;
}