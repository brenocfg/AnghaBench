#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* pCryptSIPGetSignedDataMsg ;
struct TYPE_7__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_9__ {int member_0; int member_1; int member_2; TYPE_1__ member_3; } ;
struct TYPE_8__ {int cbSize; void* pfGet; void* pfRemove; void* pfVerify; void* pfCreate; void* pfPut; } ;
typedef  TYPE_2__ SIP_DISPATCH_INFO ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  TYPE_3__ GUID ;
typedef  int BOOL ;

/* Variables and functions */
 int CryptSIPLoad (TYPE_3__*,int,TYPE_2__*) ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ TRUST_E_SUBJECT_FORM_UNKNOWN ; 
 void* funcCryptSIPCreateIndirectData ; 
 void* funcCryptSIPGetSignedDataMsg ; 
 void* funcCryptSIPPutSignedDataMsg ; 
 void* funcCryptSIPRemoveSignedDataMsg ; 
 void* funcCryptSIPVerifyIndirectData ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_SIPLoad(void)
{
    BOOL ret;
    GUID subject;
    static GUID dummySubject = { 0xdeadbeef, 0xdead, 0xbeef, { 0xde,0xad,0xbe,0xef,0xde,0xad,0xbe,0xef }};
    static GUID unknown      = { 0xC689AABA, 0x8E78, 0x11D0, { 0x8C,0x47,0x00,0xC0,0x4F,0xC2,0x95,0xEE }}; /* WINTRUST.DLL */
    static GUID unknown2     = { 0xDE351A43, 0x8E59, 0x11D0, { 0x8C,0x47,0x00,0xC0,0x4F,0xC2,0x95,0xEE }}; /* WINTRUST.DLL */
    /* The next SIP is available on Windows and on Wine */
    static GUID unknown3     = { 0x000C10F1, 0x0000, 0x0000, { 0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46 }}; /* MSISIP.DLL */
    SIP_DISPATCH_INFO sdi;
    HMODULE hCrypt;

    /* All NULL */
    SetLastError(0xdeadbeef);
    ret = CryptSIPLoad(NULL, 0, NULL);
    ok ( !ret, "Expected CryptSIPLoad to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got 0x%08x\n", GetLastError());

    /* Only pSipDispatch NULL */
    SetLastError(0xdeadbeef);
    ret = CryptSIPLoad(&subject, 0, NULL);
    ok ( !ret, "Expected CryptSIPLoad to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got 0x%08x\n", GetLastError());

    /* No NULLs, but nonexistent pgSubject */
    SetLastError(0xdeadbeef);
    memset(&sdi, 0, sizeof(SIP_DISPATCH_INFO));
    sdi.cbSize = sizeof(SIP_DISPATCH_INFO);
    sdi.pfGet = (pCryptSIPGetSignedDataMsg)0xdeadbeef;
    ret = CryptSIPLoad(&dummySubject, 0, &sdi);
    ok ( !ret, "Expected CryptSIPLoad to fail\n");
    ok ( GetLastError() == TRUST_E_SUBJECT_FORM_UNKNOWN,
        "Expected TRUST_E_SUBJECT_FORM_UNKNOWN, got 0x%08x\n", GetLastError());
    ok( sdi.pfGet == (pCryptSIPGetSignedDataMsg)0xdeadbeef, "Expected no change to the function pointer\n");

    hCrypt = GetModuleHandleA("crypt32.dll");
    funcCryptSIPGetSignedDataMsg = (void*)GetProcAddress(hCrypt, "CryptSIPGetSignedDataMsg");
    funcCryptSIPPutSignedDataMsg = (void*)GetProcAddress(hCrypt, "CryptSIPPutSignedDataMsg");
    funcCryptSIPCreateIndirectData = (void*)GetProcAddress(hCrypt, "CryptSIPCreateIndirectData");
    funcCryptSIPVerifyIndirectData = (void*)GetProcAddress(hCrypt, "CryptSIPVerifyIndirectData");
    funcCryptSIPRemoveSignedDataMsg = (void*)GetProcAddress(hCrypt, "CryptSIPRemoveSignedDataMsg");

    /* All OK */
    SetLastError(0xdeadbeef);
    memset(&sdi, 0, sizeof(SIP_DISPATCH_INFO));
    sdi.cbSize = sizeof(SIP_DISPATCH_INFO);
    sdi.pfGet = (pCryptSIPGetSignedDataMsg)0xdeadbeef;
    ret = CryptSIPLoad(&unknown, 0, &sdi);
    ok ( ret, "Expected CryptSIPLoad to succeed\n");
    /* On native the last error will always be ERROR_PROC_NOT_FOUND as native searches for the function DllCanUnloadNow
     * in WINTRUST.DLL (in this case). This function is not available in WINTRUST.DLL.
     * For now there's no need to implement this is Wine as I doubt any program will rely on
     * this last error when the call succeeded.
     */
    ok( sdi.pfGet != (pCryptSIPGetSignedDataMsg)0xdeadbeef, "Expected a function pointer to be loaded.\n");

    /* The function addresses returned by CryptSIPLoad are actually the addresses of
     * crypt32's own functions. A function calling these addresses will end up first
     * calling crypt32 functions which in its turn call the equivalent in the SIP
     * as dictated by the given GUID.
     */
    if (funcCryptSIPGetSignedDataMsg && funcCryptSIPPutSignedDataMsg && funcCryptSIPCreateIndirectData &&
        funcCryptSIPVerifyIndirectData && funcCryptSIPRemoveSignedDataMsg)
        ok (sdi.pfGet == funcCryptSIPGetSignedDataMsg &&
            sdi.pfPut == funcCryptSIPPutSignedDataMsg &&
            sdi.pfCreate == funcCryptSIPCreateIndirectData &&
            sdi.pfVerify == funcCryptSIPVerifyIndirectData &&
            sdi.pfRemove == funcCryptSIPRemoveSignedDataMsg,
            "Expected function addresses to be from crypt32\n");
    else
        trace("Couldn't load function pointers\n");

    /* All OK, but different GUID (same SIP though) */
    SetLastError(0xdeadbeef);
    memset(&sdi, 0, sizeof(SIP_DISPATCH_INFO));
    sdi.cbSize = sizeof(SIP_DISPATCH_INFO);
    sdi.pfGet = (pCryptSIPGetSignedDataMsg)0xdeadbeef;
    ret = CryptSIPLoad(&unknown2, 0, &sdi);
    ok ( ret, "Expected CryptSIPLoad to succeed\n");
    /* This call on its own would have resulted in an ERROR_PROC_NOT_FOUND, but the previous
     * call to CryptSIPLoad already loaded wintrust.dll. As this information is cached,
     * CryptSIPLoad will not try to search for the already mentioned DllCanUnloadNow.
     */
    ok( sdi.pfGet != (pCryptSIPGetSignedDataMsg)0xdeadbeef, "Expected a function pointer to be loaded.\n");

    /* All OK, but other SIP */
    SetLastError(0xdeadbeef);
    memset(&sdi, 0, sizeof(SIP_DISPATCH_INFO));
    sdi.cbSize = sizeof(SIP_DISPATCH_INFO);
    sdi.pfGet = (pCryptSIPGetSignedDataMsg)0xdeadbeef;
    ret = CryptSIPLoad(&unknown3, 0, &sdi);
    if (ret)
    {
        /* The SIP is known so we can safely assume that the next tests can be done */

        /* As msisip.dll is not checked yet by any of the previous calls, the
         * function DllCanUnloadNow will be checked again in msisip.dll (it's not present)
         */
        ok( sdi.pfGet != (pCryptSIPGetSignedDataMsg)0xdeadbeef, "Expected a function pointer to be loaded.\n");

        /* This is another SIP but this test proves the function addresses are the same as
         * in the previous test.
         */
        if (funcCryptSIPGetSignedDataMsg && funcCryptSIPPutSignedDataMsg && funcCryptSIPCreateIndirectData &&
            funcCryptSIPVerifyIndirectData && funcCryptSIPRemoveSignedDataMsg)
            ok (sdi.pfGet == funcCryptSIPGetSignedDataMsg &&
                sdi.pfPut == funcCryptSIPPutSignedDataMsg &&
                sdi.pfCreate == funcCryptSIPCreateIndirectData &&
                sdi.pfVerify == funcCryptSIPVerifyIndirectData &&
                sdi.pfRemove == funcCryptSIPRemoveSignedDataMsg,
                "Expected function addresses to be from crypt32\n");
        else
            trace("Couldn't load function pointers\n");
    }

    /* Reserved parameter not 0 */
    SetLastError(0xdeadbeef);
    memset(&sdi, 0, sizeof(SIP_DISPATCH_INFO));
    sdi.cbSize = sizeof(SIP_DISPATCH_INFO);
    sdi.pfGet = (pCryptSIPGetSignedDataMsg)0xdeadbeef;
    ret = CryptSIPLoad(&unknown, 1, &sdi);
    ok ( !ret, "Expected CryptSIPLoad to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got 0x%08x\n", GetLastError());
    ok( sdi.pfGet == (pCryptSIPGetSignedDataMsg)0xdeadbeef, "Expected no change to the function pointer\n");
}