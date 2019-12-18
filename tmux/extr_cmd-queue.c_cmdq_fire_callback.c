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
struct cmdq_item {int (* cb ) (struct cmdq_item*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
typedef  enum cmd_retval { ____Placeholder_cmd_retval } cmd_retval ;

/* Variables and functions */
 int stub1 (struct cmdq_item*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum cmd_retval
cmdq_fire_callback(struct cmdq_item *item)
{
	return (item->cb(item, item->data));
}