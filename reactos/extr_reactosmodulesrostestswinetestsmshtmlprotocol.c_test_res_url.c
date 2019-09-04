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
typedef  int /*<<< orphan*/  url ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IInternetProtocol ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_ResProtocol ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IInternetProtocol ; 
 scalar_t__ IInternetProtocol_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,scalar_t__*) ; 
 scalar_t__ IInternetProtocol_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IInternetProtocol_Terminate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int INTERNET_MAX_URL_LENGTH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  protocol_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  res_url_base ; 
 int res_url_base_len ; 

__attribute__((used)) static void test_res_url(const char *url_suffix)
{
    WCHAR url[INTERNET_MAX_URL_LENGTH];
    IInternetProtocol *protocol;
    ULONG size, ref;
    BYTE buf[100];
    HRESULT hres;

    memcpy(url, res_url_base, res_url_base_len*sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP, 0, url_suffix, -1, url+res_url_base_len, sizeof(url)/sizeof(WCHAR)-res_url_base_len);

    hres = CoCreateInstance(&CLSID_ResProtocol, NULL, CLSCTX_INPROC_SERVER, &IID_IInternetProtocol, (void**)&protocol);
    ok(hres == S_OK, "Could not create ResProtocol instance: %08x\n", hres);

    protocol_start(protocol, url);

    hres = IInternetProtocol_Read(protocol, buf, sizeof(buf), &size);
    ok(hres == S_OK, "Read failed: %08x\n", hres);

    hres = IInternetProtocol_Terminate(protocol, 0);
    ok(hres == S_OK, "Terminate failed: %08x\n", hres);


    ref = IInternetProtocol_Release(protocol);
    ok(!ref, "ref=%u\n", ref);
}