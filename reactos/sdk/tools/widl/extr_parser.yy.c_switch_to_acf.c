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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  YY_BUF_SIZE ; 
 int /*<<< orphan*/  YY_CURRENT_BUFFER ; 
 int /*<<< orphan*/ * acf_name ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  error_loc (char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 TYPE_1__* import_stack ; 
 int import_stack_ptr ; 
 int /*<<< orphan*/ * input_name ; 
 int line_number ; 
 int mkstemps (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser__create_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parser__switch_to_buffer (int /*<<< orphan*/ ) ; 
 char* temp_name ; 
 int wpp_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void switch_to_acf(void)
{
    int ptr = import_stack_ptr;
    int ret, fd;
    char *name;
    FILE *f;

    assert(import_stack_ptr == 0);

    input_name = acf_name;
    acf_name = NULL;
    line_number = 1;

    name = xstrdup( "widl.XXXXXX" );
    if((fd = mkstemps( name, 0 )) == -1)
        error("Could not generate a temp name from %s\n", name);

    temp_name = name;
    if (!(f = fdopen(fd, "wt")))
        error("Could not open fd %s for writing\n", name);

    ret = wpp_parse(input_name, f);
    fclose(f);
    if (ret) exit(1);

    if((f = fopen(temp_name, "r")) == NULL)
        error_loc("Unable to open %s\n", temp_name);

    import_stack[ptr].state = YY_CURRENT_BUFFER;
    parser__switch_to_buffer(parser__create_buffer(f,YY_BUF_SIZE));
}