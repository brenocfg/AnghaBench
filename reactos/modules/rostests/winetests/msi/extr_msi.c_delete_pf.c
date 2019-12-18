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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ DeleteFileA (char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  PROG_FILES_DIR ; 
 scalar_t__ RemoveDirectoryA (char*) ; 
 int /*<<< orphan*/  lstrcatA (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL delete_pf(const char *rel_path, BOOL is_file)
{
    char path[MAX_PATH];

    lstrcpyA(path, PROG_FILES_DIR);
    lstrcatA(path, "\\");
    lstrcatA(path, rel_path);

    if (is_file)
        return DeleteFileA(path);
    else
        return RemoveDirectoryA(path);
}