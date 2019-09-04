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
struct symt_function_signature {struct symt symt; } ;
struct codeview_type_parse {int /*<<< orphan*/  module; } ;
typedef  enum CV_call_e { ____Placeholder_CV_call_e } CV_call_e ;

/* Variables and functions */
 int /*<<< orphan*/  SymTagFunctionType ; 
 struct symt_function_signature* codeview_cast_symt (struct symt*,int /*<<< orphan*/ ) ; 
 struct symt_function_signature* symt_new_function_signature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct symt* codeview_new_func_signature(struct codeview_type_parse* ctp, 
                                                struct symt* existing,
                                                enum CV_call_e call_conv)
{
    struct symt_function_signature*     sym;

    if (existing)
    {
        sym = codeview_cast_symt(existing, SymTagFunctionType);
        if (!sym) return NULL;
    }
    else
    {
        sym = symt_new_function_signature(ctp->module, NULL, call_conv);
    }
    return &sym->symt;
}