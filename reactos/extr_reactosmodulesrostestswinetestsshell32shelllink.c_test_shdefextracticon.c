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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HICON ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAKELONG (int,int) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pSHDefExtractIconA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_shdefextracticon(void)
{
    HICON hiconlarge=NULL, hiconsmall=NULL;
    HRESULT res;

    if (!pSHDefExtractIconA)
    {
        win_skip("SHDefExtractIconA is unavailable\n");
        return;
    }

    res = pSHDefExtractIconA("shell32.dll", 0, 0, &hiconlarge, &hiconsmall, MAKELONG(16,24));
    ok(SUCCEEDED(res), "SHDefExtractIconA failed, res=%x\n", res);
    ok(hiconlarge != NULL, "got null hiconlarge\n");
    ok(hiconsmall != NULL, "got null hiconsmall\n");
    DestroyIcon(hiconlarge);
    DestroyIcon(hiconsmall);

    hiconsmall = NULL;
    res = pSHDefExtractIconA("shell32.dll", 0, 0, NULL, &hiconsmall, MAKELONG(16,24));
    ok(SUCCEEDED(res), "SHDefExtractIconA failed, res=%x\n", res);
    ok(hiconsmall != NULL, "got null hiconsmall\n");
    DestroyIcon(hiconsmall);

    res = pSHDefExtractIconA("shell32.dll", 0, 0, NULL, NULL, MAKELONG(16,24));
    ok(SUCCEEDED(res), "SHDefExtractIconA failed, res=%x\n", res);
}