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
struct TYPE_3__ {int var; scalar_t__ avg; } ;
typedef  TYPE_1__ vout_chrono_t ;
typedef  int /*<<< orphan*/  vlc_tick_t ;

/* Variables and functions */
 int /*<<< orphan*/  __MAX (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline vlc_tick_t vout_chrono_GetLow(vout_chrono_t *chrono)
{
    return __MAX(chrono->avg - 2 * chrono->var, 0);
}