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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  LPOLESTR ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ VT_I4 ; 
 scalar_t__ V_I4 (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 scalar_t__ navHyperlink ; 
 int /*<<< orphan*/  nav_url ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp_wa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_NavigateWithBindCtx(BSTR uri, VARIANT *flags, VARIANT *target_frame, VARIANT *post_data,
        VARIANT *headers, IBindCtx *bind_ctx, LPOLESTR url_fragment)
{
    ok(!strcmp_wa(uri, nav_url), "uri = %s\n", wine_dbgstr_w(uri));
    ok(V_VT(flags) == VT_I4, "V_VT(flags) = %d\n", V_VT(flags));
    ok(V_I4(flags) == navHyperlink, "V_I4(flags) = %x\n", V_I4(flags));
    ok(!target_frame, "target_frame != NULL\n");
    ok(!post_data, "post_data != NULL\n");
    ok(!headers, "headers != NULL\n");
    ok(bind_ctx != NULL, "bind_ctx == NULL\n");
    ok(!url_fragment, "url_dragment = %s\n", wine_dbgstr_w(url_fragment));
}