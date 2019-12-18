#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int line_number; int char_number; int state; int /*<<< orphan*/ * input; int /*<<< orphan*/  file; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* close ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* open ) (char const*,int) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  add_cmdline_defines () ; 
 int /*<<< orphan*/  add_special_defines () ; 
 int /*<<< orphan*/  del_cmdline_defines () ; 
 int /*<<< orphan*/  del_special_defines () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ pp_get_if_depth () ; 
 int /*<<< orphan*/  pp_pop_define_state () ; 
 int /*<<< orphan*/  pp_pop_if () ; 
 int pp_push_define_state () ; 
 TYPE_2__ pp_status ; 
 int /*<<< orphan*/  pp_writestring (char*,char const*) ; 
 int /*<<< orphan*/ * pp_xstrdup (char const*) ; 
 int /*<<< orphan*/  ppy_error (char*,char const*) ; 
 int /*<<< orphan*/ * ppy_out ; 
 int ppy_parse () ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stub1 (char const*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 TYPE_1__* wpp_callbacks ; 

int wpp_parse( const char *input, FILE *output )
{
    int ret;

    pp_status.input = NULL;
    pp_status.line_number = 1;
    pp_status.char_number = 1;
    pp_status.state = 0;

    ret = pp_push_define_state();
    if(ret)
        return ret;
    add_cmdline_defines();
    add_special_defines();

    if (!input) pp_status.file = stdin;
    else if (!(pp_status.file = wpp_callbacks->open(input, 1)))
    {
        ppy_error("Could not open %s\n", input);
        del_special_defines();
        del_cmdline_defines();
        pp_pop_define_state();
        return 2;
    }

    pp_status.input = input ? pp_xstrdup(input) : NULL;

    ppy_out = output;
    pp_writestring("# 1 \"%s\" 1\n", input ? input : "");

    ret = ppy_parse();
    /* If there were errors during processing, return an error code */
    if (!ret && pp_status.state) ret = pp_status.state;

    if (input)
    {
	wpp_callbacks->close(pp_status.file);
	free(pp_status.input);
    }
    /* Clean if_stack, it could remain dirty on errors */
    while (pp_get_if_depth()) pp_pop_if();
    del_special_defines();
    del_cmdline_defines();
    pp_pop_define_state();
    return ret;
}