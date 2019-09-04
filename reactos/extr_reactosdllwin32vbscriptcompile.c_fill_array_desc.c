#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ val; struct TYPE_9__* next; } ;
typedef  TYPE_1__ dim_list_t ;
struct TYPE_10__ {TYPE_1__* dims; } ;
typedef  TYPE_2__ dim_decl_t ;
struct TYPE_11__ {int /*<<< orphan*/  code; } ;
typedef  TYPE_3__ compile_ctx_t ;
struct TYPE_12__ {unsigned int dim_cnt; TYPE_8__* bounds; } ;
typedef  TYPE_4__ array_desc_t ;
struct TYPE_13__ {scalar_t__ lLbound; scalar_t__ cElements; } ;
typedef  int /*<<< orphan*/  SAFEARRAYBOUND ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_8__* compiler_alloc (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static HRESULT fill_array_desc(compile_ctx_t *ctx, dim_decl_t *dim_decl, array_desc_t *array_desc)
{
    unsigned dim_cnt = 0, i;
    dim_list_t *iter;

    for(iter = dim_decl->dims; iter; iter = iter->next)
        dim_cnt++;

    array_desc->bounds = compiler_alloc(ctx->code, dim_cnt * sizeof(SAFEARRAYBOUND));
    if(!array_desc->bounds)
        return E_OUTOFMEMORY;

    array_desc->dim_cnt = dim_cnt;

    for(iter = dim_decl->dims, i=0; iter; iter = iter->next, i++) {
        array_desc->bounds[i].cElements = iter->val+1;
        array_desc->bounds[i].lLbound = 0;
    }

    return S_OK;
}