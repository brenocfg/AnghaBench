#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct list {int dummy; } ;
struct TYPE_4__ {char* cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATAA ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFileA (char*,TYPE_1__*) ; 
 scalar_t__ FindNextFileA (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  enum_gac_assembly_dirs (struct list*,char*,char*) ; 
 int /*<<< orphan*/  lstrcpynA (char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void enum_gac_assemblies(struct list *assemblies, char path[MAX_PATH])
{
    WIN32_FIND_DATAA ffd;
    HANDLE hfind;
    char *end = path + strlen( path );

    lstrcpynA( end, "\\*", path + MAX_PATH - end );
    hfind = FindFirstFileA(path, &ffd);
    if (hfind == INVALID_HANDLE_VALUE) return;
    end++;

    do
    {
        if (!strcmp(ffd.cFileName, ".") || !strcmp(ffd.cFileName, "..")) continue;
        lstrcpynA( end, ffd.cFileName, path + MAX_PATH - end );
        enum_gac_assembly_dirs( assemblies, ffd.cFileName, path );
    } while (FindNextFileA(hfind, &ffd) != 0);

    FindClose(hfind);
}