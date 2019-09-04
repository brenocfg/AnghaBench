#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_30__ {TYPE_2__* SubstLookupRecord; int /*<<< orphan*/  SubstCount; } ;
struct TYPE_29__ {int /*<<< orphan*/ * Backtrack; int /*<<< orphan*/  BacktrackGlyphCount; } ;
struct TYPE_28__ {int /*<<< orphan*/ * Input; int /*<<< orphan*/  InputGlyphCount; } ;
struct TYPE_27__ {int /*<<< orphan*/ * LookAhead; int /*<<< orphan*/  LookaheadGlyphCount; } ;
struct TYPE_26__ {TYPE_1__* SubstLookupRecord; int /*<<< orphan*/  SubstCount; } ;
struct TYPE_25__ {int /*<<< orphan*/ * ChainSubClassRule; int /*<<< orphan*/  ChainSubClassRuleCnt; } ;
struct TYPE_24__ {int /*<<< orphan*/  SubTableCount; } ;
struct TYPE_23__ {int /*<<< orphan*/  SequenceIndex; int /*<<< orphan*/  LookupListIndex; } ;
struct TYPE_22__ {int /*<<< orphan*/  SequenceIndex; int /*<<< orphan*/  LookupListIndex; } ;
struct TYPE_21__ {int /*<<< orphan*/  SubstFormat; } ;
struct TYPE_20__ {int /*<<< orphan*/ * ChainSubClassSet; int /*<<< orphan*/  ChainSubClassSetCnt; int /*<<< orphan*/  LookaheadClassDef; int /*<<< orphan*/  InputClassDef; int /*<<< orphan*/  BacktrackClassDef; int /*<<< orphan*/  Coverage; } ;
struct TYPE_19__ {int /*<<< orphan*/ * Coverage; int /*<<< orphan*/  BacktrackGlyphCount; } ;
struct TYPE_18__ {int /*<<< orphan*/ * Coverage; int /*<<< orphan*/  InputGlyphCount; } ;
struct TYPE_17__ {int /*<<< orphan*/ * Coverage; int /*<<< orphan*/  LookaheadGlyphCount; } ;
typedef  TYPE_3__ OT_LookupTable ;
typedef  int /*<<< orphan*/  OT_LookupList ;
typedef  int INT ;
typedef  TYPE_4__ GSUB_ChainSubClassSet ;
typedef  TYPE_5__ GSUB_ChainSubClassRule_4 ;
typedef  TYPE_6__ GSUB_ChainSubClassRule_3 ;
typedef  TYPE_7__ GSUB_ChainSubClassRule_2 ;
typedef  TYPE_8__ GSUB_ChainSubClassRule_1 ;
typedef  TYPE_9__ GSUB_ChainContextSubstFormat3_4 ;
typedef  TYPE_10__ GSUB_ChainContextSubstFormat3_3 ;
typedef  TYPE_11__ GSUB_ChainContextSubstFormat3_2 ;
typedef  TYPE_12__ GSUB_ChainContextSubstFormat3_1 ;
typedef  TYPE_13__ GSUB_ChainContextSubstFormat2 ;
typedef  TYPE_14__ GSUB_ChainContextSubstFormat1 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 int GSUB_E_NOGLYPH ; 
 int GSUB_apply_lookup (int /*<<< orphan*/  const*,unsigned int,int*,unsigned int,int,int*) ; 
 scalar_t__ GSUB_get_subtable (TYPE_3__ const*,int) ; 
 int GSUB_is_glyph_covered (int /*<<< orphan*/  const*,int) ; 
 int OT_get_glyph_class (void const*,int) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WARN (char*,unsigned int,int,int) ; 

__attribute__((used)) static INT GSUB_apply_ChainContextSubst(const OT_LookupList* lookup, const OT_LookupTable *look, WORD *glyphs, INT glyph_index, INT write_dir, INT *glyph_count)
{
    int j;

    TRACE("Chaining Contextual Substitution Subtable\n");
    for (j = 0; j < GET_BE_WORD(look->SubTableCount); j++)
    {
        const GSUB_ChainContextSubstFormat1 *ccsf1;
        int offset;
        int dirLookahead = write_dir;
        int dirBacktrack = -1 * write_dir;

        ccsf1 = (const GSUB_ChainContextSubstFormat1*)GSUB_get_subtable(look, j);
        if (GET_BE_WORD(ccsf1->SubstFormat) == 1)
        {
            static int once;
            if (!once++)
                FIXME("  TODO: subtype 1 (Simple context glyph substitution)\n");
            continue;
        }
        else if (GET_BE_WORD(ccsf1->SubstFormat) == 2)
        {
            WORD offset, count;
            const void *backtrack_class_table;
            const void *input_class_table;
            const void *lookahead_class_table;
            int i;
            WORD class;

            const GSUB_ChainContextSubstFormat2 *ccsf2 = (const GSUB_ChainContextSubstFormat2*)ccsf1;
            const GSUB_ChainSubClassSet *csc;

            TRACE("  subtype 2 (Class-based Chaining Context Glyph Substitution)\n");

            offset = GET_BE_WORD(ccsf2->Coverage);

            if (GSUB_is_glyph_covered((const BYTE*)ccsf2+offset, glyphs[glyph_index]) == -1)
            {
                TRACE("Glyph not covered\n");
                continue;
            }
            offset = GET_BE_WORD(ccsf2->BacktrackClassDef);
            backtrack_class_table = (const BYTE*)ccsf2+offset;
            offset = GET_BE_WORD(ccsf2->InputClassDef);
            input_class_table = (const BYTE*)ccsf2+offset;
            offset = GET_BE_WORD(ccsf2->LookaheadClassDef);
            lookahead_class_table = (const BYTE*)ccsf2+offset;
            count =  GET_BE_WORD(ccsf2->ChainSubClassSetCnt);

            class = OT_get_glyph_class(input_class_table, glyphs[glyph_index]);
            offset = GET_BE_WORD(ccsf2->ChainSubClassSet[class]);

            if (offset == 0)
            {
                TRACE("No rules for class\n");
                continue;
            }

            csc = (const GSUB_ChainSubClassSet*)((BYTE*)ccsf2+offset);
            count = GET_BE_WORD(csc->ChainSubClassRuleCnt);

            TRACE("%i rules to check\n",count);

            for (i = 0; i < count; i++)
            {
                WORD backtrack_count, input_count, lookahead_count, substitute_count;
                int k;
                const GSUB_ChainSubClassRule_1 *backtrack;
                const GSUB_ChainSubClassRule_2 *input;
                const GSUB_ChainSubClassRule_3 *lookahead;
                const GSUB_ChainSubClassRule_4 *substitute;
                int new_index = GSUB_E_NOGLYPH;

                offset = GET_BE_WORD(csc->ChainSubClassRule[i]);
                backtrack = (const GSUB_ChainSubClassRule_1 *)((BYTE *)csc + offset);
                backtrack_count = GET_BE_WORD(backtrack->BacktrackGlyphCount);
                k = glyph_index + dirBacktrack * backtrack_count;
                if (k < 0 || k >= *glyph_count)
                    continue;

                input = (const GSUB_ChainSubClassRule_2 *)&backtrack->Backtrack[backtrack_count];
                input_count = GET_BE_WORD(input->InputGlyphCount) - 1;
                k = glyph_index + write_dir * input_count;
                if (k < 0 || k >= *glyph_count)
                    continue;

                lookahead = (const GSUB_ChainSubClassRule_3 *)&input->Input[input_count];
                lookahead_count = GET_BE_WORD(lookahead->LookaheadGlyphCount);
                k = glyph_index + dirLookahead * (input_count + lookahead_count);
                if (k < 0 || k >= *glyph_count)
                    continue;

                substitute = (const GSUB_ChainSubClassRule_4 *)&lookahead->LookAhead[lookahead_count];

                for (k = 0; k < backtrack_count; ++k)
                {
                    WORD target_class = GET_BE_WORD(backtrack->Backtrack[k]);
                    WORD glyph_class = OT_get_glyph_class(backtrack_class_table, glyphs[glyph_index + (dirBacktrack * (k+1))]);
                    if (target_class != glyph_class)
                        break;
                }
                if (k != backtrack_count)
                    continue;
                TRACE("Matched Backtrack\n");

                for (k = 0; k < input_count; ++k)
                {
                    WORD target_class = GET_BE_WORD(input->Input[k]);
                    WORD glyph_class = OT_get_glyph_class(input_class_table, glyphs[glyph_index + (write_dir * (k+1))]);
                    if (target_class != glyph_class)
                        break;
                }
                if (k != input_count)
                    continue;
                TRACE("Matched IndexGlyphs\n");

                for (k = 0; k < lookahead_count; ++k)
                {
                    WORD target_class = GET_BE_WORD(lookahead->LookAhead[k]);
                    WORD glyph_class = OT_get_glyph_class(lookahead_class_table,
                            glyphs[glyph_index + (dirLookahead * (input_count + k + 1))]);
                    if (target_class != glyph_class)
                        break;
                }
                if (k != lookahead_count)
                    continue;
                TRACE("Matched LookAhead\n");

                substitute_count = GET_BE_WORD(substitute->SubstCount);
                for (k = 0; k < substitute_count; ++k)
                {
                    unsigned int lookup_index = GET_BE_WORD(substitute->SubstLookupRecord[k].LookupListIndex);
                    unsigned int sequence_index = GET_BE_WORD(substitute->SubstLookupRecord[k].SequenceIndex);
                    unsigned int g = glyph_index + write_dir * sequence_index;

                    if (g >= *glyph_count)
                    {
                        WARN("Skipping invalid sequence index %u (glyph index %u, write dir %d).\n",
                                sequence_index, glyph_index, write_dir);
                        continue;
                    }

                    TRACE("SUBST: %u -> %u %u.\n", k, sequence_index, lookup_index);
                    new_index = GSUB_apply_lookup(lookup, lookup_index, glyphs, g, write_dir, glyph_count);
                    if (new_index == GSUB_E_NOGLYPH)
                        ERR("Chain failed to generate a glyph.\n");
                }
                return new_index;
            }
        }
        else if (GET_BE_WORD(ccsf1->SubstFormat) == 3)
        {
            WORD backtrack_count, input_count, lookahead_count, substitution_count;
            int k;
            const GSUB_ChainContextSubstFormat3_1 *backtrack;
            const GSUB_ChainContextSubstFormat3_2 *input;
            const GSUB_ChainContextSubstFormat3_3 *lookahead;
            const GSUB_ChainContextSubstFormat3_4 *substitute;
            int new_index = GSUB_E_NOGLYPH;

            TRACE("  subtype 3 (Coverage-based Chaining Context Glyph Substitution)\n");

            backtrack = (const GSUB_ChainContextSubstFormat3_1 *)ccsf1;
            backtrack_count = GET_BE_WORD(backtrack->BacktrackGlyphCount);
            k = glyph_index + dirBacktrack * backtrack_count;
            if (k < 0 || k >= *glyph_count)
                continue;

            input = (const GSUB_ChainContextSubstFormat3_2 *)&backtrack->Coverage[backtrack_count];
            input_count = GET_BE_WORD(input->InputGlyphCount);
            k = glyph_index + write_dir * (input_count - 1);
            if (k < 0 || k >= *glyph_count)
                continue;

            lookahead = (const GSUB_ChainContextSubstFormat3_3 *)&input->Coverage[input_count];
            lookahead_count = GET_BE_WORD(lookahead->LookaheadGlyphCount);
            k = glyph_index + dirLookahead * (input_count + lookahead_count - 1);
            if (k < 0 || k >= *glyph_count)
                continue;

            substitute = (const GSUB_ChainContextSubstFormat3_4 *)&lookahead->Coverage[lookahead_count];

            for (k = 0; k < backtrack_count; ++k)
            {
                offset = GET_BE_WORD(backtrack->Coverage[k]);
                if (GSUB_is_glyph_covered((const BYTE *)ccsf1 + offset,
                        glyphs[glyph_index + (dirBacktrack * (k + 1))]) == -1)
                    break;
            }
            if (k != backtrack_count)
                continue;
            TRACE("Matched Backtrack\n");

            for (k = 0; k < input_count; ++k)
            {
                offset = GET_BE_WORD(input->Coverage[k]);
                if (GSUB_is_glyph_covered((const BYTE *)ccsf1 + offset,
                        glyphs[glyph_index + (write_dir * k)]) == -1)
                    break;
            }
            if (k != input_count)
                continue;
            TRACE("Matched IndexGlyphs\n");

            for (k = 0; k < lookahead_count; ++k)
            {
                offset = GET_BE_WORD(lookahead->Coverage[k]);
                if (GSUB_is_glyph_covered((const BYTE *)ccsf1 + offset,
                        glyphs[glyph_index + (dirLookahead * (input_count + k))]) == -1)
                    break;
            }
            if (k != lookahead_count)
                continue;
            TRACE("Matched LookAhead\n");

            substitution_count = GET_BE_WORD(substitute->SubstCount);
            for (k = 0; k < substitution_count; ++k)
            {
                unsigned int lookup_index = GET_BE_WORD(substitute->SubstLookupRecord[k].LookupListIndex);
                unsigned int sequence_index = GET_BE_WORD(substitute->SubstLookupRecord[k].SequenceIndex);
                unsigned int g = glyph_index + write_dir * sequence_index;

                if (g >= *glyph_count)
                {
                    WARN("Skipping invalid sequence index %u (glyph index %u, write dir %d).\n",
                            sequence_index, glyph_index, write_dir);
                    continue;
                }

                TRACE("SUBST: %u -> %u %u.\n", k, sequence_index, lookup_index);
                new_index = GSUB_apply_lookup(lookup, lookup_index, glyphs, g, write_dir, glyph_count);
                if (new_index == GSUB_E_NOGLYPH)
                    ERR("Chain failed to generate a glyph.\n");
            }
            return new_index;
        }
    }
    return GSUB_E_NOGLYPH;
}