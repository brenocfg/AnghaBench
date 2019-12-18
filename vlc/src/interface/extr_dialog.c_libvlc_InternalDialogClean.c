#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_dialog_provider ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_6__ {TYPE_1__* p_dialog_provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dialog_clear_all_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_2__* libvlc_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void
libvlc_InternalDialogClean(libvlc_int_t *p_libvlc)
{
    assert(p_libvlc != NULL);
    vlc_dialog_provider *p_provider = libvlc_priv(p_libvlc)->p_dialog_provider;

    if (p_provider == NULL)
        return;
    vlc_mutex_lock(&p_provider->lock);
    dialog_clear_all_locked(p_provider);
    vlc_mutex_unlock(&p_provider->lock);

    vlc_mutex_destroy(&p_provider->lock);
    free(p_provider);
    libvlc_priv(p_libvlc)->p_dialog_provider = NULL;
}