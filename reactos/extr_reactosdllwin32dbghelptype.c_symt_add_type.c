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
struct symt {int dummy; } ;
struct module {int /*<<< orphan*/  pool; int /*<<< orphan*/  vtypes; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct symt**) ; 
 struct symt** vector_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void symt_add_type(struct module* module, struct symt* symt)
{
    struct symt**       p;
    p = vector_add(&module->vtypes, &module->pool);
    assert(p);
    *p = symt;
}