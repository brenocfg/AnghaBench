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
typedef  int off_t ;
struct TYPE_3__ {int* ntom_val; int spf; int ntom_step; } ;
typedef  TYPE_1__ mpg123_handle ;

/* Variables and functions */
 int NTOM_MUL ; 

off_t ntom_frame_outsamples(mpg123_handle *fr)
{
	/* The do this before decoding the separate channels, so there is only one common ntom value. */
	int ntm = fr->ntom_val[0];
	ntm += fr->spf*fr->ntom_step;
	return ntm/NTOM_MUL;
}