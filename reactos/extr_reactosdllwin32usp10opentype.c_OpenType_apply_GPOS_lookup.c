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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_6__ {int /*<<< orphan*/  LookupList; } ;
struct TYPE_5__ {scalar_t__ GPOS_Table; } ;
typedef  TYPE_1__ ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  int /*<<< orphan*/  OUTLINETEXTMETRICW ;
typedef  int /*<<< orphan*/  OT_LookupList ;
typedef  int /*<<< orphan*/  LOGFONTW ;
typedef  TYPE_2__ GPOS_Header ;
typedef  int /*<<< orphan*/  GOFFSET ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 unsigned int GPOS_apply_lookup (TYPE_1__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int*,int /*<<< orphan*/  const*,unsigned int,int /*<<< orphan*/  const*,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 

unsigned int OpenType_apply_GPOS_lookup(const ScriptCache *script_cache, const OUTLINETEXTMETRICW *otm,
        const LOGFONTW *logfont, const SCRIPT_ANALYSIS *analysis, int *advance, unsigned int lookup_index,
        const WORD *glyphs, unsigned int glyph_index, unsigned int glyph_count, GOFFSET *goffset)
{
    const GPOS_Header *header = (const GPOS_Header *)script_cache->GPOS_Table;
    const OT_LookupList *lookup = (const OT_LookupList*)((const BYTE*)header + GET_BE_WORD(header->LookupList));

    return GPOS_apply_lookup(script_cache, otm, logfont, analysis, advance, lookup,
            lookup_index, glyphs, glyph_index, glyph_count, goffset);
}