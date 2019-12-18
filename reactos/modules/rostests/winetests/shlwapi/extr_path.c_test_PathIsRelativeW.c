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
struct TYPE_3__ {int /*<<< orphan*/  expect; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeWideString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWideString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pPathIsRelativeW (int /*<<< orphan*/ ) ; 
 TYPE_1__* test_path_is_relative ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_PathIsRelativeW(void)
{
    BOOL ret;
    int i, num;
    LPWSTR path;

    if (!pPathIsRelativeW) {
        win_skip("PathIsRelativeW not available\n");
        return;
    }

    num = ARRAY_SIZE(test_path_is_relative);
    for (i = 0; i < num; i++) {
        path = GetWideString(test_path_is_relative[i].path);

        ret = pPathIsRelativeW(path);
        ok(ret == test_path_is_relative[i].expect,
          "PathIsRelativeW(\"%s\") expects %d, got %d.\n",
          test_path_is_relative[i].path, test_path_is_relative[i].expect, ret);

        FreeWideString(path);
    }
}