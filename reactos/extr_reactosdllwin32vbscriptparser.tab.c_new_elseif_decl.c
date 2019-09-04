#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  statement_t ;
typedef  int /*<<< orphan*/  parser_ctx_t ;
typedef  int /*<<< orphan*/  expression_t ;
struct TYPE_4__ {int /*<<< orphan*/ * next; int /*<<< orphan*/ * stat; int /*<<< orphan*/ * expr; } ;
typedef  TYPE_1__ elseif_decl_t ;

/* Variables and functions */
 TYPE_1__* parser_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static elseif_decl_t *new_elseif_decl(parser_ctx_t *ctx, expression_t *expr, statement_t *stat)
{
    elseif_decl_t *decl;

    decl = parser_alloc(ctx, sizeof(*decl));
    if(!decl)
        return NULL;

    decl->expr = expr;
    decl->stat = stat;
    decl->next = NULL;
    return decl;
}