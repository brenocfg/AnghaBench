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
typedef  int /*<<< orphan*/  type_t ;

/* Variables and functions */
 int /*<<< orphan*/  reg_type (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_new_alias (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void decl_builtin_alias(const char *name, type_t *t)
{
  reg_type(type_new_alias(t, name), name, NULL, 0);
}