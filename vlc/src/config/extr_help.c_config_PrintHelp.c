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
 int /*<<< orphan*/  Help (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ListModules (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VLC_VAR_BOOL ; 
 int /*<<< orphan*/  Version () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  var_Create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ var_InheritBool (int /*<<< orphan*/ *,char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_SetBool (int /*<<< orphan*/ *,char*,int) ; 

bool config_PrintHelp (vlc_object_t *obj)
{
    char *str;

    /* Check for short help option */
    if (var_InheritBool (obj, "help"))
    {
        Help (obj, "help");
        return true;
    }

    /* Check for version option */
    if (var_InheritBool (obj, "version"))
    {
        Version();
        return true;
    }

    /* Check for help on modules */
    str = var_InheritString (obj, "module");
    if (str != NULL)
    {
        Help (obj, str);
        free (str);
        return true;
    }

    /* Check for full help option */
    if (var_InheritBool (obj, "full-help"))
    {
        var_Create (obj, "help-verbose", VLC_VAR_BOOL);
        var_SetBool (obj, "help-verbose", true);
        Help (obj, "full-help");
        return true;
    }

    /* Check for long help option */
    if (var_InheritBool (obj, "longhelp"))
    {
        Help (obj, "longhelp");
        return true;
    }

    /* Check for module list option */
    if (var_InheritBool (obj, "list"))
    {
        ListModules (obj, false );
        return true;
    }

    if (var_InheritBool (obj, "list-verbose"))
    {
        ListModules (obj, true);
        return true;
    }

    return false;
}