#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_dialog_id ;
struct cb_answer {int /*<<< orphan*/ * psz_username; scalar_t__ b_dismiss; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,char const*,char const*,int) ; 
 int /*<<< orphan*/  vlc_dialog_id_dismiss (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dialog_id_post_login (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
display_login_cb(void *p_data, vlc_dialog_id *p_id, const char *psz_title,
                 const char *psz_text, const char *psz_default_username,
                 bool b_ask_store)
{
    struct cb_answer *p_ans = p_data;
    printf("login dialog: title: '%s', text: '%s', "
           "default_username: '%s', b_ask_store: %d\n",
           psz_title, psz_text, psz_default_username, b_ask_store);

    if (p_ans->b_dismiss)
        vlc_dialog_id_dismiss(p_id);
    else if (p_ans->psz_username != NULL)
        vlc_dialog_id_post_login(p_id, p_ans->psz_username, "", false);
}