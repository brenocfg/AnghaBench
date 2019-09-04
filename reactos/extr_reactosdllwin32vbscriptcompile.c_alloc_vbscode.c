#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* code_ctx; int /*<<< orphan*/  type; } ;
struct TYPE_12__ {int /*<<< orphan*/  entry; TYPE_2__ main_code; int /*<<< orphan*/  option_explicit; int /*<<< orphan*/  heap; int /*<<< orphan*/  instrs; int /*<<< orphan*/  source; } ;
typedef  TYPE_3__ vbscode_t ;
typedef  int /*<<< orphan*/  instr_t ;
struct TYPE_10__ {int /*<<< orphan*/  option_explicit; } ;
struct TYPE_13__ {int instr_cnt; int instr_size; TYPE_1__ parser; } ;
typedef  TYPE_4__ compile_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC_GLOBAL ; 
 int /*<<< orphan*/  heap_alloc (int) ; 
 TYPE_3__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_3__*) ; 
 int /*<<< orphan*/  heap_pool_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_strdupW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_vbscode (TYPE_3__*) ; 

__attribute__((used)) static vbscode_t *alloc_vbscode(compile_ctx_t *ctx, const WCHAR *source)
{
    vbscode_t *ret;

    ret = heap_alloc_zero(sizeof(*ret));
    if(!ret)
        return NULL;

    ret->source = heap_strdupW(source);
    if(!ret->source) {
        heap_free(ret);
        return NULL;
    }

    ret->instrs = heap_alloc(32*sizeof(instr_t));
    if(!ret->instrs) {
        release_vbscode(ret);
        return NULL;
    }

    ctx->instr_cnt = 1;
    ctx->instr_size = 32;
    heap_pool_init(&ret->heap);

    ret->option_explicit = ctx->parser.option_explicit;

    ret->main_code.type = FUNC_GLOBAL;
    ret->main_code.code_ctx = ret;

    list_init(&ret->entry);
    return ret;
}