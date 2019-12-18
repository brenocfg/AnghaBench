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
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; } ;
typedef  TYPE_2__ vlc_dialog_id ;
struct dialog_i11e_context {TYPE_2__* p_id; TYPE_1__* p_provider; } ;

/* Variables and functions */
 int /*<<< orphan*/  dialog_cancel_locked (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dialog_wait_interrupted(void *p_data)
{
    struct dialog_i11e_context *p_context = p_data;
    vlc_dialog_provider *p_provider = p_context->p_provider;
    vlc_dialog_id *p_id = p_context->p_id;

    vlc_mutex_lock(&p_provider->lock);
    dialog_cancel_locked(p_provider, p_id);
    vlc_mutex_unlock(&p_provider->lock);

    vlc_mutex_lock(&p_id->lock);
    vlc_cond_signal(&p_id->wait);
    vlc_mutex_unlock(&p_id->lock);
}