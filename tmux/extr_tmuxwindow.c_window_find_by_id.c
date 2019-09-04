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
typedef  int /*<<< orphan*/  u_int ;
struct window {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 struct window* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct window*) ; 
 int /*<<< orphan*/  windows ; 

struct window *
window_find_by_id(u_int id)
{
	struct window	w;

	w.id = id;
	return (RB_FIND(windows, &windows, &w));
}