#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_18__ {int /*<<< orphan*/  PosFormat; int /*<<< orphan*/ * PosClassSet; int /*<<< orphan*/  ClassDef; int /*<<< orphan*/  Coverage; } ;
struct TYPE_17__ {int /*<<< orphan*/  PosCount; int /*<<< orphan*/ * Class; int /*<<< orphan*/  GlyphCount; } ;
struct TYPE_16__ {TYPE_1__* PosLookupRecord; } ;
struct TYPE_15__ {int /*<<< orphan*/ * PosClassRule; int /*<<< orphan*/  PosClassRuleCnt; } ;
struct TYPE_14__ {int /*<<< orphan*/  SubTableCount; } ;
struct TYPE_13__ {int /*<<< orphan*/  fLogicalOrder; scalar_t__ fRTL; } ;
struct TYPE_12__ {int /*<<< orphan*/  SequenceIndex; int /*<<< orphan*/  LookupListIndex; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  TYPE_2__ SCRIPT_ANALYSIS ;
typedef  int /*<<< orphan*/  OUTLINETEXTMETRICW ;
typedef  TYPE_3__ OT_LookupTable ;
typedef  int /*<<< orphan*/  OT_LookupList ;
typedef  int /*<<< orphan*/  LOGFONTW ;
typedef  TYPE_4__ GPOS_PosClassSet ;
typedef  TYPE_5__ GPOS_PosClassRule_2 ;
typedef  TYPE_6__ GPOS_PosClassRule_1 ;
typedef  TYPE_7__ GPOS_ContextPosFormat2 ;
typedef  int /*<<< orphan*/  GOFFSET ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPOS_apply_lookup (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_2__ const*,int*,int /*<<< orphan*/  const*,unsigned int,int const*,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ GPOS_get_subtable (TYPE_3__ const*,int) ; 
 int GSUB_is_glyph_covered (int /*<<< orphan*/  const*,int const) ; 
 int OT_get_glyph_class (void const*,int const) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static unsigned int GPOS_apply_ContextPos(const ScriptCache *script_cache, const OUTLINETEXTMETRICW *otm,
        const LOGFONTW *logfont, const SCRIPT_ANALYSIS *analysis, int *advance, const OT_LookupList *lookup,
        const OT_LookupTable *look, const WORD *glyphs, unsigned int glyph_index, unsigned int glyph_count,
        GOFFSET *goffset)
{
    int j;
    int write_dir = (analysis->fRTL && !analysis->fLogicalOrder) ? -1 : 1;

    TRACE("Contextual Positioning Subtable\n");

    for (j = 0; j < GET_BE_WORD(look->SubTableCount); j++)
    {
        const GPOS_ContextPosFormat2 *cpf2 = (GPOS_ContextPosFormat2*)GPOS_get_subtable(look, j);

        if (GET_BE_WORD(cpf2->PosFormat) == 1)
        {
            static int once;
            if (!once++)
                FIXME("  TODO: subtype 1\n");
            continue;
        }
        else if (GET_BE_WORD(cpf2->PosFormat) == 2)
        {
            WORD offset = GET_BE_WORD(cpf2->Coverage);
            int index;

            TRACE("Contextual Positioning Subtable: Format 2\n");

            index = GSUB_is_glyph_covered((const BYTE*)cpf2+offset, glyphs[glyph_index]);
            TRACE("Coverage index %i\n",index);
            if (index != -1)
            {
                int k, count, class;
                const GPOS_PosClassSet *pcs;
                const void *glyph_class_table = NULL;

                offset = GET_BE_WORD(cpf2->ClassDef);
                glyph_class_table = (const BYTE *)cpf2 + offset;

                class = OT_get_glyph_class(glyph_class_table,glyphs[glyph_index]);

                offset = GET_BE_WORD(cpf2->PosClassSet[class]);
                if (offset == 0)
                {
                    TRACE("No class rule table for class %i\n",class);
                    continue;
                }
                pcs = (const GPOS_PosClassSet*)((const BYTE*)cpf2+offset);
                count = GET_BE_WORD(pcs->PosClassRuleCnt);
                TRACE("PosClassSet has %i members\n",count);
                for (k = 0; k < count; k++)
                {
                    const GPOS_PosClassRule_1 *pr;
                    const GPOS_PosClassRule_2 *pr_2;
                    unsigned int g;
                    int g_count, l;

                    offset = GET_BE_WORD(pcs->PosClassRule[k]);
                    pr = (const GPOS_PosClassRule_1*)((const BYTE*)pcs+offset);
                    g_count = GET_BE_WORD(pr->GlyphCount);
                    TRACE("PosClassRule has %i glyphs classes\n",g_count);

                    g = glyph_index + write_dir * (g_count - 1);
                    if (g >= glyph_count)
                        continue;

                    for (l = 0; l < g_count-1; l++)
                    {
                        int g_class = OT_get_glyph_class(glyph_class_table, glyphs[glyph_index + (write_dir * (l+1))]);
                        if (g_class != GET_BE_WORD(pr->Class[l])) break;
                    }

                    if (l < g_count-1)
                    {
                        TRACE("Rule does not match\n");
                        continue;
                    }

                    TRACE("Rule matches\n");
                    pr_2 = (const GPOS_PosClassRule_2 *)&pr->Class[g_count - 1];

                    for (l = 0; l < GET_BE_WORD(pr->PosCount); l++)
                    {
                        unsigned int lookup_index = GET_BE_WORD(pr_2->PosLookupRecord[l].LookupListIndex);
                        unsigned int sequence_index = GET_BE_WORD(pr_2->PosLookupRecord[l].SequenceIndex);

                        g = glyph_index + write_dir * sequence_index;
                        if (g >= glyph_count)
                        {
                            WARN("Invalid sequence index %u (glyph index %u, write dir %d).\n",
                                    sequence_index, glyph_index, write_dir);
                            continue;
                        }

                        TRACE("Position: %u -> %u %u.\n", l, sequence_index, lookup_index);

                        GPOS_apply_lookup(script_cache, otm, logfont, analysis, advance,
                                lookup, lookup_index, glyphs, g, glyph_count, goffset);
                    }
                    return 1;
                }
            }

            TRACE("Not covered\n");
            continue;
        }
        else if (GET_BE_WORD(cpf2->PosFormat) == 3)
        {
            static int once;
            if (!once++)
                FIXME("  TODO: subtype 3\n");
            continue;
        }
        else
            FIXME("Unhandled Contextual Positioning Format %i\n",GET_BE_WORD(cpf2->PosFormat));
    }
    return 1;
}