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
struct environ_entry {int dummy; } ;

/* Variables and functions */
 struct environ_entry* RB_NEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct environ_entry*) ; 
 int /*<<< orphan*/  env ; 
 int /*<<< orphan*/  environ ; 

struct environ_entry *
environ_next(struct environ_entry *envent)
{
	return (RB_NEXT(environ, env, envent));
}