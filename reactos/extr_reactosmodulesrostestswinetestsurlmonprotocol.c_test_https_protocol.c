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
typedef  char WCHAR ;

/* Variables and functions */
 int BINDF_ASYNCHRONOUS ; 
 int BINDF_ASYNCSTORAGE ; 
 int BINDF_FROMURLMON ; 
 int BINDF_NOWRITECACHE ; 
 int BINDF_PULLDATA ; 
 int /*<<< orphan*/  HTTPS_TEST ; 
 int /*<<< orphan*/  TEST_FIRST_HTTP ; 
 int /*<<< orphan*/  TYMED_NULL ; 
 int bindf ; 
 int /*<<< orphan*/  test_http_protocol_url (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_https_protocol(void)
{
    static const WCHAR https_winehq_url[] =
        {'h','t','t','p','s',':','/','/','t','e','s','t','.','w','i','n','e','h','q','.','o','r','g','/',
         't','e','s','t','s','/','h','e','l','l','o','.','h','t','m','l',0};

    trace("Testing https protocol (from urlmon)...\n");
    bindf = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA | BINDF_FROMURLMON | BINDF_NOWRITECACHE;
    test_http_protocol_url(https_winehq_url, HTTPS_TEST, TEST_FIRST_HTTP, TYMED_NULL);
}