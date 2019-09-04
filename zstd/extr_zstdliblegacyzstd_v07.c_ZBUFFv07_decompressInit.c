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
typedef  int /*<<< orphan*/  ZBUFFv07_DCtx ;

/* Variables and functions */
 size_t ZBUFFv07_decompressInitDictionary (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

size_t ZBUFFv07_decompressInit(ZBUFFv07_DCtx* zbd)
{
    return ZBUFFv07_decompressInitDictionary(zbd, NULL, 0);
}