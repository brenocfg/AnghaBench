#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {char const* const* ppsz_keys; } ;
typedef  TYPE_1__ vlc_actions_t ;
struct TYPE_4__ {TYPE_1__* actions; } ;

/* Variables and functions */
 TYPE_2__* libvlc_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_object_instance (int /*<<< orphan*/ *) ; 

const char* const*
vlc_actions_get_key_names(vlc_object_t *p_obj)
{
    vlc_actions_t *as = libvlc_priv(vlc_object_instance(p_obj))->actions;
    return as->ppsz_keys;
}