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
typedef  int /*<<< orphan*/  statement_list_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* header_name ; 
 char* input_name ; 
 int /*<<< orphan*/  local_stubs_name ; 
 int /*<<< orphan*/  write_local_stubs_stmts (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void write_local_stubs(const statement_list_t *stmts)
{
  FILE *local_stubs;

  if (!local_stubs_name) return;

  local_stubs = fopen(local_stubs_name, "w");
  if (!local_stubs) {
    error("Could not open %s for output\n", local_stubs_name);
    return;
  }
  fprintf(local_stubs, "/* call_as/local stubs for %s */\n\n", input_name);
  fprintf(local_stubs, "#include <objbase.h>\n");
  fprintf(local_stubs, "#include \"%s\"\n\n", header_name);

  write_local_stubs_stmts(local_stubs, stmts);

  fclose(local_stubs);
}