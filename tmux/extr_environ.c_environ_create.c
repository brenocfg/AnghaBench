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
struct environ {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_INIT (struct environ*) ; 
 struct environ* xcalloc (int,int) ; 

struct environ *
environ_create(void)
{
	struct environ	*env;

	env = xcalloc(1, sizeof *env);
	RB_INIT(env);

	return (env);
}