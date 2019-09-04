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
struct TYPE_3__ {scalar_t__ word_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ dwarf2_traverse_context_t ;

/* Variables and functions */
 unsigned long dwarf2_get_addr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static unsigned long dwarf2_parse_addr(dwarf2_traverse_context_t* ctx)
{
    unsigned long ret = dwarf2_get_addr(ctx->data, ctx->word_size);
    ctx->data += ctx->word_size;
    return ret;
}