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
struct TYPE_2__ {size_t expected; } ;
typedef  TYPE_1__ dctx_t ;
typedef  int /*<<< orphan*/  ZSTDv01_Dctx ;

/* Variables and functions */

size_t ZSTDv01_nextSrcSizeToDecompress(ZSTDv01_Dctx* dctx)
{
    return ((dctx_t*)dctx)->expected;
}