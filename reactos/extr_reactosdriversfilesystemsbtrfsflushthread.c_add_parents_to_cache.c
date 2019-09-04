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
struct TYPE_3__ {int /*<<< orphan*/  write; struct TYPE_3__* parent; } ;
typedef  TYPE_1__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void add_parents_to_cache(tree* t) {
    while (t->parent) {
        t = t->parent;
        t->write = TRUE;
    }
}