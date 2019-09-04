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
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 void* pCertCreateSelfSignCertificate ; 
 void* pCertGetValidUsages ; 
 void* pCryptAcquireCertificatePrivateKey ; 
 void* pCryptAcquireContextA ; 
 void* pCryptEncodeObjectEx ; 
 void* pCryptVerifyCertificateSignatureEx ; 
 int /*<<< orphan*/  trace (char*,char*) ; 

__attribute__((used)) static void init_function_pointers(void)
{
    HMODULE hCrypt32 = GetModuleHandleA("crypt32.dll");
    HMODULE hAdvapi32 = GetModuleHandleA("advapi32.dll");

#define GET_PROC(dll, func) \
    p ## func = (void *)GetProcAddress(dll, #func); \
    if(!p ## func) \
      trace("GetProcAddress(%s) failed\n", #func);

    GET_PROC(hCrypt32, CertCreateSelfSignCertificate)
    GET_PROC(hCrypt32, CertGetValidUsages)
    GET_PROC(hCrypt32, CryptAcquireCertificatePrivateKey)
    GET_PROC(hCrypt32, CryptEncodeObjectEx)
    GET_PROC(hCrypt32, CryptVerifyCertificateSignatureEx)

    GET_PROC(hAdvapi32, CryptAcquireContextA)

#undef GET_PROC
}