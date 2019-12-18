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
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void write_coclass_forward(FILE *header, type_t *cocl)
{
  fprintf(header, "#ifndef __%s_FWD_DEFINED__\n", cocl->name);
  fprintf(header, "#define __%s_FWD_DEFINED__\n", cocl->name);
  fprintf(header, "#ifdef __cplusplus\n");
  fprintf(header, "typedef class %s %s;\n", cocl->name, cocl->name);
  fprintf(header, "#else\n");
  fprintf(header, "typedef struct %s %s;\n", cocl->name, cocl->name);
  fprintf(header, "#endif /* defined __cplusplus */\n");
  fprintf(header, "#endif /* defined __%s_FWD_DEFINED__ */\n\n", cocl->name );
}