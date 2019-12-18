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
struct environ {int dummy; } ;

/* Variables and functions */
 struct environ_entry* RB_MIN (int /*<<< orphan*/ ,struct environ*) ; 
 int /*<<< orphan*/  environ ; 

struct environ_entry *
environ_first(struct environ *env)
{
	return (RB_MIN(environ, env));
}