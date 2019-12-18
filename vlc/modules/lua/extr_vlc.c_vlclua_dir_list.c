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
 int VLC_EGENERIC ; 
 int /*<<< orphan*/  VLC_PKG_DATA_DIR ; 
 int /*<<< orphan*/  VLC_PKG_LIBEXEC_DIR ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_USERDATA_DIR ; 
 char* config_GetSysPath (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* config_GetUserDir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char** malloc (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 char** vlclua_dir_list_append (char**,char*,char const*) ; 

int vlclua_dir_list(const char *luadirname, char ***restrict listp)
{
    char **list = malloc(4 * sizeof(char *));
    if (unlikely(list == NULL))
        return VLC_EGENERIC;

    *listp = list;

    /* Lua scripts in user-specific data directory */
    list = vlclua_dir_list_append(list, config_GetUserDir(VLC_USERDATA_DIR),
                                  luadirname);

    char *libdir = config_GetSysPath(VLC_PKG_LIBEXEC_DIR, NULL);
    char *datadir = config_GetSysPath(VLC_PKG_DATA_DIR, NULL);
    bool both = libdir != NULL && datadir != NULL && strcmp(libdir, datadir);

    /* Tokenized Lua scripts in architecture-specific data directory */
    list = vlclua_dir_list_append(list, libdir, luadirname);

    /* Source Lua Scripts in architecture-independent data directory */
    if (both || libdir == NULL)
        list = vlclua_dir_list_append(list, datadir, luadirname);
    else
        free(datadir);

    *list = NULL;
    return VLC_SUCCESS;
}