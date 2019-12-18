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
typedef  int vlc_dialog_question_type ;
typedef  int /*<<< orphan*/  vlc_dialog_id ;
struct cb_answer {int /*<<< orphan*/  i_action; scalar_t__ b_dismiss; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,char const*,int,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  vlc_dialog_id_dismiss (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dialog_id_post_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
display_question_cb(void *p_data, vlc_dialog_id *p_id, const char *psz_title,
                    const char *psz_text, vlc_dialog_question_type i_type,
                    const char *psz_cancel, const char *psz_action1,
                    const char *psz_action2)
{
    struct cb_answer *p_ans = p_data;
    printf("question dialog: title: '%s', text: '%s', "
           "type: %d, cancel: '%s', action1: '%s', action2: '%s'\n",
           psz_title, psz_text, i_type, psz_cancel, psz_action1, psz_action2);

    if (p_ans->b_dismiss)
        vlc_dialog_id_dismiss(p_id);
    else if (p_ans->i_action > 0)
        vlc_dialog_id_post_action(p_id, p_ans->i_action);
}