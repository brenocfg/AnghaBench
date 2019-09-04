#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  string_constr; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_10__ {int /*<<< orphan*/  str; int /*<<< orphan*/  dispex; } ;
typedef  TYPE_2__ StringInstance ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StringInst_info ; 
 int /*<<< orphan*/  String_info ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_dispex_from_constr (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsstr_addref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT string_alloc(script_ctx_t *ctx, jsdisp_t *object_prototype, jsstr_t *str, StringInstance **ret)
{
    StringInstance *string;
    HRESULT hres;

    string = heap_alloc_zero(sizeof(StringInstance));
    if(!string)
        return E_OUTOFMEMORY;

    if(object_prototype)
        hres = init_dispex(&string->dispex, ctx, &String_info, object_prototype);
    else
        hres = init_dispex_from_constr(&string->dispex, ctx, &StringInst_info, ctx->string_constr);
    if(FAILED(hres)) {
        heap_free(string);
        return hres;
    }

    string->str = jsstr_addref(str);
    *ret = string;
    return S_OK;
}