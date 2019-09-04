#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  expression_t ;
struct TYPE_4__ {int /*<<< orphan*/ * value_expr; int /*<<< orphan*/  name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ const_decl_t ;
struct TYPE_5__ {TYPE_1__* global_consts; TYPE_1__* const_decls; } ;
typedef  TYPE_2__ compile_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static expression_t *lookup_const_decls(compile_ctx_t *ctx, const WCHAR *name, BOOL lookup_global)
{
    const_decl_t *decl;

    for(decl = ctx->const_decls; decl; decl = decl->next) {
        if(!strcmpiW(decl->name, name))
            return decl->value_expr;
    }

    if(!lookup_global)
        return NULL;

    for(decl = ctx->global_consts; decl; decl = decl->next) {
        if(!strcmpiW(decl->name, name))
            return decl->value_expr;
    }

    return NULL;
}