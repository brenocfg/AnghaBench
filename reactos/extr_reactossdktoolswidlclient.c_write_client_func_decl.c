#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_6__* type; } ;
typedef  TYPE_1__ var_t ;
typedef  int /*<<< orphan*/  var_list_t ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ type_t ;
struct TYPE_12__ {int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_CALLCONV ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  client ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_name (TYPE_1__ const*) ; 
 int /*<<< orphan*/  indent ; 
 char* prefix_client ; 
 int /*<<< orphan*/  print_client (char*) ; 
 TYPE_2__* type_function_get_rettype (TYPE_6__*) ; 
 int /*<<< orphan*/ * type_get_function_args (TYPE_6__*) ; 
 int /*<<< orphan*/  write_args (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_type_decl_left (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void write_client_func_decl( const type_t *iface, const var_t *func )
{
    const char *callconv = get_attrp(func->type->attrs, ATTR_CALLCONV);
    const var_list_t *args = type_get_function_args(func->type);
    type_t *rettype = type_function_get_rettype(func->type);

    if (!callconv) callconv = "__cdecl";
    write_type_decl_left(client, rettype);
    fprintf(client, " %s ", callconv);
    fprintf(client, "%s%s(\n", prefix_client, get_name(func));
    indent++;
    if (args)
        write_args(client, args, iface->name, 0, TRUE);
    else
        print_client("void");
    fprintf(client, ")\n");
    indent--;
}