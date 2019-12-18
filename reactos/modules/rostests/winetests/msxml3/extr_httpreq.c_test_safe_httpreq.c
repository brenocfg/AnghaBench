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
typedef  int /*<<< orphan*/  IXMLHttpRequest ;
typedef  int /*<<< orphan*/  IUnknown ;

/* Variables and functions */
 int /*<<< orphan*/  E_ACCESSDENIED ; 
 int /*<<< orphan*/  INTERFACESAFE_FOR_UNTRUSTED_DATA ; 
 int /*<<< orphan*/  IXMLHttpRequest_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_xhr () ; 
 int /*<<< orphan*/  free_bstrs () ; 
 int /*<<< orphan*/  set_safety_opt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_xhr_site (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_open (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_safe_httpreq(void)
{
    IXMLHttpRequest *xhr;

    xhr = create_xhr();

    set_safety_opt((IUnknown*)xhr, INTERFACESAFE_FOR_UNTRUSTED_DATA, -1);
    set_xhr_site(xhr);

    /* different scheme */
    test_open(xhr, "GET", "https://test.winehq.org/tests/hello.html", E_ACCESSDENIED);

    /* different host */
    test_open(xhr, "GET", "http://tests.winehq.org/tests/hello.html", E_ACCESSDENIED);
    test_open(xhr, "GET", "http://www.test.winehq.org/tests/hello.html", E_ACCESSDENIED);

    IXMLHttpRequest_Release(xhr);
    free_bstrs();
}