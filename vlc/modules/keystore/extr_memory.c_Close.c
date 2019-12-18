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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ vlc_keystore_sys ;
struct TYPE_5__ {TYPE_1__* p_sys; } ;
typedef  TYPE_2__ vlc_keystore ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  ks_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
Close(vlc_object_t *p_this)
{
    vlc_keystore *p_keystore = (vlc_keystore *)p_this;
    vlc_keystore_sys *p_sys = p_keystore->p_sys;

    ks_list_free(&p_sys->list);
    vlc_mutex_destroy(&p_keystore->p_sys->lock);
    free(p_sys);
}