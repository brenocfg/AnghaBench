#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  statement_t ;
struct TYPE_7__ {int /*<<< orphan*/  hres; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  scalar_t__ function_type_t ;
struct TYPE_8__ {int is_public; int /*<<< orphan*/ * next_prop_func; int /*<<< orphan*/ * next; int /*<<< orphan*/ * body; int /*<<< orphan*/ * args; scalar_t__ type; int /*<<< orphan*/  const* name; } ;
typedef  TYPE_2__ function_decl_t ;
typedef  int /*<<< orphan*/  arg_decl_t ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ FUNC_DEFGET ; 
 scalar_t__ FUNC_PROPGET ; 
 unsigned int STORAGE_IS_DEFAULT ; 
 unsigned int STORAGE_IS_PRIVATE ; 
 TYPE_2__* parser_alloc (TYPE_1__*,int) ; 

__attribute__((used)) static function_decl_t *new_function_decl(parser_ctx_t *ctx, const WCHAR *name, function_type_t type,
        unsigned storage_flags, arg_decl_t *arg_decl, statement_t *body)
{
    function_decl_t *decl;

    if(storage_flags & STORAGE_IS_DEFAULT) {
        if(type == FUNC_PROPGET) {
            type = FUNC_DEFGET;
        }else {
            FIXME("Invalid default property\n");
            ctx->hres = E_FAIL;
            return NULL;
        }
    }

    decl = parser_alloc(ctx, sizeof(*decl));
    if(!decl)
        return NULL;

    decl->name = name;
    decl->type = type;
    decl->is_public = !(storage_flags & STORAGE_IS_PRIVATE);
    decl->args = arg_decl;
    decl->body = body;
    decl->next = NULL;
    decl->next_prop_func = NULL;
    return decl;
}