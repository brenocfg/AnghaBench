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
typedef  int /*<<< orphan*/  UINT ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseClipboard () ; 
 scalar_t__ GetClipboardData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OpenClipboard (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegisterClipboardFormatA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_no_cf_dataobject(void)
{
    UINT cf_dataobject = RegisterClipboardFormatA("DataObject");
    UINT cf_ole_priv_data = RegisterClipboardFormatA("Ole Private Data");
    HANDLE h;
    OpenClipboard(NULL);

    h = GetClipboardData(cf_dataobject);
    ok(!h, "got %p\n", h);
    h = GetClipboardData(cf_ole_priv_data);
    ok(!h, "got %p\n", h);

    CloseClipboard();
}