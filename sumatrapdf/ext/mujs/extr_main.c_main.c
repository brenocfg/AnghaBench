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
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int /*<<< orphan*/  JS_STRICT ; 
 int /*<<< orphan*/  PS1 ; 
 int /*<<< orphan*/  add_history (char*) ; 
 int /*<<< orphan*/  eval_print (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsB_compile ; 
 int /*<<< orphan*/  jsB_gc ; 
 int /*<<< orphan*/  jsB_load ; 
 int /*<<< orphan*/  jsB_print ; 
 int /*<<< orphan*/  jsB_quit ; 
 int /*<<< orphan*/  jsB_read ; 
 int /*<<< orphan*/  jsB_readline ; 
 int /*<<< orphan*/  jsB_repr ; 
 int /*<<< orphan*/  jsB_write ; 
 scalar_t__ js_dofile (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_dostring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_freestate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_gc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_newcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * js_newstate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_setglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char* read_stdin () ; 
 char* readline (int /*<<< orphan*/ ) ; 
 char* require_js ; 
 int /*<<< orphan*/  rl_bind_key (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rl_insert ; 
 char* stacktrace_js ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  using_history () ; 
 int xgetopt (int,char**,char*) ; 
 int xoptind ; 

int
main(int argc, char **argv)
{
	char *input;
	js_State *J;
	int status = 0;
	int strict = 0;
	int interactive = 0;
	int i, c;

	while ((c = xgetopt(argc, argv, "is")) != -1) {
		switch (c) {
		default: usage(); break;
		case 'i': interactive = 1; break;
		case 's': strict = 1; break;
		}
	}

	J = js_newstate(NULL, NULL, strict ? JS_STRICT : 0);

	js_newcfunction(J, jsB_gc, "gc", 0);
	js_setglobal(J, "gc");

	js_newcfunction(J, jsB_load, "load", 1);
	js_setglobal(J, "load");

	js_newcfunction(J, jsB_compile, "compile", 2);
	js_setglobal(J, "compile");

	js_newcfunction(J, jsB_print, "print", 0);
	js_setglobal(J, "print");

	js_newcfunction(J, jsB_write, "write", 0);
	js_setglobal(J, "write");

	js_newcfunction(J, jsB_read, "read", 1);
	js_setglobal(J, "read");

	js_newcfunction(J, jsB_readline, "readline", 0);
	js_setglobal(J, "readline");

	js_newcfunction(J, jsB_repr, "repr", 0);
	js_setglobal(J, "repr");

	js_newcfunction(J, jsB_quit, "quit", 1);
	js_setglobal(J, "quit");

	js_dostring(J, require_js);
	js_dostring(J, stacktrace_js);

	if (xoptind == argc) {
		interactive = 1;
	} else {
		c = xoptind++;

		js_newarray(J);
		i = 0;
		while (xoptind < argc) {
			js_pushstring(J, argv[xoptind++]);
			js_setindex(J, -2, i++);
		}
		js_setglobal(J, "scriptArgs");

		if (js_dofile(J, argv[c]))
			status = 1;
	}

	if (interactive) {
		if (isatty(0)) {
			using_history();
			rl_bind_key('\t', rl_insert);
			input = readline(PS1);
			while (input) {
				eval_print(J, input);
				if (*input)
					add_history(input);
				free(input);
				input = readline(PS1);
			}
			putchar('\n');
		} else {
			input = read_stdin();
			if (!input || !js_dostring(J, input))
				status = 1;
			free(input);
		}
	}

	js_gc(J, 0);
	js_freestate(J);

	return status;
}