#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * pf_update_progress; int /*<<< orphan*/ * pf_cancel; int /*<<< orphan*/ * pf_display_progress; int /*<<< orphan*/ * pf_display_question; int /*<<< orphan*/ * pf_display_login; int /*<<< orphan*/ * pf_display_error; } ;
typedef  TYPE_2__ vlc_dialog_cbs ;
typedef  int /*<<< orphan*/  libvlc_int_t ;
struct TYPE_12__ {int /*<<< orphan*/ * pf_update_progress; int /*<<< orphan*/ * pf_cancel; int /*<<< orphan*/ * pf_display_progress; int /*<<< orphan*/ * pf_display_question; int /*<<< orphan*/  pf_display_login; int /*<<< orphan*/ * pf_display_error; } ;
struct TYPE_9__ {void* data; TYPE_4__ cbs; } ;
struct TYPE_11__ {int /*<<< orphan*/  instance_lock; TYPE_1__ dialog; int /*<<< orphan*/ * p_libvlc_int; } ;
typedef  TYPE_3__ libvlc_instance_t ;
typedef  TYPE_4__ libvlc_dialog_cbs ;

/* Variables and functions */
 int /*<<< orphan*/ * cancel_cb ; 
 int /*<<< orphan*/ * display_error_cb ; 
 int /*<<< orphan*/ * display_login_cb ; 
 int /*<<< orphan*/ * display_progress_cb ; 
 int /*<<< orphan*/ * display_question_cb ; 
 int /*<<< orphan*/ * update_progress_cb ; 
 int /*<<< orphan*/  vlc_dialog_provider_set_callbacks (int /*<<< orphan*/ *,TYPE_2__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void
libvlc_dialog_set_callbacks(libvlc_instance_t *p_instance,
                            const libvlc_dialog_cbs *p_cbs, void *p_data)
{
    libvlc_int_t *p_libvlc = p_instance->p_libvlc_int;

    vlc_mutex_lock(&p_instance->instance_lock);
    if (p_cbs != NULL)
    {
        const vlc_dialog_cbs dialog_cbs = {
            .pf_display_error = p_cbs->pf_display_error != NULL ?
                                display_error_cb : NULL,
            .pf_display_login = p_cbs->pf_display_login ?
                                display_login_cb : NULL,
            .pf_display_question = p_cbs->pf_display_question != NULL ?
                                   display_question_cb : NULL,
            .pf_display_progress = p_cbs->pf_display_progress != NULL ?
                                   display_progress_cb : NULL,
            .pf_cancel = p_cbs->pf_cancel != NULL ? cancel_cb : NULL,
            .pf_update_progress = p_cbs->pf_update_progress != NULL ?
                                  update_progress_cb : NULL,
        };

        p_instance->dialog.cbs = *p_cbs;
        p_instance->dialog.data = p_data;

        vlc_dialog_provider_set_callbacks(p_libvlc, &dialog_cbs, p_instance);
    }
    else
        vlc_dialog_provider_set_callbacks(p_libvlc, NULL, NULL);
    vlc_mutex_unlock(&p_instance->instance_lock);
}