#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_4__ {int /*<<< orphan*/ * ntom_val; } ;
typedef  TYPE_1__ mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ntom_val (TYPE_1__*,int /*<<< orphan*/ ) ; 

void ntom_set_ntom(mpg123_handle *fr, off_t num)
{
	fr->ntom_val[1] = fr->ntom_val[0] = ntom_val(fr, num);
}