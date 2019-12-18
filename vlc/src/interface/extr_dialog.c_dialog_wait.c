#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ vlc_dialog_provider ;
struct TYPE_11__ {int i_type; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_3__ answer; scalar_t__ b_cancelled; int /*<<< orphan*/  wait; int /*<<< orphan*/  b_answered; } ;
typedef  TYPE_2__ vlc_dialog_id ;
struct dialog_i11e_context {TYPE_2__* p_id; TYPE_1__* p_provider; } ;
struct dialog_answer {int dummy; } ;
typedef  enum dialog_type { ____Placeholder_dialog_type } dialog_type ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  dialog_remove_locked (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dialog_wait_interrupted ; 
 int /*<<< orphan*/  memcpy (struct dialog_answer*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_register (int /*<<< orphan*/ ,struct dialog_i11e_context*) ; 
 int /*<<< orphan*/  vlc_interrupt_unregister () ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dialog_wait(vlc_dialog_provider *p_provider, vlc_dialog_id *p_id,
            enum dialog_type i_type, struct dialog_answer *p_answer)
{
    struct dialog_i11e_context context = {
        .p_provider = p_provider,
        .p_id = p_id,
    };
    vlc_interrupt_register(dialog_wait_interrupted, &context);

    vlc_mutex_lock(&p_id->lock);
    /* Wait for the dialog to be dismissed, interrupted or answered */
    while (!p_id->b_cancelled && !p_id->b_answered)
        vlc_cond_wait(&p_id->wait, &p_id->lock);

    int i_ret;
    if (p_id->b_cancelled)
        i_ret = 0;
    else if (p_id->answer.i_type != i_type)
        i_ret = VLC_EGENERIC;
    else
    {
        i_ret = 1;
        memcpy(p_answer, &p_id->answer, sizeof(p_id->answer));
        memset(&p_id->answer, 0, sizeof(p_id->answer));
    }

    vlc_mutex_unlock(&p_id->lock);
    vlc_interrupt_unregister();

    vlc_mutex_lock(&p_provider->lock);
    dialog_remove_locked(p_provider, p_id);
    vlc_mutex_unlock(&p_provider->lock);
    return i_ret;
}