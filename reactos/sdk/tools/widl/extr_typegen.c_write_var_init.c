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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ decl_indirect (int /*<<< orphan*/  const*) ; 
 scalar_t__ is_array (int /*<<< orphan*/  const*) ; 
 scalar_t__ is_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  print_file (int /*<<< orphan*/ *,int,char*,char const*,char const*,...) ; 

__attribute__((used)) static void write_var_init(FILE *file, int indent, const type_t *t, const char *n, const char *local_var_prefix)
{
    if (decl_indirect(t))
    {
        print_file(file, indent, "MIDL_memset(&%s%s, 0, sizeof(%s%s));\n",
                   local_var_prefix, n, local_var_prefix, n);
        print_file(file, indent, "%s_p_%s = &%s%s;\n", local_var_prefix, n, local_var_prefix, n);
    }
    else if (is_ptr(t) || is_array(t))
        print_file(file, indent, "%s%s = 0;\n", local_var_prefix, n);
}