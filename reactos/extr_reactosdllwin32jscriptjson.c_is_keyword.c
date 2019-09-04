#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ const* ptr; } ;
typedef  TYPE_1__ json_parse_ctx_t ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ is_identifier_char (scalar_t__ const) ; 

__attribute__((used)) static BOOL is_keyword(json_parse_ctx_t *ctx, const WCHAR *keyword)
{
    unsigned i;
    for(i=0; keyword[i]; i++) {
        if(!ctx->ptr[i] || keyword[i] != ctx->ptr[i])
            return FALSE;
    }
    if(is_identifier_char(ctx->ptr[i]))
        return FALSE;
    ctx->ptr += i;
    return TRUE;
}