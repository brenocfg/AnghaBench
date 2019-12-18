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
struct cb_answer {int b_dismiss; char const* psz_username; int i_action; } ;

/* Variables and functions */

__attribute__((used)) static inline void
set_answer(struct cb_answer *p_ans, bool b_dismiss, const char *psz_username,
           int i_action)
{
    if (p_ans != NULL)
    {
        p_ans->b_dismiss = b_dismiss;
        p_ans->psz_username = psz_username;
        p_ans->i_action = i_action;
    }
}