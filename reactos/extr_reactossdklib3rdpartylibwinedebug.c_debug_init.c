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
struct TYPE_2__ {int /*<<< orphan*/  dbg_vlog; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetEnvironmentVariableA (char*,char*,scalar_t__) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  extfmt_default_dbg_vlog ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__ funcs ; 
 char* malloc (scalar_t__) ; 
 int nb_debug_options ; 
 int /*<<< orphan*/  parse_options (char*) ; 
 int /*<<< orphan*/  rosfmt_default_dbg_vlog ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  winefmt_default_dbg_vlog ; 

__attribute__((used)) static void debug_init(void)
{
    char *wine_debug;
    DWORD dwLength;
    /* GetEnvironmentVariableA will change LastError! */
    DWORD LastError = GetLastError();

    if (nb_debug_options != -1) return;  /* already initialized */
    nb_debug_options = 0;

    dwLength = GetEnvironmentVariableA("DEBUGCHANNEL", NULL, 0);
    if (dwLength)
    {
        wine_debug = malloc(dwLength);
        if (wine_debug)
        {
            if (GetEnvironmentVariableA("DEBUGCHANNEL", wine_debug, dwLength) < dwLength)
                parse_options(wine_debug);
            free(wine_debug);
        }
    }

    dwLength = GetEnvironmentVariableA("DEBUGFORMAT", NULL, 0);
    if (dwLength)
    {
        wine_debug = malloc(dwLength);
        if (wine_debug)
        {
            if (GetEnvironmentVariableA("DEBUGFORMAT", wine_debug, dwLength) < dwLength)
            {
                if (strcmp(wine_debug, "wine") == 0)
                {
                    funcs.dbg_vlog = winefmt_default_dbg_vlog;
                }
                else
                if (strcmp(wine_debug, "extended") == 0 ||
                    strcmp(wine_debug, "ext") == 0)
                {
                    funcs.dbg_vlog = extfmt_default_dbg_vlog;
                }
                else
                {
                    funcs.dbg_vlog = rosfmt_default_dbg_vlog;
                }
            }
            free(wine_debug);
        }
    }

    SetLastError(LastError);
}