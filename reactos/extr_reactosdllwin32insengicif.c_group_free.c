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
struct cifgroup {struct cifgroup* description; struct cifgroup* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (struct cifgroup*) ; 

__attribute__((used)) static void group_free(struct cifgroup *group)
{
    heap_free(group->id);
    heap_free(group->description);
    heap_free(group);
}