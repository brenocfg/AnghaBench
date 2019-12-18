#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct diff_stat_context {size_t cells; int /*<<< orphan*/  type; TYPE_1__* cell; int /*<<< orphan*/  text; int /*<<< orphan*/  cell_text; scalar_t__ skip; } ;
struct TYPE_2__ {size_t length; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  argv_appendn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static bool
diff_common_add_cell(struct diff_stat_context *context, size_t length, bool allow_empty)
{
	assert(ARRAY_SIZE(context->cell) > context->cells);
	if (!allow_empty && (length == 0))
		return true;
	if (context->skip && !argv_appendn(&context->cell_text, context->text, length))
		return false;
	context->cell[context->cells].length = length;
	context->cell[context->cells].type = context->type;
	context->cells++;
	return true;
}