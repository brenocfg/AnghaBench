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
struct TYPE_18__ {int /*<<< orphan*/  PosFormat; int /*<<< orphan*/ * Coverage; int /*<<< orphan*/  BacktrackGlyphCount; } ;
struct TYPE_17__ {int /*<<< orphan*/ * Coverage; int /*<<< orphan*/  InputGlyphCount; } ;
struct TYPE_16__ {int /*<<< orphan*/ * Coverage; int /*<<< orphan*/  LookaheadGlyphCount; } ;
struct TYPE_15__ {TYPE_1__* PosLookupRecord; int /*<<< orphan*/  PosCount; } ;
struct TYPE_14__ {int /*<<< orphan*/  SubTableCount; } ;
struct TYPE_13__ {int /*<<< orphan*/  fLogicalOrder; scalar_t__ fRTL; } ;
struct TYPE_12__ {int /*<<< orphan*/  SequenceIndex; int /*<<< orphan*/  LookupListIndex; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  TYPE_2__ SCRIPT_ANALYSIS ;
typedef  int /*<<< orphan*/  OUTLINETEXTMETRICW ;
typedef  TYPE_3__ OT_LookupTable ;
typedef  int /*<<< orphan*/  OT_LookupList ;
typedef  int /*<<< orphan*/  LOGFONTW ;
typedef  TYPE_4__ GPOS_ChainContextPosFormat3_4 ;
typedef  TYPE_5__ GPOS_ChainContextPosFormat3_3 ;
typedef  TYPE_6__ GPOS_ChainContextPosFormat3_2 ;
typedef  TYPE_7__ GPOS_ChainContextPosFormat3_1 ;
typedef  int /*<<< orphan*/  GOFFSET ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPOS_apply_lookup (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_2__ const*,int*,int /*<<< orphan*/  const*,unsigned int,int const*,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ GPOS_get_subtable (TYPE_3__ const*,int) ; 
 int GSUB_is_glyph_covered (int /*<<< orphan*/  const*,int const) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,unsigned int,unsigned int,int) ; 

__attribute__((used)) static unsigned int GPOS_apply_ChainContextPos(const ScriptCache *script_cache, const OUTLINETEXTMETRICW *otm,
        const LOGFONTW *logfont, const SCRIPT_ANALYSIS *analysis, int *advance, const OT_LookupList *lookup,
        const OT_LookupTable *look, const WORD *glyphs, unsigned int glyph_index, unsigned int glyph_count,
        GOFFSET *goffset)
{
    int j;
    int write_dir = (analysis->fRTL && !analysis->fLogicalOrder) ? -1 : 1;

    TRACE("Chaining Contextual Positioning Subtable\n");

    for (j = 0; j < GET_BE_WORD(look->SubTableCount); j++)
    {
        int offset;
        const GPOS_ChainContextPosFormat3_1 *backtrack = (GPOS_ChainContextPosFormat3_1 *)GPOS_get_subtable(look, j);
        int dirLookahead = write_dir;
        int dirBacktrack = -1 * write_dir;

        if (GET_BE_WORD(backtrack->PosFormat) == 1)
        {
            static int once;
            if (!once++)
                FIXME("  TODO: subtype 1 (Simple Chaining Context Glyph Positioning)\n");
            continue;
        }
        else if (GET_BE_WORD(backtrack->PosFormat) == 2)
        {
            static int once;
            if (!once++)
                FIXME("  TODO: subtype 2 (Class-based Chaining Context Glyph Positioning)\n");
            continue;
        }
        else if (GET_BE_WORD(backtrack->PosFormat) == 3)
        {
            WORD backtrack_count, input_count, lookahead_count, positioning_count;
            int k;
            const GPOS_ChainContextPosFormat3_2 *input;
            const GPOS_ChainContextPosFormat3_3 *lookahead;
            const GPOS_ChainContextPosFormat3_4 *positioning;

            TRACE("  subtype 3 (Coverage-based Chaining Context Glyph Positioning)\n");

            backtrack_count = GET_BE_WORD(backtrack->BacktrackGlyphCount);
            k = glyph_index + dirBacktrack * backtrack_count;
            if (k < 0 || k >= glyph_count)
                continue;

            input = (const GPOS_ChainContextPosFormat3_2 *)&backtrack->Coverage[backtrack_count];
            input_count = GET_BE_WORD(input->InputGlyphCount);
            k = glyph_index + write_dir * (input_count - 1);
            if (k < 0 || k >= glyph_count)
                continue;

            lookahead = (const GPOS_ChainContextPosFormat3_3 *)&input->Coverage[input_count];
            lookahead_count = GET_BE_WORD(lookahead->LookaheadGlyphCount);
            k = glyph_index + dirLookahead * (input_count + lookahead_count - 1);
            if (k < 0 || k >= glyph_count)
                continue;

            positioning = (const GPOS_ChainContextPosFormat3_4 *)&lookahead->Coverage[lookahead_count];

            for (k = 0; k < backtrack_count; ++k)
            {
                offset = GET_BE_WORD(backtrack->Coverage[k]);
                if (GSUB_is_glyph_covered((const BYTE *)backtrack + offset,
                        glyphs[glyph_index + (dirBacktrack * (k + 1))]) == -1)
                    break;
            }
            if (k != backtrack_count)
                continue;
            TRACE("Matched Backtrack\n");

            for (k = 0; k < input_count; ++k)
            {
                offset = GET_BE_WORD(input->Coverage[k]);
                if (GSUB_is_glyph_covered((const BYTE *)backtrack + offset,
                        glyphs[glyph_index + (write_dir * k)]) == -1)
                    break;
            }
            if (k != input_count)
                continue;
            TRACE("Matched IndexGlyphs\n");

            for (k = 0; k < lookahead_count; ++k)
            {
                offset = GET_BE_WORD(lookahead->Coverage[k]);
                if (GSUB_is_glyph_covered((const BYTE *)backtrack + offset,
                        glyphs[glyph_index + (dirLookahead * (input_count + k))]) == -1)
                    break;
            }
            if (k != lookahead_count)
                continue;
            TRACE("Matched LookAhead\n");

            if (!(positioning_count = GET_BE_WORD(positioning->PosCount)))
                return 1;

            for (k = 0; k < positioning_count; ++k)
            {
                unsigned int lookup_index = GET_BE_WORD(positioning->PosLookupRecord[k].LookupListIndex);
                unsigned int sequence_index = GET_BE_WORD(positioning->PosLookupRecord[k].SequenceIndex);
                unsigned int g = glyph_index + write_dir * sequence_index;

                if (g >= glyph_count)
                {
                    WARN("Skipping invalid sequence index %u (glyph index %u, write dir %d).\n",
                            sequence_index, glyph_index, write_dir);
                    continue;
                }

                TRACE("Position: %u -> %u %u.\n", k, sequence_index, lookup_index);
                GPOS_apply_lookup(script_cache, otm, logfont, analysis, advance, lookup, lookup_index,
                        glyphs, g, glyph_count, goffset);
            }
            return input_count + lookahead_count;
        }
        else
            FIXME("Unhandled Chaining Contextual Positioning Format %#x.\n", GET_BE_WORD(backtrack->PosFormat));
    }
    return 1;
}