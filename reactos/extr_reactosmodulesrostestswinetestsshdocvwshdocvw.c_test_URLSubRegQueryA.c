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
typedef  int /*<<< orphan*/  buffer ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  char CHAR ;

/* Variables and functions */
 scalar_t__ E_FAIL ; 
 int INTERNET_MAX_URL_LENGTH ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_SZ ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  appdata ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  common_appdata ; 
 int /*<<< orphan*/  default_page_url ; 
 int /*<<< orphan*/  does_not_exist ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ pURLSubRegQueryA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  regpath_iemain ; 
 int /*<<< orphan*/  regpath_shellfolders ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  start_page ; 

__attribute__((used)) static void test_URLSubRegQueryA(void)
{
    CHAR buffer[INTERNET_MAX_URL_LENGTH];
    HRESULT hr;
    DWORD used;
    DWORD len;

    if (!pURLSubRegQueryA) {
        skip("URLSubRegQueryA not found\n");
        return;
    }

    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    /* called by inetcpl.cpl */
    hr = pURLSubRegQueryA(regpath_iemain, default_page_url, REG_SZ, buffer, INTERNET_MAX_URL_LENGTH, -1);
    ok(hr == E_FAIL || hr == S_OK, "got 0x%x (expected E_FAIL or S_OK)\n", hr);

    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    /* called by inetcpl.cpl */
    hr = pURLSubRegQueryA(regpath_iemain, start_page, REG_SZ, buffer, INTERNET_MAX_URL_LENGTH, -1);
    len = lstrlenA(buffer);
    /* respect privacy: do not dump the url */
    ok(hr == S_OK, "got 0x%x and %d (expected S_OK)\n", hr, len);

    /* test buffer length: just large enough */
    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    hr = pURLSubRegQueryA(regpath_iemain, start_page, REG_SZ, buffer, len+1, -1);
    used = lstrlenA(buffer);
    /* respect privacy: do not dump the url */
    ok((hr == S_OK) && (used == len),
        "got 0x%x and %d (expected S_OK and %d)\n", hr, used, len);

    /* no space for terminating 0: result is truncated */
    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    hr = pURLSubRegQueryA(regpath_iemain, start_page, REG_SZ, buffer, len, -1);
    used = lstrlenA(buffer);
    ok((hr == S_OK) && (used == len - 1),
        "got 0x%x and %d (expected S_OK and %d)\n", hr, used, len - 1);

    /* no space for the complete result: truncate another char */
    if (len > 1) {
        memset(buffer, '#', sizeof(buffer)-1);
        buffer[sizeof(buffer)-1] = '\0';
        hr = pURLSubRegQueryA(regpath_iemain, start_page, REG_SZ, buffer, len-1, -1);
        used = lstrlenA(buffer);
        ok((hr == S_OK) && (used == (len - 2)),
            "got 0x%x and %d (expected S_OK and %d)\n", hr, used, len - 2);
    }

    /* only space for the terminating 0: function still succeeded */
    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    hr = pURLSubRegQueryA(regpath_iemain, start_page, REG_SZ, buffer, 1, -1);
    used = lstrlenA(buffer);
    ok((hr == S_OK) && !used,
        "got 0x%x and %d (expected S_OK and 0)\n", hr, used);

    /* size of buffer is 0, but the function still succeed.
       buffer[0] is cleared in IE 5.01 and IE 5.5 (Buffer Overflow) */
    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    hr = pURLSubRegQueryA(regpath_iemain, start_page, REG_SZ, buffer, 0, -1);
    used = lstrlenA(buffer);
    ok( (hr == S_OK) &&
        ((used == INTERNET_MAX_URL_LENGTH - 1) || broken(used == 0)) ,
        "got 0x%x and %d (expected S_OK and INTERNET_MAX_URL_LENGTH - 1)\n",
        hr, used);

    /* still succeed without a buffer for the result */
    hr = pURLSubRegQueryA(regpath_iemain, start_page, REG_SZ, NULL, 0, -1);
    ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);

    /* still succeed, when a length is given without a buffer */
    hr = pURLSubRegQueryA(regpath_iemain, start_page, REG_SZ, NULL, INTERNET_MAX_URL_LENGTH, -1);
    ok(hr == S_OK, "got 0x%x (expected S_OK)\n", hr);

    /* this value does not exist */
    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    hr = pURLSubRegQueryA(regpath_iemain, does_not_exist, REG_SZ, buffer, INTERNET_MAX_URL_LENGTH, -1);
    /* random bytes are copied to the buffer */
    ok((hr == E_FAIL), "got 0x%x (expected E_FAIL)\n", hr);

    /* the third parameter is ignored. Is it really a type? (data is REG_SZ) */
    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    hr = pURLSubRegQueryA(regpath_iemain, start_page, REG_DWORD, buffer, INTERNET_MAX_URL_LENGTH, -1);
    used = lstrlenA(buffer);
    ok((hr == S_OK) && (used == len),
        "got 0x%x and %d (expected S_OK and %d)\n", hr, used, len);

    /* the function works for HKCU and HKLM */
    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    hr = pURLSubRegQueryA(regpath_shellfolders, appdata, REG_SZ, buffer, INTERNET_MAX_URL_LENGTH, -1);
    used = lstrlenA(buffer);
    ok(hr == S_OK, "got 0x%x and %d (expected S_OK)\n", hr, used);

    memset(buffer, '#', sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';
    hr = pURLSubRegQueryA(regpath_shellfolders, common_appdata, REG_SZ, buffer, INTERNET_MAX_URL_LENGTH, -1);
    used = lstrlenA(buffer);
    ok(hr == S_OK, "got 0x%x and %d (expected S_OK)\n", hr, used);

    /* todo: what does the last parameter mean? */
}