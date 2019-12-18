#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  loc; } ;

/* Variables and functions */
 int /*<<< orphan*/  currentpage ; 
 scalar_t__ eqloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* history ; 
 int history_count ; 
 int /*<<< orphan*/  memmove (TYPE_1__*,TYPE_1__*,int) ; 
 int nelem (TYPE_1__*) ; 
 TYPE_1__ save_mark () ; 

__attribute__((used)) static void push_history(void)
{
	if (history_count > 0 && eqloc(history[history_count-1].loc, currentpage))
		return;
	if (history_count + 1 >= (int)nelem(history))
	{
		memmove(history, history + 1, sizeof *history * (nelem(history) - 1));
		history[history_count] = save_mark();
	}
	else
	{
		history[history_count++] = save_mark();
	}
}