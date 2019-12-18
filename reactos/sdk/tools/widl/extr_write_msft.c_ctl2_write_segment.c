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
struct TYPE_5__ {TYPE_1__* typelib_segdir; int /*<<< orphan*/ * typelib_segment_data; } ;
typedef  TYPE_2__ msft_typelib_t ;
struct TYPE_4__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctl2_write_segment(msft_typelib_t *typelib, int segment)
{
    put_data(typelib->typelib_segment_data[segment], typelib->typelib_segdir[segment].length);
}