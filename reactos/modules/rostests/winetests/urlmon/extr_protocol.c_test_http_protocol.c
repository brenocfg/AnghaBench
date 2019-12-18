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
 int BINDF_NEEDFILE ; 
 int BINDF_NOWRITECACHE ; 
 int BINDF_PULLDATA ; 
 int /*<<< orphan*/  CLSID_HttpProtocol ; 
 int /*<<< orphan*/  CLSID_HttpSProtocol ; 
 int /*<<< orphan*/  HTTP_TEST ; 
 int TEST_ABORT ; 
 int TEST_ASYNCREQ ; 
 int TEST_DIRECT_READ ; 
 int TEST_DISABLEAUTOREDIRECT ; 
 int TEST_EMPTY ; 
 int TEST_FIRST_HTTP ; 
 int TEST_FROMCACHE ; 
 int TEST_POST ; 
 int TEST_REDIRECT ; 
 int TEST_USEIURI ; 
 int /*<<< orphan*/  TYMED_HGLOBAL ; 
 int /*<<< orphan*/  TYMED_ISTREAM ; 
 int /*<<< orphan*/  TYMED_NULL ; 
 int bindf ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  test_early_abort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_http_protocol_url (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_http_protocol(void)
{
    static const WCHAR posttest_url[] =
        {'h','t','t','p',':','/','/','t','e','s','t','.','w','i','n','e','h','q','.','o','r','g','/',
         't','e','s','t','s','/','p','o','s','t','.','p','h','p',0};
    static const WCHAR redirect_url[] =
        {'h','t','t','p',':','/','/','t','e','s','t','.','w','i','n','e','h','q','.','o','r','g','/',
         't','e','s','t','s','/','r','e','d','i','r','e','c','t',0};
    static const WCHAR winetest_url[] =
        {'h','t','t','p',':','/','/','t','e','s','t','.','w','i','n','e','h','q','.','o','r','g','/',
         't','e','s','t','s','/','d','a','t','a','.','p','h','p',0};
    static const WCHAR empty_url[] =
        {'h','t','t','p',':','/','/','t','e','s','t','.','w','i','n','e','h','q','.','o','r','g','/',
         't','e','s','t','s','/','e','m','p','t','y','.','j','s',0};
    static const WCHAR cache_only_url[] =
        {'h','t','t','p',':','/','/','t','e','s','t','.','w','i','n','e','h','q','.','o','r','g','/',
         't','e','s','t','s','/','c','a','c','h','e','-','o','n','l','y',0};


    trace("Testing http protocol (not from urlmon)...\n");
    bindf = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA;
    test_http_protocol_url(winetest_url, HTTP_TEST, TEST_FIRST_HTTP, TYMED_NULL);

    trace("Testing http protocol (from urlmon)...\n");
    bindf = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA | BINDF_FROMURLMON;
    test_http_protocol_url(winetest_url, HTTP_TEST, 0, TYMED_NULL);

    trace("Testing http protocol (to file)...\n");
    bindf = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA | BINDF_FROMURLMON | BINDF_NEEDFILE;
    test_http_protocol_url(winetest_url, HTTP_TEST, 0, TYMED_NULL);

    trace("Testing http protocol (post data)...\n");
    bindf = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA | BINDF_FROMURLMON;
    test_http_protocol_url(posttest_url, HTTP_TEST, TEST_FIRST_HTTP|TEST_POST, TYMED_HGLOBAL);

    trace("Testing http protocol (post data stream)...\n");
    test_http_protocol_url(posttest_url, HTTP_TEST, TEST_FIRST_HTTP|TEST_POST|TEST_ASYNCREQ, TYMED_ISTREAM);

    trace("Testing http protocol (direct read)...\n");
    bindf = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA | BINDF_FROMURLMON;
    test_http_protocol_url(winetest_url, HTTP_TEST, TEST_DIRECT_READ|TEST_USEIURI, TYMED_NULL);

    trace("Testing http protocol (redirected)...\n");
    bindf = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA | BINDF_FROMURLMON | BINDF_NOWRITECACHE;
    test_http_protocol_url(redirect_url, HTTP_TEST, TEST_REDIRECT, TYMED_NULL);

    trace("Testing http protocol (redirected, disable auto redirect)...\n");
    bindf = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA | BINDF_FROMURLMON | BINDF_NOWRITECACHE;
    test_http_protocol_url(redirect_url, HTTP_TEST, TEST_REDIRECT | TEST_DISABLEAUTOREDIRECT, TYMED_NULL);

    trace("Testing http protocol empty file...\n");
    bindf = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA | BINDF_FROMURLMON | BINDF_NOWRITECACHE;
    test_http_protocol_url(empty_url, HTTP_TEST, TEST_EMPTY, TYMED_NULL);

    /* This is a bit ugly. We unconditionally disable this test on Wine. This won't work until we have
     * support for reading from cache via HTTP layer in wininet. Until then, Wine will fail badly, affecting
     * other, unrelated, tests. Working around it is not worth the trouble, we may simply make sure those
     * tests work on Windows and have them around for the future.
     */
    if(broken(1)) {
    trace("Testing http protocol (from cache)...\n");
    bindf = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA | BINDF_FROMURLMON;
    test_http_protocol_url(cache_only_url, HTTP_TEST, TEST_FROMCACHE, TYMED_NULL);
    }

    trace("Testing http protocol abort...\n");
    bindf = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE | BINDF_PULLDATA | BINDF_FROMURLMON | BINDF_NOWRITECACHE;
    test_http_protocol_url(winetest_url, HTTP_TEST, TEST_ABORT, TYMED_NULL);

    test_early_abort(&CLSID_HttpProtocol);
    test_early_abort(&CLSID_HttpSProtocol);
}