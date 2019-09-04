#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_5__* type; } ;
typedef  TYPE_1__ var_t ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ type_t ;
struct TYPE_10__ {int /*<<< orphan*/  attrs; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_CALLCONV ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_name (TYPE_1__ const*) ; 
 int /*<<< orphan*/  type_function_get_rettype (TYPE_5__*) ; 
 scalar_t__ type_get_function_args (TYPE_5__*) ; 
 int /*<<< orphan*/  write_args (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_type_decl_left (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_function_proto(FILE *header, const type_t *iface, const var_t *fun, const char *prefix)
{
  const char *callconv = get_attrp(fun->type->attrs, ATTR_CALLCONV);

  if (!callconv) callconv = "__cdecl";
  /* FIXME: do we need to handle call_as? */
  write_type_decl_left(header, type_function_get_rettype(fun->type));
  fprintf(header, " %s ", callconv);
  fprintf(header, "%s%s(\n", prefix, get_name(fun));
  if (type_get_function_args(fun->type))
    write_args(header, type_get_function_args(fun->type), iface->name, 0, TRUE);
  else
    fprintf(header, "    void");
  fprintf(header, ");\n\n");
}