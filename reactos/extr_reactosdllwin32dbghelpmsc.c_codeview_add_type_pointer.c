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
struct symt {int dummy; } ;
struct codeview_type_parse {int /*<<< orphan*/  module; } ;
struct TYPE_2__ {struct symt symt; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SymTagPointerType ; 
 struct symt* codeview_cast_symt (struct symt*,int /*<<< orphan*/ ) ; 
 struct symt* codeview_fetch_type (struct codeview_type_parse*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* symt_new_pointer (int /*<<< orphan*/ ,struct symt*,int) ; 

__attribute__((used)) static struct symt* codeview_add_type_pointer(struct codeview_type_parse* ctp,
                                              struct symt* existing,
                                              unsigned int pointee_type)
{
    struct symt* pointee;

    if (existing)
    {
        existing = codeview_cast_symt(existing, SymTagPointerType);
        return existing;
    }
    pointee = codeview_fetch_type(ctp, pointee_type, FALSE);
    return &symt_new_pointer(ctp->module, pointee, sizeof(void *))->symt;
}