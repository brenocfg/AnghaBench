#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  formats; } ;
struct wined3d_adapter {int /*<<< orphan*/  cfgs; TYPE_1__ gl_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_adapter_cleanup(struct wined3d_adapter *adapter)
{
    heap_free(adapter->gl_info.formats);
    heap_free(adapter->cfgs);
}