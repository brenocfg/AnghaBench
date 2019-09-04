#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* typelib_segdir; } ;
typedef  TYPE_1__ msft_typelib_t ;
struct TYPE_5__ {int offset; int res08; int res0c; scalar_t__ length; } ;
typedef  TYPE_2__ MSFT_pSeg ;

/* Variables and functions */
 int MSFT_SEG_MAX ; 
 size_t MSFT_SEG_TYPEINFO ; 

__attribute__((used)) static void ctl2_init_segdir(
	msft_typelib_t *typelib) /* [I] The typelib to initialize. */
{
    int i;
    MSFT_pSeg *segdir;

    segdir = &typelib->typelib_segdir[MSFT_SEG_TYPEINFO];

    for (i = 0; i < MSFT_SEG_MAX; i++) {
	segdir[i].offset = -1;
	segdir[i].length = 0;
	segdir[i].res08 = -1;
	segdir[i].res0c = 0x0f;
    }
}