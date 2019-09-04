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
typedef  int /*<<< orphan*/  parser_ctx_t ;
struct TYPE_4__ {int /*<<< orphan*/ * next; int /*<<< orphan*/  const* identifier; } ;
typedef  TYPE_1__ parameter_t ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 TYPE_1__* parser_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static parameter_t *new_parameter(parser_ctx_t *ctx, const WCHAR *identifier)
{
    parameter_t *ret = parser_alloc(ctx, sizeof(parameter_t));

    ret->identifier = identifier;
    ret->next = NULL;

    return ret;
}