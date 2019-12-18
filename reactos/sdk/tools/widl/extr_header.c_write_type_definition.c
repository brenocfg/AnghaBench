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
struct TYPE_4__ {int written; scalar_t__ namespace; } ;
typedef  TYPE_1__ type_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NAME_C ; 
 int /*<<< orphan*/  NAME_DEFAULT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  indent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_global_namespace (scalar_t__) ; 
 int /*<<< orphan*/  write_namespace_end (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  write_namespace_start (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  write_type_left (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_type_definition(FILE *f, type_t *t)
{
    int in_namespace = t->namespace && !is_global_namespace(t->namespace);
    int save_written = t->written;

    if(in_namespace) {
        fprintf(f, "#ifdef __cplusplus\n");
        fprintf(f, "} /* extern \"C\" */\n");
        write_namespace_start(f, t->namespace);
    }
    indent(f, 0);
    write_type_left(f, t, NAME_DEFAULT, FALSE);
    fprintf(f, ";\n");
    if(in_namespace) {
        t->written = save_written;
        write_namespace_end(f, t->namespace);
        fprintf(f, "extern \"C\" {\n");
        fprintf(f, "#else\n");
        write_type_left(f, t, NAME_C, FALSE);
        fprintf(f, ";\n");
        fprintf(f, "#endif\n\n");
    }
}