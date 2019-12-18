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
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  PauseConsole () ; 
 int /*<<< orphan*/  ShowConsole () ; 
 int /*<<< orphan*/  Usage (int /*<<< orphan*/ *,char const*) ; 
 char* _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_help_on_full_help () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  vlc_usage ; 

__attribute__((used)) static void Help (vlc_object_t *p_this, char const *psz_help_name)
{
    ShowConsole();

    if( psz_help_name && !strcmp( psz_help_name, "help" ) )
    {
        printf(_(vlc_usage), "vlc");
        Usage( p_this, "=core" );
        print_help_on_full_help();
    }
    else if( psz_help_name && !strcmp( psz_help_name, "longhelp" ) )
    {
        printf(_(vlc_usage), "vlc");
        Usage( p_this, NULL );
        print_help_on_full_help();
    }
    else if( psz_help_name && !strcmp( psz_help_name, "full-help" ) )
    {
        printf(_(vlc_usage), "vlc");
        Usage( p_this, NULL );
    }
    else if( psz_help_name )
    {
        Usage( p_this, psz_help_name );
    }

    PauseConsole();
}