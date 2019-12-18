#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  link; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ filename_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  dup_basename (char const*,char*) ; 
 int /*<<< orphan*/  list_add_tail (struct list*,int /*<<< orphan*/ *) ; 
 TYPE_1__* xmalloc (int) ; 

__attribute__((used)) static void add_filename_node(struct list *list, const char *name)
{
  filename_node_t *node = xmalloc(sizeof *node);
  node->filename = dup_basename( name, ".idl" );
  list_add_tail(list, &node->link);
}