#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hres; } ;
typedef  TYPE_1__ parser_ctx_t ;
struct TYPE_9__ {int is_public; struct TYPE_9__* next; } ;
typedef  TYPE_2__ dim_decl_t ;
struct TYPE_10__ {TYPE_2__* props; } ;
typedef  TYPE_3__ class_decl_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 unsigned int STORAGE_IS_DEFAULT ; 
 unsigned int STORAGE_IS_PRIVATE ; 

__attribute__((used)) static class_decl_t *add_dim_prop(parser_ctx_t *ctx, class_decl_t *class_decl, dim_decl_t *dim_decl, unsigned storage_flags)
{
    if(storage_flags & STORAGE_IS_DEFAULT) {
        FIXME("variant prop van't be default value\n");
        ctx->hres = E_FAIL;
        return NULL;
    }

    dim_decl->is_public = !(storage_flags & STORAGE_IS_PRIVATE);
    dim_decl->next = class_decl->props;
    class_decl->props = dim_decl;
    return class_decl;
}