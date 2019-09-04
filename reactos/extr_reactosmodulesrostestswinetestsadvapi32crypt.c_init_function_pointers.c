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
 void* pCryptAcquireContextA ; 
 void* pCryptContextAddRef ; 
 void* pCryptCreateHash ; 
 void* pCryptDecrypt ; 
 void* pCryptDeriveKey ; 
 void* pCryptDestroyHash ; 
 void* pCryptDestroyKey ; 
 void* pCryptDuplicateHash ; 
 void* pCryptDuplicateKey ; 
 void* pCryptEncrypt ; 
 void* pCryptEnumProviderTypesA ; 
 void* pCryptEnumProvidersA ; 
 void* pCryptExportKey ; 
 void* pCryptGenKey ; 
 void* pCryptGenRandom ; 
 void* pCryptGetDefaultProviderA ; 
 void* pCryptGetHashParam ; 
 void* pCryptGetKeyParam ; 
 void* pCryptGetProvParam ; 
 void* pCryptGetUserKey ; 
 void* pCryptHashData ; 
 void* pCryptHashSessionKey ; 
 void* pCryptImportKey ; 
 void* pCryptReleaseContext ; 
 void* pCryptSetHashParam ; 
 void* pCryptSetKeyParam ; 
 void* pCryptSetProvParam ; 
 void* pCryptSetProviderExA ; 
 void* pCryptSignHashW ; 
 void* pCryptVerifySignatureW ; 
 void* pSystemFunction004 ; 
 void* pSystemFunction005 ; 
 void* pSystemFunction036 ; 

__attribute__((used)) static void init_function_pointers(void)
{
    HMODULE hadvapi32 = GetModuleHandleA("advapi32.dll");

    pCryptAcquireContextA = (void*)GetProcAddress(hadvapi32, "CryptAcquireContextA");
    pCryptEnumProviderTypesA = (void*)GetProcAddress(hadvapi32, "CryptEnumProviderTypesA");
    pCryptEnumProvidersA = (void*)GetProcAddress(hadvapi32, "CryptEnumProvidersA");
    pCryptGetDefaultProviderA = (void*)GetProcAddress(hadvapi32, "CryptGetDefaultProviderA");
    pCryptReleaseContext = (void*)GetProcAddress(hadvapi32, "CryptReleaseContext");
    pCryptSetProviderExA = (void*)GetProcAddress(hadvapi32, "CryptSetProviderExA");
    pCryptCreateHash = (void*)GetProcAddress(hadvapi32, "CryptCreateHash");
    pCryptDestroyHash = (void*)GetProcAddress(hadvapi32, "CryptDestroyHash");
    pCryptGenRandom = (void*)GetProcAddress(hadvapi32, "CryptGenRandom");
    pCryptContextAddRef = (void*)GetProcAddress(hadvapi32, "CryptContextAddRef");
    pCryptGenKey = (void*)GetProcAddress(hadvapi32, "CryptGenKey");
    pCryptDestroyKey = (void*)GetProcAddress(hadvapi32, "CryptDestroyKey");
    pCryptDecrypt = (void*)GetProcAddress(hadvapi32, "CryptDecrypt");
    pCryptDeriveKey = (void*)GetProcAddress(hadvapi32, "CryptDeriveKey");
    pCryptDuplicateHash = (void*)GetProcAddress(hadvapi32, "CryptDuplicateHash");
    pCryptDuplicateKey = (void*)GetProcAddress(hadvapi32, "CryptDuplicateKey");
    pCryptEncrypt = (void*)GetProcAddress(hadvapi32, "CryptEncrypt");
    pCryptExportKey = (void*)GetProcAddress(hadvapi32, "CryptExportKey");
    pCryptGetHashParam = (void*)GetProcAddress(hadvapi32, "CryptGetHashParam");
    pCryptGetKeyParam = (void*)GetProcAddress(hadvapi32, "CryptGetKeyParam");
    pCryptGetProvParam = (void*)GetProcAddress(hadvapi32, "CryptGetProvParam");
    pCryptGetUserKey = (void*)GetProcAddress(hadvapi32, "CryptGetUserKey");
    pCryptHashData = (void*)GetProcAddress(hadvapi32, "CryptHashData");
    pCryptHashSessionKey = (void*)GetProcAddress(hadvapi32, "CryptHashSessionKey");
    pCryptImportKey = (void*)GetProcAddress(hadvapi32, "CryptImportKey");
    pCryptSignHashW = (void*)GetProcAddress(hadvapi32, "CryptSignHashW");
    pCryptSetHashParam = (void*)GetProcAddress(hadvapi32, "CryptSetHashParam");
    pCryptSetKeyParam = (void*)GetProcAddress(hadvapi32, "CryptSetKeyParam");
    pCryptSetProvParam = (void*)GetProcAddress(hadvapi32, "CryptSetProvParam");
    pCryptVerifySignatureW = (void*)GetProcAddress(hadvapi32, "CryptVerifySignatureW");
    pSystemFunction004 = (void*)GetProcAddress(hadvapi32, "SystemFunction004");
    pSystemFunction005 = (void*)GetProcAddress(hadvapi32, "SystemFunction005");
    pSystemFunction036 = (void*)GetProcAddress(hadvapi32, "SystemFunction036");
}