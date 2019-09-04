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
struct TYPE_3__ {int /*<<< orphan*/  IDispatchEx_iface; } ;
typedef  TYPE_1__ jsdisp_t ;
typedef  int /*<<< orphan*/  IDispatch ;

/* Variables and functions */

__attribute__((used)) static inline IDispatch *to_disp(jsdisp_t *jsdisp)
{
    return (IDispatch*)&jsdisp->IDispatchEx_iface;
}