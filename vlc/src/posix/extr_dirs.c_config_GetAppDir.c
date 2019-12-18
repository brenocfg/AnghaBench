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
typedef  int /*<<< orphan*/  var ;

/* Variables and functions */
 int asprintf (char**,char*,char const*,...) ; 
 char* config_GetHomeDir () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static char *config_GetAppDir (const char *xdg_name, const char *xdg_default)
{
    char *psz_dir;
    char var[sizeof ("XDG__HOME") + strlen (xdg_name)];

    /* XDG Base Directory Specification - Version 0.6 */
    snprintf (var, sizeof (var), "XDG_%s_HOME", xdg_name);

    const char *home = getenv (var);
    if (home != NULL)
    {
        if (asprintf (&psz_dir, "%s/vlc", home) == -1)
            psz_dir = NULL;
        return psz_dir;
    }

    char *psz_home = config_GetHomeDir ();
    if( psz_home == NULL
     || asprintf( &psz_dir, "%s/%s/vlc", psz_home, xdg_default ) == -1 )
        psz_dir = NULL;
    free (psz_home);
    return psz_dir;
}