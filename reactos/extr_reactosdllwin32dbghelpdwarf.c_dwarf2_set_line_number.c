#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vector {int dummy; } ;
struct TYPE_3__ {scalar_t__ tag; } ;
struct symt_ht {TYPE_1__ symt; } ;
struct symt_function {scalar_t__ address; } ;
struct TYPE_4__ {int /*<<< orphan*/  ModuleName; } ;
struct module {TYPE_2__ module; } ;

/* Variables and functions */
 scalar_t__ SymTagFunction ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  source_get (struct module*,unsigned int) ; 
 int /*<<< orphan*/  symt_add_func_line (struct module*,struct symt_function*,unsigned int,unsigned int,scalar_t__) ; 
 struct symt_ht* symt_find_nearest (struct module*,unsigned long) ; 
 unsigned int* vector_at (struct vector const*,unsigned int) ; 

__attribute__((used)) static void dwarf2_set_line_number(struct module* module, unsigned long address,
                                   const struct vector* v, unsigned file, unsigned line)
{
    struct symt_function*       func;
    struct symt_ht*             symt;
    unsigned*                   psrc;

    if (!file || !(psrc = vector_at(v, file - 1))) return;

    TRACE("%s %lx %s %u\n",
          debugstr_w(module->module.ModuleName), address, source_get(module, *psrc), line);
    if (!(symt = symt_find_nearest(module, address)) ||
        symt->symt.tag != SymTagFunction) return;
    func = (struct symt_function*)symt;
    symt_add_func_line(module, func, *psrc, line, address - func->address);
}