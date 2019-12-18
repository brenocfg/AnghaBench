#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct imports {struct imports* next; void* name; } ;
struct TYPE_2__ {char* temp_name; char* input_name; int line_number; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_IMPORT_DEPTH ; 
 int /*<<< orphan*/  YY_BUF_SIZE ; 
 int /*<<< orphan*/  YY_CURRENT_BUFFER ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  error_loc (char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 struct imports* first_import ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 TYPE_1__* import_stack ; 
 int import_stack_ptr ; 
 char* input_name ; 
 int line_number ; 
 int mkstemps (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser__create_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser__switch_to_buffer (int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strcmp (void*,char*) ; 
 char* temp_name ; 
 char* wpp_find_include (char*,char*) ; 
 int wpp_parse (char*,int /*<<< orphan*/ *) ; 
 struct imports* xmalloc (int) ; 
 void* xstrdup (char*) ; 

int do_import(char *fname)
{
    FILE *f;
    char *path, *name;
    struct imports *import;
    int ptr = import_stack_ptr;
    int ret, fd;

    import = first_import;
    while (import && strcmp(import->name, fname))
        import = import->next;
    if (import) return 0; /* already imported */

    import = xmalloc(sizeof(struct imports));
    import->name = xstrdup(fname);
    import->next = first_import;
    first_import = import;

    /* don't search for a file name with a path in the include directories,
     * for compatibility with MIDL */
    if (strchr( fname, '/' ) || strchr( fname, '\\' ))
        path = xstrdup( fname );
    else if (!(path = wpp_find_include( fname, input_name )))
        error_loc("Unable to open include file %s\n", fname);

    if (import_stack_ptr == MAX_IMPORT_DEPTH)
        error_loc("Exceeded max import depth\n");

    import_stack[ptr].temp_name = temp_name;
    import_stack[ptr].input_name = input_name;
    import_stack[ptr].line_number = line_number;
    import_stack_ptr++;
    input_name = path;
    line_number = 1;

    name = xstrdup( "widl.XXXXXX" );
    if((fd = mkstemps( name, 0 )) == -1)
        error("Could not generate a temp name from %s\n", name);

    temp_name = name;
    if (!(f = fdopen(fd, "wt")))
        error("Could not open fd %s for writing\n", name);

    ret = wpp_parse( path, f );
    fclose( f );
    if (ret) exit(1);

    if((f = fopen(temp_name, "r")) == NULL)
        error_loc("Unable to open %s\n", temp_name);

    import_stack[ptr].state = YY_CURRENT_BUFFER;
    parser__switch_to_buffer(parser__create_buffer(f,YY_BUF_SIZE));
    return 1;
}