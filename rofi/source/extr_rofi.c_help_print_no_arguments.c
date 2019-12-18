#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__** available_modi ; 
 char* color_bold ; 
 char* color_green ; 
 char* color_red ; 
 char* color_reset ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int isatty (int /*<<< orphan*/ ) ; 
 TYPE_1__** modi ; 
 unsigned int num_available_modi ; 
 unsigned int num_modi ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void help_print_no_arguments ( void )
{
    int is_term = isatty ( fileno ( stdout ) );
    // Daemon mode
    fprintf ( stderr, "Rofi is unsure what to show.\n" );
    fprintf ( stderr, "Please specify the mode you want to show.\n\n" );
    fprintf ( stderr, "    %srofi%s -show %s{mode}%s\n\n",
              is_term ? color_bold : "", is_term ? color_reset : "",
              is_term ? color_green : "", is_term ? color_reset : "" );
    fprintf ( stderr, "The following modi are enabled:\n" );
    for ( unsigned int j = 0; j < num_modi; j++ ) {
        fprintf ( stderr, " * %s%s%s\n",
                  is_term ? color_green : "",
                  modi[j]->name,
                  is_term ? color_reset : "" );
    }
    fprintf ( stderr, "\nThe following can be enabled:\n" );
    for  ( unsigned int i = 0; i < num_available_modi; i++ ) {
        gboolean active = FALSE;
        for ( unsigned int j = 0; j < num_modi; j++ ) {
            if ( modi[j] == available_modi[i] ) {
                active = TRUE;
                break;
            }
        }
        if ( !active ) {
            fprintf ( stderr, " * %s%s%s\n",
                      is_term ? color_red : "",
                      available_modi[i]->name,
                      is_term ? color_reset : "" );
        }
    }
    fprintf ( stderr, "\nTo activate a mode, add it to the list of modi in the %smodi%s setting.\n",
              is_term ? color_green : "", is_term ? color_reset : "" );
}