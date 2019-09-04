#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* dwarf2_info; } ;
struct module_format {TYPE_3__ u; } ;
struct TYPE_9__ {int /*<<< orphan*/  word_size; int /*<<< orphan*/  const* end_data; int /*<<< orphan*/  const* data; } ;
typedef  TYPE_4__ dwarf2_traverse_context_t ;
struct TYPE_6__ {int size; int /*<<< orphan*/  const* address; } ;
struct TYPE_7__ {int /*<<< orphan*/  word_size; TYPE_1__ debug_loc; } ;
typedef  unsigned long DWORD_PTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 unsigned long dwarf2_get_addr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int dwarf2_get_u2 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL dwarf2_lookup_loclist(const struct module_format* modfmt, const BYTE* start,
                                  unsigned long ip, dwarf2_traverse_context_t* lctx)
{
    DWORD_PTR                   beg, end;
    const BYTE*                 ptr = start;
    DWORD                       len;

    while (ptr < modfmt->u.dwarf2_info->debug_loc.address + modfmt->u.dwarf2_info->debug_loc.size)
    {
        beg = dwarf2_get_addr(ptr, modfmt->u.dwarf2_info->word_size); ptr += modfmt->u.dwarf2_info->word_size;
        end = dwarf2_get_addr(ptr, modfmt->u.dwarf2_info->word_size); ptr += modfmt->u.dwarf2_info->word_size;
        if (!beg && !end) break;
        len = dwarf2_get_u2(ptr); ptr += 2;

        if (beg <= ip && ip < end)
        {
            lctx->data = ptr;
            lctx->end_data = ptr + len;
            lctx->word_size = modfmt->u.dwarf2_info->word_size;
            return TRUE;
        }
        ptr += len;
    }
    WARN("Couldn't find ip in location list\n");
    return FALSE;
}