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
typedef  int /*<<< orphan*/  hash_buf ;
typedef  int /*<<< orphan*/  HCRYPTHASH ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BITMAPINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_SHA1 ; 
 int /*<<< orphan*/  CryptCreateHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptDestroyHash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptGetHashParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptHashData (int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HP_HASHVAL ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crypt_prov ; 
 int get_dib_size (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static char *hash_dib(const BITMAPINFO *bmi, const void *bits)
{
    DWORD dib_size = get_dib_size(bmi);
    HCRYPTHASH hash;
    char *buf;
    BYTE hash_buf[20];
    DWORD hash_size = sizeof(hash_buf);
    int i;
    static const char *hex = "0123456789abcdef";

    if(!crypt_prov) return NULL;

    if(!CryptCreateHash(crypt_prov, CALG_SHA1, 0, 0, &hash)) return NULL;

    CryptHashData(hash, bits, dib_size, 0);

    CryptGetHashParam(hash, HP_HASHVAL, NULL, &hash_size, 0);
    if(hash_size != sizeof(hash_buf)) return NULL;

    CryptGetHashParam(hash, HP_HASHVAL, hash_buf, &hash_size, 0);
    CryptDestroyHash(hash);

    buf = HeapAlloc(GetProcessHeap(), 0, hash_size * 2 + 1);

    for(i = 0; i < hash_size; i++)
    {
        buf[i * 2] = hex[hash_buf[i] >> 4];
        buf[i * 2 + 1] = hex[hash_buf[i] & 0xf];
    }
    buf[i * 2] = '\0';

    return buf;
}