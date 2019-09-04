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
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pCoInternetCompareUrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  url1 ; 
 int /*<<< orphan*/  url3 ; 

__attribute__((used)) static void test_CoInternetCompareUrl(void)
{
    HRESULT hres;

    hres = pCoInternetCompareUrl(url1, url1, 0);
    ok(hres == S_OK, "CoInternetCompareUrl failed: %08x\n", hres);

    hres = pCoInternetCompareUrl(url1, url3, 0);
    ok(hres == S_FALSE, "CoInternetCompareUrl failed: %08x\n", hres);

    hres = pCoInternetCompareUrl(url3, url1, 0);
    ok(hres == S_FALSE, "CoInternetCompareUrl failed: %08x\n", hres);
}