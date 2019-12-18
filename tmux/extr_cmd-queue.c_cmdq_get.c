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
struct cmdq_list {int dummy; } ;
struct client {struct cmdq_list queue; } ;

/* Variables and functions */
 struct cmdq_list global_queue ; 

__attribute__((used)) static struct cmdq_list *
cmdq_get(struct client *c)
{
	if (c == NULL)
		return (&global_queue);
	return (&c->queue);
}