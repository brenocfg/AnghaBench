#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int num; } ;
struct parsed_symbol {TYPE_1__ stack; } ;

/* Variables and functions */
 scalar_t__ get_class (struct parsed_symbol*) ; 
 char* get_class_string (struct parsed_symbol*,unsigned int) ; 

__attribute__((used)) static char* get_class_name(struct parsed_symbol* sym)
{
    unsigned    mark = sym->stack.num;
    char*       s = NULL;

    if (get_class(sym))
        s = get_class_string(sym, mark);
    sym->stack.num = mark;
    return s;
}