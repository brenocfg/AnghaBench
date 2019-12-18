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
struct parsed_symbol {scalar_t__ avail_in_first; void* alloc_list; int /*<<< orphan*/  (* mem_free_ptr ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void und_free_all(struct parsed_symbol* sym)
{
    void*       next;

    while (sym->alloc_list)
    {
        next = *(void**)sym->alloc_list;
        if(sym->mem_free_ptr) sym->mem_free_ptr(sym->alloc_list);
        sym->alloc_list = next;
    }
    sym->avail_in_first = 0;
}