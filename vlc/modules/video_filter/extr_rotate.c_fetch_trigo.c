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
struct TYPE_4__ {int sin; int cos; int /*<<< orphan*/  u; } ;
typedef  TYPE_1__ sincos_t ;
struct TYPE_5__ {int /*<<< orphan*/  sincos; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_load (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fetch_trigo( filter_sys_t *sys, int *i_sin, int *i_cos )
{
    sincos_t sincos = { .u = atomic_load(&sys->sincos) };

    *i_sin = sincos.sin;
    *i_cos = sincos.cos;
}