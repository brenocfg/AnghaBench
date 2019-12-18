#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* psz_password; TYPE_4__* psz_username; } ;
struct TYPE_8__ {TYPE_1__ login; } ;
struct TYPE_9__ {scalar_t__ i_type; TYPE_2__ u; } ;
struct TYPE_10__ {int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; struct TYPE_10__* psz_progress_text; TYPE_3__ answer; } ;
typedef  TYPE_4__ vlc_dialog_id ;

/* Variables and functions */
 scalar_t__ VLC_DIALOG_LOGIN ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dialog_id_release(vlc_dialog_id *p_id)
{
    if (p_id->answer.i_type == VLC_DIALOG_LOGIN)
    {
        free(p_id->answer.u.login.psz_username);
        free(p_id->answer.u.login.psz_password);
    }
    free(p_id->psz_progress_text);
    vlc_mutex_destroy(&p_id->lock);
    vlc_cond_destroy(&p_id->wait);
    free(p_id);
}