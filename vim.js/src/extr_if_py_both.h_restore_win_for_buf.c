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
typedef  int /*<<< orphan*/  win_T ;
typedef  int /*<<< orphan*/  tabpage_T ;
typedef  int /*<<< orphan*/  buf_T ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  restore_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_win (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
restore_win_for_buf(
    win_T	*save_curwin,
    tabpage_T	*save_curtab,
    buf_T	*save_curbuf)
{
    if (save_curbuf == NULL)
	restore_win(save_curwin, save_curtab, TRUE);
    else
	restore_buffer(save_curbuf);
}