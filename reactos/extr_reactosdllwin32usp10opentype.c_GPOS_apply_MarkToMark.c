#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_20__ {int /*<<< orphan*/ * Mark2Anchor; } ;
struct TYPE_19__ {TYPE_4__* MarkRecord; int /*<<< orphan*/  MarkCount; } ;
struct TYPE_18__ {int /*<<< orphan*/  PosFormat; int /*<<< orphan*/  Mark2Array; int /*<<< orphan*/  Mark1Array; int /*<<< orphan*/  ClassCount; int /*<<< orphan*/  Mark2Coverage; int /*<<< orphan*/  Mark1Coverage; } ;
struct TYPE_17__ {int /*<<< orphan*/  MarkAnchor; int /*<<< orphan*/  Class; } ;
struct TYPE_16__ {int /*<<< orphan*/  SubTableCount; } ;
struct TYPE_15__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_14__ {int /*<<< orphan*/  fLogicalOrder; scalar_t__ fRTL; } ;
typedef  TYPE_1__ SCRIPT_ANALYSIS ;
typedef  TYPE_2__ POINT ;
typedef  TYPE_3__ OT_LookupTable ;
typedef  TYPE_4__ GPOS_MarkRecord ;
typedef  TYPE_5__ GPOS_MarkMarkPosFormat1 ;
typedef  TYPE_6__ GPOS_MarkArray ;
typedef  TYPE_7__ GPOS_Mark2Record ;
typedef  int /*<<< orphan*/  GPOS_Mark2Array ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPOS_get_anchor_values (int /*<<< orphan*/  const*,TYPE_2__*,unsigned int) ; 
 scalar_t__ GPOS_get_subtable (TYPE_3__ const*,int) ; 
 int GSUB_is_glyph_covered (int /*<<< orphan*/  const*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wine_dbgstr_point (TYPE_2__*) ; 

__attribute__((used)) static BOOL GPOS_apply_MarkToMark(const OT_LookupTable *look, const SCRIPT_ANALYSIS *analysis,
        const WORD *glyphs, unsigned int glyph_index, unsigned int glyph_count, unsigned int ppem, POINT *pt)
{
    int j;
    BOOL rc = FALSE;
    int write_dir = (analysis->fRTL && !analysis->fLogicalOrder) ? -1 : 1;

    TRACE("MarkToMark Attachment Positioning Subtable\n");

    for (j = 0; j < GET_BE_WORD(look->SubTableCount); j++)
    {
        const GPOS_MarkMarkPosFormat1 *mmpf1 = (const GPOS_MarkMarkPosFormat1 *)GPOS_get_subtable(look, j);
        if (GET_BE_WORD(mmpf1->PosFormat) == 1)
        {
            int offset = GET_BE_WORD(mmpf1->Mark1Coverage);
            int mark_index;
            mark_index = GSUB_is_glyph_covered((const BYTE*)mmpf1+offset, glyphs[glyph_index]);
            if (mark_index != -1)
            {
                int mark2_index;
                offset = GET_BE_WORD(mmpf1->Mark2Coverage);
                mark2_index = GSUB_is_glyph_covered((const BYTE*)mmpf1+offset, glyphs[glyph_index - write_dir]);
                if (mark2_index != -1)
                {
                    const GPOS_MarkArray *ma;
                    const GPOS_MarkRecord *mr;
                    const GPOS_Mark2Array *m2a;
                    const GPOS_Mark2Record *m2r;
                    int mark_class;
                    int class_count = GET_BE_WORD(mmpf1->ClassCount);
                    int mark2record_size;
                    POINT mark2_pt;
                    POINT mark_pt;
                    TRACE("Mark %x(%i) and Mark2 %x(%i)\n",glyphs[glyph_index], mark_index, glyphs[glyph_index - write_dir], mark2_index);
                    offset = GET_BE_WORD(mmpf1->Mark1Array);
                    ma = (const GPOS_MarkArray*)((const BYTE*)mmpf1 + offset);
                    if (mark_index > GET_BE_WORD(ma->MarkCount))
                    {
                        ERR("Mark index exceeded mark count\n");
                        return FALSE;
                    }
                    mr = &ma->MarkRecord[mark_index];
                    mark_class = GET_BE_WORD(mr->Class);
                    TRACE("Mark Class %i total classes %i\n",mark_class,class_count);
                    offset = GET_BE_WORD(mmpf1->Mark2Array);
                    m2a = (const GPOS_Mark2Array*)((const BYTE*)mmpf1 + offset);
                    mark2record_size = class_count * sizeof(WORD);
                    m2r = (const GPOS_Mark2Record*)((const BYTE*)m2a + sizeof(WORD) + (mark2record_size * mark2_index));
                    offset = GET_BE_WORD(m2r->Mark2Anchor[mark_class]);
                    GPOS_get_anchor_values((const BYTE*)m2a + offset, &mark2_pt, ppem);
                    offset = GET_BE_WORD(mr->MarkAnchor);
                    GPOS_get_anchor_values((const BYTE*)ma + offset, &mark_pt, ppem);
                    TRACE("Offset on mark2 is %s design units\n",wine_dbgstr_point(&mark2_pt));
                    TRACE("Offset on mark is %s design units\n",wine_dbgstr_point(&mark_pt));
                    pt->x += mark2_pt.x - mark_pt.x;
                    pt->y += mark2_pt.y - mark_pt.y;
                    TRACE("Resulting cumulative offset is %s design units\n",wine_dbgstr_point(pt));
                    rc = TRUE;
                }
            }
        }
        else
            FIXME("Unhandled Mark To Mark Format %i\n",GET_BE_WORD(mmpf1->PosFormat));
    }
    return rc;
}