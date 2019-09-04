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
struct TYPE_4__ {scalar_t__* ptr; } ;
typedef  TYPE_1__ parser_ctx_t ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JS_E_SYNTAX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  set_error (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL explicit_error(parser_ctx_t *ctx, void *obj, WCHAR next)
{
    if(obj || *(ctx->ptr-1)==next) return TRUE;

    set_error(ctx, JS_E_SYNTAX);
    return FALSE;
}