#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct module {int dummy; } ;
struct frame_info {int fde_encoding; unsigned long ip; } ;
struct TYPE_7__ {unsigned char* data; unsigned char* end_data; int /*<<< orphan*/  word_size; } ;
typedef  TYPE_1__ dwarf2_traverse_context_t ;
typedef  unsigned long DWORD_PTR ;
typedef  unsigned char BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 unsigned int DW_CIE_ID ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 scalar_t__ TRUE ; 
 unsigned long dwarf2_parse_augmentation_ptr (TYPE_1__*,int) ; 
 unsigned int dwarf2_parse_u4 (TYPE_1__*) ; 
 int /*<<< orphan*/  parse_cie_details (TYPE_1__*,struct frame_info*) ; 

__attribute__((used)) static BOOL dwarf2_get_cie(unsigned long addr, struct module* module, DWORD_PTR delta,
                           dwarf2_traverse_context_t* fde_ctx, dwarf2_traverse_context_t* cie_ctx,
                           struct frame_info* info, BOOL in_eh_frame)
{
    const unsigned char*        ptr_blk;
    const unsigned char*        cie_ptr;
    const unsigned char*        last_cie_ptr = (const unsigned char*)~0;
    unsigned                    len, id;
    unsigned long               start, range;
    unsigned                    cie_id;
    const BYTE*                 start_data = fde_ctx->data;

    cie_id = in_eh_frame ? 0 : DW_CIE_ID;
    /* skip 0-padding at beginning of section (alignment) */
    while (fde_ctx->data + 2 * 4 < fde_ctx->end_data)
    {
        if (dwarf2_parse_u4(fde_ctx))
        {
            fde_ctx->data -= 4;
            break;
        }
    }
    for (; fde_ctx->data + 2 * 4 < fde_ctx->end_data; fde_ctx->data = ptr_blk)
    {
        /* find the FDE for address addr (skip CIE) */
        len = dwarf2_parse_u4(fde_ctx);
        if (len == 0xffffffff) FIXME("Unsupported yet 64-bit CIEs\n");
        ptr_blk = fde_ctx->data + len;
        id  = dwarf2_parse_u4(fde_ctx);
        if (id == cie_id)
        {
            last_cie_ptr = fde_ctx->data - 8;
            /* we need some bits out of the CIE in order to parse all contents */
            if (!parse_cie_details(fde_ctx, info)) return FALSE;
            cie_ctx->data = fde_ctx->data;
            cie_ctx->end_data = ptr_blk;
            cie_ctx->word_size = fde_ctx->word_size;
            continue;
        }
        cie_ptr = (in_eh_frame) ? fde_ctx->data - id - 4 : start_data + id;
        if (cie_ptr != last_cie_ptr)
        {
            last_cie_ptr = cie_ptr;
            cie_ctx->data = cie_ptr;
            cie_ctx->word_size = fde_ctx->word_size;
            cie_ctx->end_data = cie_ptr + 4;
            cie_ctx->end_data = cie_ptr + 4 + dwarf2_parse_u4(cie_ctx);
            if (dwarf2_parse_u4(cie_ctx) != cie_id)
            {
                FIXME("wrong CIE pointer at %x from FDE %x\n",
                      (unsigned)(cie_ptr - start_data),
                      (unsigned)(fde_ctx->data - start_data));
                return FALSE;
            }
            if (!parse_cie_details(cie_ctx, info)) return FALSE;
        }
        start = delta + dwarf2_parse_augmentation_ptr(fde_ctx, info->fde_encoding);
        range = dwarf2_parse_augmentation_ptr(fde_ctx, info->fde_encoding & 0x0F);

        if (addr >= start && addr < start + range)
        {
            /* reset the FDE context */
            fde_ctx->end_data = ptr_blk;

            info->ip = start;
            return TRUE;
        }
    }
    return FALSE;
}