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
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void
PrintUsage(int type)
{
    if (type == 0)
    {
        _ftprintf(stdout, _T("vcdcli usage:\n"));
        _ftprintf(stdout, _T("\tlist [/a]: list all the virtual drives\n"));
        _ftprintf(stdout, _T("\tcreate: create a virtual drive\n"));
        _ftprintf(stdout, _T("\tmount X path: mount path image on X virtual drive\n"));
        _ftprintf(stdout, _T("\tremount X: remount image on X virtual drive\n"));
        _ftprintf(stdout, _T("\tremount X: remount image on X virtual drive\n"));
        _ftprintf(stdout, _T("\teject X: eject image on X virtual drive\n"));
        _ftprintf(stdout, _T("\tremove X: remove virtual drive X\n"));
    }
    else if (type == 1)
    {
        _ftprintf(stdout, _T("mount usage:\n"));
        _ftprintf(stdout, _T("\tmount <drive letter> <path.iso> [/u] [/j] [/p]\n"));
        _ftprintf(stdout, _T("\tMount the ISO image given in <path.iso> on the previously created virtual drive <drive letter>\n"));
        _ftprintf(stdout, _T("\t\tDo not use colon for drive letter\n"));
        _ftprintf(stdout, _T("\t\tUse /u to make UDF volumes not appear as such\n"));
        _ftprintf(stdout, _T("\t\tUse /j to make Joliet volumes not appear as such\n"));
        _ftprintf(stdout, _T("\t\tUse /p to make the mounting persistent\n"));
    }
    else if (type == 2)
    {
        _ftprintf(stdout, _T("remount usage:\n"));
        _ftprintf(stdout, _T("\tremount <drive letter>\n"));
        _ftprintf(stdout, _T("\tRemount the ISO image that was previously mounted on the virtual drive <drive letter>\n"));
        _ftprintf(stdout, _T("\t\tDo not use colon for drive letter\n"));
    }
    else if (type == 3)
    {
        _ftprintf(stdout, _T("eject usage:\n"));
        _ftprintf(stdout, _T("\teject <drive letter>\n"));
        _ftprintf(stdout, _T("\tEjects the ISO image that is mounted on the virtual drive <drive letter>\n"));
        _ftprintf(stdout, _T("\t\tDo not use colon for drive letter\n"));
    }
    else if (type == 4)
    {
        _ftprintf(stdout, _T("remove usage:\n"));
        _ftprintf(stdout, _T("\tremove <drive letter>\n"));
        _ftprintf(stdout, _T("\tRemoves the virtual drive <drive letter> making it no longer usable\n"));
        _ftprintf(stdout, _T("\t\tDo not use colon for drive letter\n"));
    }
}