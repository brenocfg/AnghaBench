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
struct TYPE_3__ {int /*<<< orphan*/  line2; int /*<<< orphan*/  line1; } ;
typedef  TYPE_1__ exarg_T ;

/* Variables and functions */
 int /*<<< orphan*/  RangeEnd ; 
 int /*<<< orphan*/  RangeStart ; 

__attribute__((used)) static void
init_range_cmd(exarg_T *eap)
{
    RangeStart = eap->line1;
    RangeEnd = eap->line2;
}