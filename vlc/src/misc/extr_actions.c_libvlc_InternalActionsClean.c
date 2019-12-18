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
struct TYPE_5__ {int /*<<< orphan*/  map; int /*<<< orphan*/  global_map; } ;
typedef  TYPE_1__ vlc_actions_t ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_6__ {TYPE_1__* actions; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_3__* libvlc_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdestroy (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (TYPE_1__*)) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_DelCallback (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_key_to_action ; 

void libvlc_InternalActionsClean (libvlc_int_t *libvlc)
{
    assert(libvlc != NULL);

    vlc_actions_t *as = libvlc_priv(libvlc)->actions;
    if (unlikely(as == NULL))
        return;

    var_DelCallback (libvlc, "global-key-pressed", vlc_key_to_action,
                     &as->global_map);
    var_DelCallback (libvlc, "key-pressed", vlc_key_to_action, &as->map);

    tdestroy (as->global_map, free);
    tdestroy (as->map, free);
    free (as);
    libvlc_priv(libvlc)->actions = NULL;
}