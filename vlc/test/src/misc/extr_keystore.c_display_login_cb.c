#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_dialog_id ;
struct TYPE_2__ {char const* psz_user; int /*<<< orphan*/ * psz_pwd; } ;
struct testcase {int /*<<< orphan*/  b_dialog_store; TYPE_1__ dialog; } ;
struct dialog_ctx {int b_abort; struct testcase* p_test; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_dialog_id_dismiss (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dialog_id_post_login (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
display_login_cb(void *p_data, vlc_dialog_id *p_id, const char *psz_title,
                 const char *psz_text, const char *psz_default_username,
                 bool b_ask_store)
{
    (void) psz_title;
    (void) psz_text;
    (void) psz_default_username;
    (void) b_ask_store;
    struct dialog_ctx *p_dialog_ctx = p_data;
    const struct testcase *p_testcase = p_dialog_ctx->p_test;

    const char *psz_user = p_testcase->dialog.psz_user != NULL ?
                           p_testcase->dialog.psz_user : psz_default_username;
    if (!p_dialog_ctx->b_abort && psz_user != NULL
     && p_testcase->dialog.psz_pwd != NULL)
    {
        vlc_dialog_id_post_login(p_id, psz_user, p_testcase->dialog.psz_pwd,
                                 p_testcase->b_dialog_store);
        p_dialog_ctx->b_abort = true;
    }
    else
        vlc_dialog_id_dismiss(p_id);
}