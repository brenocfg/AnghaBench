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
typedef  int /*<<< orphan*/  IHTMLDocument2 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateInstance ; 
 int /*<<< orphan*/  Invoke_READYSTATE ; 
 int /*<<< orphan*/  Invoke_SCRIPTCALL ; 
 int /*<<< orphan*/  Invoke_SECURITYCTX ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_DISPONLY ; 
 int /*<<< orphan*/ * create_doc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_ax_str ; 
 int /*<<< orphan*/  release_doc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_nooleobj_ax(void)
{
    IHTMLDocument2 *doc;

    init_test(TEST_DISPONLY);

    SET_EXPECT(CreateInstance);
    SET_EXPECT(Invoke_READYSTATE);
    SET_EXPECT(Invoke_SECURITYCTX);
    SET_EXPECT(Invoke_SCRIPTCALL);

    doc = create_doc(object_ax_str);

    CHECK_CALLED(CreateInstance);
    CHECK_CALLED(Invoke_READYSTATE);
    CHECK_CALLED(Invoke_SECURITYCTX);
    CHECK_CALLED(Invoke_SCRIPTCALL);

    release_doc(doc);
}