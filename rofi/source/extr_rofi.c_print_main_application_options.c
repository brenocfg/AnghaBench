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
 int /*<<< orphan*/  print_help_msg (char*,char*,char*,char*,int) ; 

__attribute__((used)) static void print_main_application_options ( int is_term )
{
    print_help_msg ( "-no-config", "", "Do not load configuration, use default values.", NULL, is_term );
    print_help_msg ( "-v,-version", "", "Print the version number and exit.", NULL, is_term  );
    print_help_msg ( "-dmenu", "", "Start in dmenu mode.", NULL, is_term );
    print_help_msg ( "-display", "[string]", "X server to contact.", "${DISPLAY}", is_term );
    print_help_msg ( "-h,-help", "", "This help message.", NULL, is_term );
    print_help_msg ( "-dump-xresources", "", "Dump the current configuration in Xresources format and exit.", NULL, is_term );
    print_help_msg ( "-e", "[string]", "Show a dialog displaying the passed message and exit.", NULL, is_term );
    print_help_msg ( "-markup", "", "Enable pango markup where possible.", NULL, is_term );
    print_help_msg ( "-normal-window", "", "In dmenu mode, behave as a normal window. (experimental)", NULL, is_term );
    print_help_msg ( "-show", "[mode]", "Show the mode 'mode' and exit. The mode has to be enabled.", NULL, is_term );
    print_help_msg ( "-no-lazy-grab", "", "Disable lazy grab that, when fail to grab keyboard, does not block but retry later.", NULL, is_term );
    print_help_msg ( "-no-plugins", "", "Disable loading of external plugins.", NULL, is_term );
    print_help_msg ( "-plugin-path", "", "Directory used to search for rofi plugins.", NULL, is_term );
    print_help_msg ( "-dump-config", "", "Dump the current configuration in rasi format and exit.", NULL, is_term );
    print_help_msg ( "-dump-theme", "", "Dump the current theme in rasi format and exit.", NULL, is_term );
}