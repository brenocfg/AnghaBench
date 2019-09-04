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
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ dwarf2_traverse_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 long dwarf2_get_leb128_as_signed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long dwarf2_leb128_as_signed(dwarf2_traverse_context_t* ctx)
{
    long ret = 0;

    assert(ctx);

    ret = dwarf2_get_leb128_as_signed(ctx->data, &ctx->data);
    return ret;
}