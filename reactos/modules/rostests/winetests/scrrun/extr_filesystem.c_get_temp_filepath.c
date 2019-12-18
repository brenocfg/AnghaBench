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
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  GetTempPathW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 

__attribute__((used)) static void get_temp_filepath(const WCHAR *filename, WCHAR *path, WCHAR *dir)
{
    static const WCHAR scrrunW[] = {'s','c','r','r','u','n','\\',0};

    GetTempPathW(MAX_PATH, path);
    lstrcatW(path, scrrunW);
    lstrcpyW(dir, path);
    lstrcatW(path, filename);
}