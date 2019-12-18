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
typedef  int /*<<< orphan*/  vout_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSDWidget (int /*<<< orphan*/ *,int,short,int) ; 

void vout_OSDSlider(vout_thread_t *vout, int channel, int position, short type)
{
    OSDWidget(vout, channel, type, position);
}