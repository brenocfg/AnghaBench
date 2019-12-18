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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ FALSE ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  expect_LayerValue (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ pSdbSetPermLayerKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int wrapSdbSetPermLayerKeys (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_SdbSetPermLayerKeysLevel(BOOL bMachine, const char* file)
{
    WCHAR fileW[MAX_PATH+20];
    WCHAR emptyString[1] = { 0 };

    MultiByteToWideChar(CP_ACP, 0, file, -1, fileW, MAX_PATH+20);

    /* Test some parameter validation. */
    ok(pSdbSetPermLayerKeys(NULL, NULL, bMachine) == FALSE, "Expected SdbSetPermLayerKeys to fail\n");
    ok(pSdbSetPermLayerKeys(NULL, emptyString, bMachine) == FALSE, "Expected SdbSetPermLayerKeys to fail\n");
    ok(pSdbSetPermLayerKeys(emptyString, emptyString, bMachine) == FALSE, "Expected SdbSetPermLayerKeys to fail\n");
    ok(pSdbSetPermLayerKeys(fileW, NULL, bMachine) == TRUE, "Expected SdbSetPermLayerKeys to succeed\n");
    ok(pSdbSetPermLayerKeys(fileW, emptyString, bMachine) == TRUE, "Expected SdbSetPermLayerKeys to fail\n");

    /* Basic tests */
    ok(wrapSdbSetPermLayerKeys(fileW, "TEST1", bMachine), "Expected SdbSetPermLayerKeys to succeed\n");
    expect_LayerValue(bMachine, file, "TEST1");

    ok(wrapSdbSetPermLayerKeys(fileW, "TEST1 TEST2", bMachine), "Expected SdbSetPermLayerKeys to succeed\n");
    expect_LayerValue(bMachine, file, "TEST1 TEST2");

    /* SdbSetPermLayerKeys does not do any validation of the value passed in. */
    ok(wrapSdbSetPermLayerKeys(fileW, "!#$% TEST1 TEST2", bMachine), "Expected SdbSetPermLayerKeys to succeed\n");
    expect_LayerValue(bMachine, file, "!#$% TEST1 TEST2");

    ok(wrapSdbSetPermLayerKeys(fileW, "!#$% TEST1     TEST2", bMachine), "Expected SdbSetPermLayerKeys to succeed\n");
    expect_LayerValue(bMachine, file, "!#$% TEST1     TEST2");

    ok(pSdbSetPermLayerKeys(fileW, NULL, bMachine) == TRUE, "Expected SdbSetPermLayerKeys to succeed\n");
    expect_LayerValue(bMachine, file, NULL);

    ok(wrapSdbSetPermLayerKeys(fileW, " ", bMachine), "Expected SdbSetPermLayerKeys to succeed\n");
    expect_LayerValue(bMachine, file, " ");

    ok(pSdbSetPermLayerKeys(fileW, NULL, bMachine) == TRUE, "Expected SdbSetPermLayerKeys to fail\n");
    expect_LayerValue(bMachine, file, NULL);
}