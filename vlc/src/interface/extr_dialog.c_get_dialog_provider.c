#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ no_interact; } ;
typedef  TYPE_1__ vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_dialog_provider ;
struct TYPE_6__ {int /*<<< orphan*/ * p_dialog_provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__* libvlc_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_killed () ; 
 int /*<<< orphan*/  vlc_object_instance (TYPE_1__*) ; 

__attribute__((used)) static inline vlc_dialog_provider *
get_dialog_provider(vlc_object_t *p_obj, bool b_check_interact)
{
    if ((b_check_interact && p_obj->no_interact) || vlc_killed())
        return NULL;

    vlc_dialog_provider *p_provider =
        libvlc_priv(vlc_object_instance(p_obj))->p_dialog_provider;
    assert(p_provider != NULL);
    return p_provider;
}