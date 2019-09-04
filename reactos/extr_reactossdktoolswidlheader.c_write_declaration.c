#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; int stgclass; int /*<<< orphan*/  type; scalar_t__ eval; } ;
typedef  TYPE_1__ var_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  STG_EXTERN 131 
#define  STG_NONE 130 
#define  STG_REGISTER 129 
#define  STG_STATIC 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ is_const_decl (TYPE_1__ const*) ; 
 int /*<<< orphan*/  write_expr (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  write_type_def_or_decl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void write_declaration(FILE *header, const var_t *v)
{
  if (is_const_decl(v) && v->eval)
  {
    fprintf(header, "#define %s (", v->name);
    write_expr(header, v->eval, 0, 1, NULL, NULL, "");
    fprintf(header, ")\n\n");
  }
  else
  {
    switch (v->stgclass)
    {
      case STG_NONE:
      case STG_REGISTER: /* ignored */
        break;
      case STG_STATIC:
        fprintf(header, "static ");
        break;
      case STG_EXTERN:
        fprintf(header, "extern ");
        break;
    }
    write_type_def_or_decl(header, v->type, FALSE, v->name);
    fprintf(header, ";\n\n");
  }
}