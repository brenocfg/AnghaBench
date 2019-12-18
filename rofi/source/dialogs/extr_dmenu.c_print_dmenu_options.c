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

/* Variables and functions */
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_help_msg (char*,char*,char*,char*,int) ; 
 int /*<<< orphan*/  stdout ; 

void print_dmenu_options ( void )
{
    int is_term = isatty ( fileno ( stdout ) );
    print_help_msg ( "-mesg", "[string]", "Print a small user message under the prompt (uses pango markup)", NULL, is_term );
    print_help_msg ( "-p", "[string]", "Prompt to display left of entry field", NULL, is_term );
    print_help_msg ( "-selected-row", "[integer]", "Select row", NULL, is_term );
    print_help_msg ( "-format", "[string]", "Output format string", "s", is_term );
    print_help_msg ( "-u", "[list]", "List of row indexes to mark urgent", NULL, is_term );
    print_help_msg ( "-a", "[list]", "List of row indexes to mark active", NULL, is_term );
    print_help_msg ( "-l", "[integer] ", "Number of rows to display", NULL, is_term );
    print_help_msg ( "-window-title", "[string] ", "Set the dmenu window title", NULL, is_term );
    print_help_msg ( "-i", "", "Set filter to be case insensitive", NULL, is_term );
    print_help_msg ( "-only-match", "", "Force selection or custom entry", NULL, is_term );
    print_help_msg ( "-no-custom", "", "Don't accept custom entry", NULL, is_term );
    print_help_msg ( "-select", "[string]", "Select the first row that matches", NULL, is_term );
    print_help_msg ( "-password", "", "Do not show what the user inputs. Show '*' instead.", NULL, is_term );
    print_help_msg ( "-markup-rows", "", "Allow and render pango markup as input data.", NULL, is_term );
    print_help_msg ( "-sep", "[char]", "Element separator.", "'\\n'", is_term );
    print_help_msg ( "-input", "[filename]", "Read input from file instead from standard input.", NULL, is_term );
    print_help_msg ( "-sync", "", "Force dmenu to first read all input data, then show dialog.", NULL, is_term );
    print_help_msg ( "-async-pre-read", "[number]", "Read several entries blocking before switching to async mode", "25", is_term );
    print_help_msg ( "-w", "windowid", "Position over window with X11 windowid.", NULL, is_term );
}