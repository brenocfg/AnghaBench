#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sg_flags; } ;
typedef  TYPE_1__ fmd_serd_eng_t ;

/* Variables and functions */
 int FMD_SERD_FIRED ; 

int
fmd_serd_eng_fired(fmd_serd_eng_t *sgp)
{
	return (sgp->sg_flags & FMD_SERD_FIRED);
}