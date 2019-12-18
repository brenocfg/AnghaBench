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
struct format_var {int dummy; } ;
struct format_context {int dummy; } ;

/* Variables and functions */
 int argv_string_formatter (struct format_context*,struct format_var*) ; 

__attribute__((used)) static bool
repo_rev_formatter(struct format_context *format, struct format_var *var)
{
	return argv_string_formatter(format, var);
}