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
struct TYPE_3__ {char* c_name; int /*<<< orphan*/  namespace; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  write_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_namespace_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_namespace_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_forward(FILE *header, type_t *iface)
{
  fprintf(header, "#ifndef __%s_FWD_DEFINED__\n", iface->c_name);
  fprintf(header, "#define __%s_FWD_DEFINED__\n", iface->c_name);
  fprintf(header, "typedef interface %s %s;\n", iface->c_name, iface->c_name);
  fprintf(header, "#ifdef __cplusplus\n");
  write_namespace_start(header, iface->namespace);
  write_line(header, 0, "interface %s;", iface->name);
  write_namespace_end(header, iface->namespace);
  fprintf(header, "#endif /* __cplusplus */\n");
  fprintf(header, "#endif\n\n" );
}