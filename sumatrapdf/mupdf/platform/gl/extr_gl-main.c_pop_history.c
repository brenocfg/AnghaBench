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
typedef  int /*<<< orphan*/  fz_location ;

/* Variables and functions */
 int /*<<< orphan*/  currentpage ; 
 scalar_t__ eqloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * history ; 
 size_t history_count ; 
 int /*<<< orphan*/  push_future () ; 
 int /*<<< orphan*/  restore_mark (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pop_history(void)
{
	fz_location here = currentpage;
	push_future();
	while (history_count > 0 && eqloc(currentpage, here))
		restore_mark(history[--history_count]);
}