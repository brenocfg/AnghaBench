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
typedef  int /*<<< orphan*/  WINECRYPT_CERTSTORE ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int DWORD ;

/* Variables and functions */
 int CERT_SYSTEM_STORE_RELOCATE_FLAG ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,int,void const*) ; 
 void const* debugstr_w (void const*) ; 

__attribute__((used)) static WINECRYPT_CERTSTORE *CRYPT_PhysOpenStoreW(HCRYPTPROV hCryptProv,
 DWORD dwFlags, const void *pvPara)
{
    if (dwFlags & CERT_SYSTEM_STORE_RELOCATE_FLAG)
        FIXME("(%ld, %08x, %p): stub\n", hCryptProv, dwFlags, pvPara);
    else
        FIXME("(%ld, %08x, %s): stub\n", hCryptProv, dwFlags,
         debugstr_w(pvPara));
    return NULL;
}