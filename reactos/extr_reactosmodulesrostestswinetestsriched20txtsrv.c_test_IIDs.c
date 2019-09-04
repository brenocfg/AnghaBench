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

/* Variables and functions */
 int /*<<< orphan*/  IsEqualIID (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expected_iid_itexthost ; 
 int /*<<< orphan*/  expected_iid_itexthost2 ; 
 int /*<<< orphan*/  expected_iid_itextservices ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pIID_ITextHost ; 
 int /*<<< orphan*/  pIID_ITextHost2 ; 
 int /*<<< orphan*/  pIID_ITextServices ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_IIDs(void)
{
    ok(IsEqualIID(pIID_ITextServices, &expected_iid_itextservices),
       "unexpected value for IID_ITextServices: %s\n", wine_dbgstr_guid(pIID_ITextServices));
    ok(IsEqualIID(pIID_ITextHost, &expected_iid_itexthost),
       "unexpected value for IID_ITextHost: %s\n", wine_dbgstr_guid(pIID_ITextHost));
    ok(IsEqualIID(pIID_ITextHost2, &expected_iid_itexthost2),
       "unexpected value for IID_ITextHost2: %s\n", wine_dbgstr_guid(pIID_ITextHost2));
}