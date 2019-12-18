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
struct TYPE_3__ {int /*<<< orphan*/  psz_string; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  intf_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int /*<<< orphan*/  intf_Create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_instance (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Intf(intf_thread_t *intf, char const *psz_cmd,
                 vlc_value_t newval)
{
    VLC_UNUSED(psz_cmd);
    intf_Create(vlc_object_instance(intf), newval.psz_string);
}