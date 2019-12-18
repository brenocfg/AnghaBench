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
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ find_win_for_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  switch_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ switch_win (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
switch_to_win_for_buf(
    buf_T	*buf,
    win_T	**save_curwinp,
    tabpage_T	**save_curtabp,
    buf_T	**save_curbufp)
{
    win_T	*wp;
    tabpage_T	*tp;

    if (find_win_for_buf(buf, &wp, &tp) == FAIL
	    || switch_win(save_curwinp, save_curtabp, wp, tp, TRUE) == FAIL)
	switch_buffer(save_curbufp, buf);
}