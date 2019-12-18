#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTDv07_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTDv07_createDCtx_advanced (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defaultCustomMem ; 

ZSTDv07_DCtx* ZSTDv07_createDCtx(void)
{
    return ZSTDv07_createDCtx_advanced(defaultCustomMem);
}