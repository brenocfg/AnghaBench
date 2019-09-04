#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {int /*<<< orphan*/  path; int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeWideString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * GetWideString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PathUnquoteSpacesA (char*) ; 
 int /*<<< orphan*/  PathUnquoteSpacesW (int /*<<< orphan*/ *) ; 
 TYPE_1__* TEST_PATH_UNQUOTE_SPACES ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strdupA (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_PathUnquoteSpaces(void)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(TEST_PATH_UNQUOTE_SPACES); i++)
    {
        char *path = strdupA(TEST_PATH_UNQUOTE_SPACES[i].path);
        WCHAR *pathW = GetWideString(TEST_PATH_UNQUOTE_SPACES[i].path);
        WCHAR *resultW = GetWideString(TEST_PATH_UNQUOTE_SPACES[i].result);

        PathUnquoteSpacesA(path);
        ok(!strcmp(path, TEST_PATH_UNQUOTE_SPACES[i].result), "%s (A): got %s expected %s\n",
           TEST_PATH_UNQUOTE_SPACES[i].path, path,
           TEST_PATH_UNQUOTE_SPACES[i].result);

        PathUnquoteSpacesW(pathW);
        ok(!lstrcmpW(pathW, resultW), "%s (W): strings differ\n",
           TEST_PATH_UNQUOTE_SPACES[i].path);
        FreeWideString(pathW);
        FreeWideString(resultW);
        HeapFree(GetProcessHeap(), 0, path);
    }
}