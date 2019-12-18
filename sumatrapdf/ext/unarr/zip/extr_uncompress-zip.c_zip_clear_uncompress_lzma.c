#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  alloc; int /*<<< orphan*/  dec; } ;
struct TYPE_4__ {TYPE_1__ lzma; } ;
struct ar_archive_zip_uncomp {TYPE_2__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  LzmaDec_Free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zip_clear_uncompress_lzma(struct ar_archive_zip_uncomp *uncomp)
{
    LzmaDec_Free(&uncomp->state.lzma.dec, &uncomp->state.lzma.alloc);
}