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
 char* CURR_DIR ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentDirectoryA (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  createTestFile (char*) ; 
 int lstrlenA (char*) ; 

__attribute__((used)) static void create_test_files(void)
{
    int len;

    GetCurrentDirectoryA(MAX_PATH, CURR_DIR);
    len = lstrlenA(CURR_DIR);

    if(len && (CURR_DIR[len-1] == '\\'))
        CURR_DIR[len-1] = 0;

    createTestFile("a.txt");
    createTestFile("b.txt");
    CreateDirectoryA("testdir", NULL);
    createTestFile("testdir\\c.txt");
    createTestFile("testdir\\d.txt");
    CreateDirectoryA("dest", NULL);
}