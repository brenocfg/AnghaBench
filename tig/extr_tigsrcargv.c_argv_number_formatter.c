#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct format_var {scalar_t__ value_ref; } ;
struct format_context {int /*<<< orphan*/  bufpos; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int string_format_from (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned long) ; 

__attribute__((used)) static bool
argv_number_formatter(struct format_context *format, struct format_var *var)
{
	unsigned long value = *(unsigned long *) var->value_ref;

	return string_format_from(format->buf, &format->bufpos, "%ld", value);
}