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
typedef  int /*<<< orphan*/  IMimeInternational ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HCHARSET ;

/* Variables and functions */
 int /*<<< orphan*/  CHARSET_BODY ; 
 int /*<<< orphan*/  GetACP () ; 
 scalar_t__ IMimeInternational_FindCharset (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 scalar_t__ IMimeInternational_GetCodePageCharset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ IMimeInternational_GetDefaultCharset (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IMimeInternational_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IMimeInternational_SetDefaultCharset (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ MimeOleGetInternat (int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_defaultcharset(void)
{
    IMimeInternational *internat;
    HRESULT hr;
    HCHARSET hcs_default, hcs, hcs_windows_1251;

    hr = MimeOleGetInternat(&internat);
    ok(hr == S_OK, "ret %08x\n", hr);

    hr = IMimeInternational_GetDefaultCharset(internat, &hcs_default);
    ok(hr == S_OK, "ret %08x\n", hr);
    hr = IMimeInternational_GetCodePageCharset(internat, GetACP(), CHARSET_BODY, &hcs);
    ok(hr == S_OK, "ret %08x\n", hr);
    ok(hcs_default == hcs, "Unexpected default charset\n");

    hr = IMimeInternational_FindCharset(internat, "windows-1251", &hcs_windows_1251);
    ok(hr == S_OK, "got %08x\n", hr);
    hr = IMimeInternational_SetDefaultCharset(internat, hcs_windows_1251);
    ok(hr == S_OK, "ret %08x\n", hr);
    hr = IMimeInternational_GetDefaultCharset(internat, &hcs);
    ok(hr == S_OK, "ret %08x\n", hr);
    ok(hcs == hcs_windows_1251, "didn't retrieve recently set default\n");
    /* Set the old default back again */
    hr = IMimeInternational_SetDefaultCharset(internat, hcs_default);
    ok(hr == S_OK, "ret %08x\n", hr);

    IMimeInternational_Release(internat);
}