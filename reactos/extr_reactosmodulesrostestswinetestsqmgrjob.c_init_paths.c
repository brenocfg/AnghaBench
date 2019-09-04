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
 int /*<<< orphan*/  GetTempFileNameW (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTempPathW (int,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  test_localPathA ; 
 int /*<<< orphan*/  test_localPathB ; 
 int /*<<< orphan*/  test_remotePathA ; 
 int /*<<< orphan*/  test_remotePathB ; 

__attribute__((used)) static void init_paths(void)
{
    WCHAR tmpDir[MAX_PATH];
    WCHAR prefix[] = {'q', 'm', 'g', 'r', 0};

    GetTempPathW(MAX_PATH, tmpDir);

    GetTempFileNameW(tmpDir, prefix, 0, test_localPathA);
    GetTempFileNameW(tmpDir, prefix, 0, test_localPathB);
    GetTempFileNameW(tmpDir, prefix, 0, test_remotePathA);
    GetTempFileNameW(tmpDir, prefix, 0, test_remotePathB);
}