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
struct TYPE_4__ {int refs; } ;
typedef  TYPE_1__ fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* Memento_label (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_calloc (int /*<<< orphan*/ *,int,int) ; 

fz_device *
fz_new_device_of_size(fz_context *ctx, int size)
{
	fz_device *dev = Memento_label(fz_calloc(ctx, 1, size), "fz_device");
	dev->refs = 1;
	return dev;
}