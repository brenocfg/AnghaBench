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
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INTERNET_CANNOT_CONNECT ; 
 int /*<<< orphan*/  ERROR_INTERNET_CONNECTION_ABORTED ; 
 int /*<<< orphan*/  ERROR_INTERNET_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR_INTERNET_INVALID_OPERATION ; 
 int /*<<< orphan*/  ERROR_INTERNET_INVALID_URL ; 
 int /*<<< orphan*/  ERROR_INTERNET_ITEM_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_INTERNET_NAME_NOT_RESOLVED ; 
 int /*<<< orphan*/  ERROR_INTERNET_OPERATION_CANCELLED ; 
 int /*<<< orphan*/  ERROR_INTERNET_SEC_CERT_CN_INVALID ; 
 int /*<<< orphan*/  ERROR_INTERNET_SEC_CERT_DATE_INVALID ; 
 int /*<<< orphan*/  ERROR_INTERNET_TIMEOUT ; 
 int /*<<< orphan*/  ERROR_INTERNET_UNRECOGNIZED_SCHEME ; 
 int /*<<< orphan*/  FORMAT_MESSAGE_FROM_HMODULE ; 
 int /*<<< orphan*/  FORMAT_MESSAGE_FROM_SYSTEM ; 
 scalar_t__ FormatMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_NEUTRAL ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_format_message(HMODULE hdll)
{
    DWORD ret;
    CHAR out[0x100];

    /* These messages come from wininet and not the system. */
    ret = FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM , NULL, ERROR_INTERNET_TIMEOUT,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), out, sizeof(out), NULL);
    ok(ret == 0, "FormatMessageA returned %d\n", ret);

    ret = FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE, hdll, ERROR_INTERNET_TIMEOUT,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), out, sizeof(out), NULL);
    ok(ret != 0, "FormatMessageA returned %d\n", ret);

    ret = FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE, hdll, ERROR_INTERNET_INTERNAL_ERROR,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), out, sizeof(out), NULL);
    ok(ret != 0, "FormatMessageA returned %d\n", ret);

    ret = FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE, hdll, ERROR_INTERNET_INVALID_URL,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), out, sizeof(out), NULL);
    ok(ret != 0, "FormatMessageA returned %d\n", ret);

    ret = FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE, hdll, ERROR_INTERNET_UNRECOGNIZED_SCHEME,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), out, sizeof(out), NULL);
    ok(ret != 0, "FormatMessageA returned %d\n", ret);

    ret = FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE, hdll, ERROR_INTERNET_NAME_NOT_RESOLVED,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), out, sizeof(out), NULL);
    ok(ret != 0, "FormatMessageA returned %d\n", ret);

    ret = FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE, hdll, ERROR_INTERNET_INVALID_OPERATION,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), out, sizeof(out), NULL);
    ok(ret != 0 || broken(!ret) /* XP, w2k3 */, "FormatMessageA returned %d\n", ret);

    ret = FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE, hdll, ERROR_INTERNET_OPERATION_CANCELLED,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), out, sizeof(out), NULL);
    ok(ret != 0, "FormatMessageA returned %d\n", ret);

    ret = FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE, hdll, ERROR_INTERNET_ITEM_NOT_FOUND,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), out, sizeof(out), NULL);
    ok(ret != 0, "FormatMessageA returned %d\n", ret);

    ret = FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE, hdll, ERROR_INTERNET_CANNOT_CONNECT,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), out, sizeof(out), NULL);
    ok(ret != 0, "FormatMessageA returned %d\n", ret);

    ret = FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE, hdll, ERROR_INTERNET_CONNECTION_ABORTED,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), out, sizeof(out), NULL);
    ok(ret != 0, "FormatMessageA returned %d\n", ret);

    ret = FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE, hdll, ERROR_INTERNET_SEC_CERT_DATE_INVALID,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), out, sizeof(out), NULL);
    ok(ret != 0, "FormatMessageA returned %d\n", ret);

    ret = FormatMessageA(FORMAT_MESSAGE_FROM_HMODULE, hdll, ERROR_INTERNET_SEC_CERT_CN_INVALID,
                         MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), out, sizeof(out), NULL);
    ok(ret != 0, "FormatMessageA returned %d\n", ret);
}