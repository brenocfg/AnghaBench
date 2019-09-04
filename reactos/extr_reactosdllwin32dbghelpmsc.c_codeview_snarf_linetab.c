#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ tag; } ;
struct symt_function {unsigned long address; unsigned long size; TYPE_1__ symt; } ;
struct startend {unsigned long start; } ;
struct p_string {int dummy; } ;
struct msc_debug_info {int /*<<< orphan*/  module; } ;
struct codeview_linetab_block {unsigned long* offsets; size_t num_lines; int /*<<< orphan*/  seg; } ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ SymTagFunction ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ,unsigned long,unsigned long,int) ; 
 unsigned long codeview_get_address (struct msc_debug_info const*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned int source_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  symt_add_func_line (int /*<<< orphan*/ ,struct symt_function*,unsigned int,unsigned short const,unsigned long) ; 
 scalar_t__ symt_find_nearest (int /*<<< orphan*/ ,unsigned long) ; 
 char const* terminate_string (struct p_string const*) ; 

__attribute__((used)) static void codeview_snarf_linetab(const struct msc_debug_info* msc_dbg, const BYTE* linetab,
                                   int size, BOOL pascal_str)
{
    const BYTE*                 ptr = linetab;
    int				nfile, nseg;
    int                         i, j;
    unsigned int                k;
    const unsigned int*         filetab;
    const unsigned int*         lt_ptr;
    const unsigned short*       linenos;
    const struct startend*      start;
    unsigned                    source;
    unsigned long               addr, func_addr0;
    struct symt_function*       func;
    const struct codeview_linetab_block* ltb;

    nfile = *(const short*)linetab;
    filetab = (const unsigned int*)(linetab + 2 * sizeof(short));

    for (i = 0; i < nfile; i++)
    {
        ptr = linetab + filetab[i];
        nseg = *(const short*)ptr;
        lt_ptr = (const unsigned int*)(ptr + 2 * sizeof(short));
        start = (const struct startend*)(lt_ptr + nseg);

        /*
         * Now snarf the filename for all of the segments for this file.
         */
        if (pascal_str)
            source = source_new(msc_dbg->module, NULL, terminate_string((const struct p_string*)(start + nseg)));
        else
            source = source_new(msc_dbg->module, NULL, (const char*)(start + nseg));

        for (j = 0; j < nseg; j++)
	{
            ltb = (const struct codeview_linetab_block*)(linetab + *lt_ptr++);
            linenos = (const unsigned short*)&ltb->offsets[ltb->num_lines];
            func_addr0 = codeview_get_address(msc_dbg, ltb->seg, start[j].start);
            if (!func_addr0) continue;
            for (func = NULL, k = 0; k < ltb->num_lines; k++)
            {
                /* now locate function (if any) */
                addr = func_addr0 + ltb->offsets[k] - start[j].start;
                /* unfortunately, we can have several functions in the same block, if there's no
                 * gap between them... find the new function if needed
                 */
                if (!func || addr >= func->address + func->size)
                {
                    func = (struct symt_function*)symt_find_nearest(msc_dbg->module, addr);
                    /* FIXME: at least labels support line numbers */
                    if (!func || func->symt.tag != SymTagFunction)
                    {
                        WARN("--not a func at %04x:%08x %lx tag=%d\n",
                             ltb->seg, ltb->offsets[k], addr, func ? func->symt.tag : -1);
                        func = NULL;
                        break;
                    }
                }
                symt_add_func_line(msc_dbg->module, func, source,
                                   linenos[k], addr - func->address);
            }
	}
    }
}