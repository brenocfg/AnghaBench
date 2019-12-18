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
struct cb_answer {scalar_t__ b_dismiss; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,char const*,int,float,char const*) ; 
 int /*<<< orphan*/  vlc_dialog_id_dismiss (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
display_progress_cb(void *p_data, vlc_dialog_id *p_id, const char *psz_title,
                    const char *psz_text, bool b_indeterminate,
                    float f_position, const char *psz_cancel)
{
    struct cb_answer *p_ans = p_data;
    printf("progress dialog: title: '%s', text: '%s', "
           "indeterminate: %d, position: %f, cancel: '%s'\n",
           psz_title, psz_text, b_indeterminate, f_position, psz_cancel);

    if (p_ans->b_dismiss)
        vlc_dialog_id_dismiss(p_id);
}