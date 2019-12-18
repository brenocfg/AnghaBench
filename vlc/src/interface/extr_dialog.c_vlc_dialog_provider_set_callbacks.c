#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * p_cbs_data; int /*<<< orphan*/  cbs; } ;
typedef  TYPE_1__ vlc_dialog_provider ;
typedef  int /*<<< orphan*/  vlc_dialog_cbs ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dialog_clear_all_locked (TYPE_1__*) ; 
 TYPE_1__* get_dialog_provider (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void
vlc_dialog_provider_set_callbacks(vlc_object_t *p_obj,
                                  const vlc_dialog_cbs *p_cbs, void *p_data)
{
    assert(p_obj != NULL);
    vlc_dialog_provider *p_provider = get_dialog_provider(p_obj, false);

    vlc_mutex_lock(&p_provider->lock);
    dialog_clear_all_locked(p_provider);

    if (p_cbs == NULL)
    {
        memset(&p_provider->cbs, 0, sizeof(p_provider->cbs));
        p_provider->p_cbs_data = NULL;
    }
    else
    {
        p_provider->cbs = *p_cbs;
        p_provider->p_cbs_data = p_data;
    }
    vlc_mutex_unlock(&p_provider->lock);
}