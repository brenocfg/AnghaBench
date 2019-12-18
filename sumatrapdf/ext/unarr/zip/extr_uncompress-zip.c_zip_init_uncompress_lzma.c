#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  Free; int /*<<< orphan*/  Alloc; } ;
struct TYPE_6__ {int /*<<< orphan*/  dec; int /*<<< orphan*/  finish; TYPE_1__ alloc; } ;
struct TYPE_5__ {TYPE_3__ lzma; } ;
struct ar_archive_zip_uncomp {TYPE_2__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_FINISH_ANY ; 
 int /*<<< orphan*/  LZMA_FINISH_END ; 
 int /*<<< orphan*/  LzmaDec_Construct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gLzma_Alloc ; 
 int /*<<< orphan*/  gLzma_Free ; 

__attribute__((used)) static bool zip_init_uncompress_lzma(struct ar_archive_zip_uncomp *uncomp, uint16_t flags)
{
    uncomp->state.lzma.alloc.Alloc = gLzma_Alloc;
    uncomp->state.lzma.alloc.Free = gLzma_Free;
    uncomp->state.lzma.finish = (flags & (1 << 1)) ? LZMA_FINISH_END : LZMA_FINISH_ANY;
    LzmaDec_Construct(&uncomp->state.lzma.dec);
    return true;
}