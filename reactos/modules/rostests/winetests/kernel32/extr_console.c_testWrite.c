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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  COORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SetConsoleTextAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ATTRIB ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resetContent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testEmptyWrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testWriteNotWrappedNotProcessed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testWriteNotWrappedProcessed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testWriteSimple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testWriteWrappedNotProcessed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testWriteWrappedProcessed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void testWrite(HANDLE hCon, COORD sbSize)
{
    /* FIXME: should in fact ensure that the sb is at least 10 characters wide */
    ok(SetConsoleTextAttribute(hCon, TEST_ATTRIB), "Setting default text color\n");
    resetContent(hCon, sbSize, FALSE);
    testEmptyWrite(hCon);
    resetContent(hCon, sbSize, FALSE);
    testWriteSimple(hCon);
    resetContent(hCon, sbSize, FALSE);
    testWriteNotWrappedNotProcessed(hCon, sbSize);
    resetContent(hCon, sbSize, FALSE);
    testWriteNotWrappedProcessed(hCon, sbSize);
    resetContent(hCon, sbSize, FALSE);
    testWriteWrappedNotProcessed(hCon, sbSize);
    resetContent(hCon, sbSize, FALSE);
    testWriteWrappedProcessed(hCon, sbSize);
}