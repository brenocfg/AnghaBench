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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t i_extra; int /*<<< orphan*/ * p_extra; } ;
typedef  TYPE_1__ mux_extradata_builder_t ;

/* Variables and functions */

size_t mux_extradata_builder_Get(mux_extradata_builder_t *m, const uint8_t **a)
{
    *a = m->p_extra;
    return m->i_extra;
}