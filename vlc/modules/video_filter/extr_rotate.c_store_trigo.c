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
struct TYPE_4__ {int /*<<< orphan*/  u; void* cos; void* sin; } ;
typedef  TYPE_1__ sincos_t ;
struct TYPE_5__ {int /*<<< orphan*/  sincos; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int M_PI ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 float cosf (float) ; 
 void* lroundf (float) ; 
 float sinf (float) ; 

__attribute__((used)) static void store_trigo( filter_sys_t *sys, float f_angle )
{
    sincos_t sincos;

    f_angle *= (float)(M_PI / 180.); /* degrees -> radians */

    sincos.sin = lroundf(sinf(f_angle) * 4096.f);
    sincos.cos = lroundf(cosf(f_angle) * 4096.f);
    atomic_store(&sys->sincos, sincos.u);
}