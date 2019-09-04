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
typedef  int /*<<< orphan*/  type_pred_t ;
typedef  int /*<<< orphan*/  statement_list_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  clear_all_offsets () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_size_procformatstring (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_size_typeformatstring (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_file (int /*<<< orphan*/ *,int,char*,...) ; 
 int /*<<< orphan*/  write_formatdesc (int /*<<< orphan*/ *,int,char*) ; 

void write_formatstringsdecl(FILE *f, int indent, const statement_list_t *stmts, type_pred_t pred)
{
    clear_all_offsets();

    print_file(f, indent, "#define TYPE_FORMAT_STRING_SIZE %d\n",
               get_size_typeformatstring(stmts, pred));

    print_file(f, indent, "#define PROC_FORMAT_STRING_SIZE %d\n",
               get_size_procformatstring(stmts, pred));

    fprintf(f, "\n");
    write_formatdesc(f, indent, "TYPE");
    write_formatdesc(f, indent, "PROC");
    fprintf(f, "\n");
    print_file(f, indent, "static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;\n");
    print_file(f, indent, "static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;\n");
    print_file(f, indent, "\n");
}