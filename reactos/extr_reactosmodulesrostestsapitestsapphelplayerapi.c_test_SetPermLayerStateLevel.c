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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ FALSE ; 
 int LAYER_APPLY_TO_SYSTEM_EXES ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ TRUE ; 
 scalar_t__ WINVER_WIN8 ; 
 int /*<<< orphan*/  expect_LayerValue (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  expect_LayerValue2 (int /*<<< orphan*/ ,char const*,char*,int,char*) ; 
 scalar_t__ g_WinVersion ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pSetPermLayerState (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setLayerValue (int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__ wrapSetPermLayerState (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_SetPermLayerStateLevel(BOOL bMachine, const char* file)
{
    WCHAR fileW[MAX_PATH+20];
    WCHAR emptyString[1] = { 0 };
    DWORD dwFlag;

    MultiByteToWideChar(CP_ACP, 0, file, -1, fileW, MAX_PATH+20);

    /* Test some parameter validation. */
    ok(pSetPermLayerState(fileW, NULL, 0, bMachine, 0) == FALSE, "Expected SetPermLayerState to fail\n");
    expect_LayerValue(bMachine, file, NULL);

    ok(pSetPermLayerState(fileW, NULL, 0, bMachine, 1) == FALSE, "Expected SetPermLayerState to fail\n");
    expect_LayerValue(bMachine, file, NULL);

    ok(wrapSetPermLayerState(fileW, "", 0, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, NULL);

    ok(wrapSetPermLayerState(fileW, "", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, NULL);

    ok(wrapSetPermLayerState(NULL, NULL, 0, bMachine, 0) == FALSE, "Expected SetPermLayerState to fail\n");
    expect_LayerValue(bMachine, NULL, NULL);

    ok(wrapSetPermLayerState(NULL, NULL, 0, bMachine, 1) == FALSE, "Expected SetPermLayerState to fail\n");
    expect_LayerValue(bMachine, NULL, NULL);

    ok(wrapSetPermLayerState(emptyString, "", 0, bMachine, 0) == FALSE, "Expected SetPermLayerState to fail\n");
    expect_LayerValue(bMachine, NULL, NULL);

    ok(wrapSetPermLayerState(emptyString, "", 0, bMachine, 1) == FALSE, "Expected SetPermLayerState to fail\n");
    expect_LayerValue(bMachine, NULL, NULL);

    ok(wrapSetPermLayerState(emptyString, "TEST", 0, bMachine, 0) == FALSE, "Expected SetPermLayerState to fail\n");
    expect_LayerValue(bMachine, NULL, NULL);

    if (g_WinVersion <= WINVER_WIN8)
    {
        ok(wrapSetPermLayerState(emptyString, "TEST", 0, bMachine, 1) == FALSE, "Expected SetPermLayerState to fail\n");
        expect_LayerValue(bMachine, NULL, NULL);
    }


    /* Now, on to the actual tests. */
    expect_LayerValue(bMachine, file, NULL);
    ok(wrapSetPermLayerState(fileW, "TEST", 0, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, NULL);

    ok(wrapSetPermLayerState(fileW, "TEST", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "TEST");

    ok(wrapSetPermLayerState(fileW, "", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "TEST");

    ok(wrapSetPermLayerState(fileW, "test", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "test");

    ok(wrapSetPermLayerState(fileW, "TEST", 0, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, NULL);

    ok(wrapSetPermLayerState(fileW, "TEST", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "TEST");

    ok(wrapSetPermLayerState(fileW, "TEST1", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
        expect_LayerValue2(bMachine, file, "TEST TEST1", g_WinVersion >= WINVER_WIN8, "TEST1 TEST");

    ok(wrapSetPermLayerState(fileW, "TEST2", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue2(bMachine, file, "TEST TEST1 TEST2", g_WinVersion >= WINVER_WIN8, "TEST2 TEST1 TEST");

    ok(wrapSetPermLayerState(fileW, "TEST1", 0, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue2(bMachine, file, "TEST TEST2", g_WinVersion >= WINVER_WIN8, "TEST2 TEST");

    ok(wrapSetPermLayerState(fileW, "TEST", 0, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "TEST2");

    ok(wrapSetPermLayerState(fileW, "TEST2", 0, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, NULL);

    /* Valid flags until win8: !# */
    /* Key is empty, now play around with the flags. */
    for (dwFlag = ((g_WinVersion >= WINVER_WIN8) ? 6 : 2); dwFlag < 32; ++dwFlag)
    {
        ok(wrapSetPermLayerState(fileW, "TEST", (1<<dwFlag), bMachine, 1) == FALSE, "Expected SetPermLayerState to fail on 0x%x\n", (1<<dwFlag));
    }
    expect_LayerValue(bMachine, file, NULL);

    /* Add layer flags */
    ok(wrapSetPermLayerState(fileW, "TEST", LAYER_APPLY_TO_SYSTEM_EXES, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "# TEST");

    ok(wrapSetPermLayerState(fileW, "TEST2", 2, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue2(bMachine, file, "!# TEST TEST2", g_WinVersion >= WINVER_WIN8, "!# TEST2 TEST");

    ok(wrapSetPermLayerState(fileW, "TEST", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue2(bMachine, file, "!# TEST2 TEST", g_WinVersion >= WINVER_WIN8, "!# TEST TEST2");

    ok(wrapSetPermLayerState(fileW, "TEST3", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue2(bMachine, file, "!# TEST2 TEST TEST3", g_WinVersion >= WINVER_WIN8, "!# TEST3 TEST TEST2");

    /* Remove on a flag removes that flag from the start. */
    ok(wrapSetPermLayerState(fileW, "TEST2", 2, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue2(bMachine, file, "# TEST TEST3", g_WinVersion >= WINVER_WIN8, "# TEST3 TEST");

    ok(wrapSetPermLayerState(fileW, "", LAYER_APPLY_TO_SYSTEM_EXES, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue2(bMachine, file, "TEST TEST3", g_WinVersion >= WINVER_WIN8, "TEST3 TEST");

    ok(wrapSetPermLayerState(fileW, "", LAYER_APPLY_TO_SYSTEM_EXES | 2, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue2(bMachine, file, "!# TEST TEST3", g_WinVersion >= WINVER_WIN8, "!# TEST3 TEST");

    ok(wrapSetPermLayerState(fileW, "TEST3", LAYER_APPLY_TO_SYSTEM_EXES, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "! TEST");

    ok(wrapSetPermLayerState(fileW, "TEST", 2, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, NULL);

    /* Try adding multiple layers: */
    ok(wrapSetPermLayerState(fileW, "TEST TEST2", LAYER_APPLY_TO_SYSTEM_EXES | 2, bMachine, 1) == FALSE, "Expected SetPermLayerState to fail\n");
    expect_LayerValue(bMachine, file, NULL);

    ok(wrapSetPermLayerState(fileW, "TEST2", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "TEST2");

    /* Try adding flags in via layer string */
    ok(wrapSetPermLayerState(fileW, "#", 0, bMachine, 1) == FALSE, "Expected SetPermLayerState to fail\n");
    expect_LayerValue(bMachine, file, "TEST2");

    ok(wrapSetPermLayerState(fileW, "!", 0, bMachine, 1) == FALSE, "Expected SetPermLayerState to fail\n");
    expect_LayerValue(bMachine, file, "TEST2");

    /* Now we prepare the registry with some crap to see how data is validated. */
    setLayerValue(bMachine, file, "!#!# TEST2 TEST2  !#  TEST    ");

    ok(wrapSetPermLayerState(fileW, "TEST1", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue2(bMachine, file, "!# TEST2 TEST2 !# TEST TEST1", g_WinVersion >= WINVER_WIN8, "!# TEST1 TEST2 TEST2 !# TEST");

    /* Removing a duplicate entry will remove all instances of it */
    ok(wrapSetPermLayerState(fileW, "TEST2", 0, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue2(bMachine, file, "!# !# TEST TEST1", g_WinVersion >= WINVER_WIN8, "!# TEST1 !# TEST");

    /* Adding a flag cleans other flags (from the start) */
    ok(wrapSetPermLayerState(fileW, "", LAYER_APPLY_TO_SYSTEM_EXES, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue2(bMachine, file, "!# TEST TEST1", g_WinVersion >= WINVER_WIN8, "!# TEST1 !# TEST");

    if(g_WinVersion < WINVER_WIN8)
    {
        ok(wrapSetPermLayerState(fileW, "$%$%^^", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
        expect_LayerValue(bMachine, file, "!# TEST TEST1 $%$%^^");
    }

    setLayerValue(bMachine, file, "!#!# TEST2  !#  TEST    ");
    ok(wrapSetPermLayerState(fileW, "", LAYER_APPLY_TO_SYSTEM_EXES, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "! TEST2 !# TEST");

    /* Tabs are treated as spaces */
    setLayerValue(bMachine, file, "!#!# TEST2 \t  TEST2 !#  \t TEST    ");
    ok(wrapSetPermLayerState(fileW, "TEST2", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue2(bMachine, file, "!# !# TEST TEST2", g_WinVersion >= WINVER_WIN8, "!# TEST2 !# TEST");

    /* Newlines are left as-is */
    setLayerValue(bMachine, file, "!#!# TEST2 \n  TEST2 !#  \r\n TEST    ");
    ok(wrapSetPermLayerState(fileW, "TEST2", 0, bMachine, 1) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue2(bMachine, file, "!# \n !# \r\n TEST TEST2", g_WinVersion >= WINVER_WIN8, "!# TEST2 \n !# \r\n TEST");

    /* Whitespace and duplicate flags are eaten from the start */
    setLayerValue(bMachine, file, "     !#!# TEST2 \t  TEST2 !#  \t TEST    ");
    ok(wrapSetPermLayerState(fileW, "", LAYER_APPLY_TO_SYSTEM_EXES, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "! TEST2 TEST2 !# TEST");

    setLayerValue(bMachine, file, "!# !# TEST2  !#  TEST    ");
    ok(wrapSetPermLayerState(fileW, "", LAYER_APPLY_TO_SYSTEM_EXES, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "! TEST2 !# TEST");

    ok(wrapSetPermLayerState(fileW, "", LAYER_APPLY_TO_SYSTEM_EXES, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "! TEST2 !# TEST");

    ok(wrapSetPermLayerState(fileW, "", 2, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "TEST2 !# TEST");

    /* First flags are cleaned, then a layer is removed. */
    ok(wrapSetPermLayerState(fileW, "TEST2", 2, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "!# TEST");

    /* Nothing is changed, still it succeeds. */
    ok(wrapSetPermLayerState(fileW, "TEST2", 2, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, "# TEST");

    /* And remove the last bits. */
    ok(wrapSetPermLayerState(fileW, "TEST", LAYER_APPLY_TO_SYSTEM_EXES, bMachine, 0) == TRUE, "Expected SetPermLayerState to succeed\n");
    expect_LayerValue(bMachine, file, NULL);
}