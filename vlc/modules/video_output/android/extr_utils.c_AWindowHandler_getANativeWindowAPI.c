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
typedef  int /*<<< orphan*/  native_window_api_t ;
struct TYPE_3__ {int /*<<< orphan*/  anw_api; } ;
typedef  TYPE_1__ AWindowHandler ;

/* Variables and functions */

native_window_api_t *
AWindowHandler_getANativeWindowAPI(AWindowHandler *p_awh)
{
    return &p_awh->anw_api;
}