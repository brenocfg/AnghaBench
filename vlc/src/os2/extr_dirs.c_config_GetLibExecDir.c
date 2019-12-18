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
 char* FromLocaleDup (char const*) ; 
 int /*<<< orphan*/  PKGLIBEXECDIR ; 
 char* config_GetRealDir (int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 

__attribute__((used)) static char *config_GetLibExecDir(void)
{
    const char *path = getenv ("VLC_LIB_PATH");
    if (path)
        return FromLocaleDup( path );

    return config_GetRealDir( PKGLIBEXECDIR );
}