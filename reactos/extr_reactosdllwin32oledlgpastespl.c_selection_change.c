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
typedef  int /*<<< orphan*/  ps_struct_t ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  update_as_icon (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_result_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void selection_change(HWND hdlg, ps_struct_t *ps_struct)
{
    update_as_icon(hdlg, ps_struct);
    update_result_text(hdlg, ps_struct);
}