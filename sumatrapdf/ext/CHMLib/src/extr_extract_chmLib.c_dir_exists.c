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
struct stat {int dummy; } ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_LIST_DIRECTORY ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static int dir_exists(const char *path)
{
#ifdef WIN32
        /* why doesn't this work?!? */
        HANDLE hFile;

        hFile = CreateFileA(path,
                        FILE_LIST_DIRECTORY,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
        if (hFile != INVALID_HANDLE_VALUE)
        {
        CloseHandle(hFile);
        return 1;
        }
        else
        return 0;
#else
        struct stat statbuf;
        if (stat(path, &statbuf) != -1)
                return 1;
        else
                return 0;
#endif
}