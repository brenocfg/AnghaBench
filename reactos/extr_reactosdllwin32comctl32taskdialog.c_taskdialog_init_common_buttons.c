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
struct taskdialog_template_desc {TYPE_1__* taskconfig; } ;
struct taskdialog_button_desc {int dummy; } ;
struct TYPE_2__ {int dwCommonButtons; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IDCANCEL ; 
 int /*<<< orphan*/  IDCLOSE ; 
 int /*<<< orphan*/  IDNO ; 
 int /*<<< orphan*/  IDOK ; 
 int /*<<< orphan*/  IDRETRY ; 
 int /*<<< orphan*/  IDS_BUTTON_CANCEL ; 
 int /*<<< orphan*/  IDS_BUTTON_CLOSE ; 
 int /*<<< orphan*/  IDS_BUTTON_NO ; 
 int /*<<< orphan*/  IDS_BUTTON_OK ; 
 int /*<<< orphan*/  IDS_BUTTON_RETRY ; 
 int /*<<< orphan*/  IDS_BUTTON_YES ; 
 int /*<<< orphan*/  IDYES ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int TDCBF_CANCEL_BUTTON ; 
 int TDCBF_CLOSE_BUTTON ; 
 int TDCBF_NO_BUTTON ; 
 int TDCBF_OK_BUTTON ; 
 int TDCBF_RETRY_BUTTON ; 
 int TDCBF_YES_BUTTON ; 
 int /*<<< orphan*/  taskdialog_init_button (struct taskdialog_button_desc*,struct taskdialog_template_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void taskdialog_init_common_buttons(struct taskdialog_template_desc *desc, struct taskdialog_button_desc *buttons,
    unsigned int *button_count)
{
    DWORD flags = desc->taskconfig->dwCommonButtons;

#define TASKDIALOG_INIT_COMMON_BUTTON(id) \
    do { \
        taskdialog_init_button(&buttons[(*button_count)++], desc, ID##id, MAKEINTRESOURCEW(IDS_BUTTON_##id), FALSE); \
    } while(0)

    if (flags & TDCBF_OK_BUTTON)
        TASKDIALOG_INIT_COMMON_BUTTON(OK);
    if (flags & TDCBF_YES_BUTTON)
        TASKDIALOG_INIT_COMMON_BUTTON(YES);
    if (flags & TDCBF_NO_BUTTON)
        TASKDIALOG_INIT_COMMON_BUTTON(NO);
    if (flags & TDCBF_RETRY_BUTTON)
        TASKDIALOG_INIT_COMMON_BUTTON(RETRY);
    if (flags & TDCBF_CANCEL_BUTTON)
        TASKDIALOG_INIT_COMMON_BUTTON(CANCEL);
    if (flags & TDCBF_CLOSE_BUTTON)
        TASKDIALOG_INIT_COMMON_BUTTON(CLOSE);

#undef TASKDIALOG_INIT_COMMON_BUTTON
}