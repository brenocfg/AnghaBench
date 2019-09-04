#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cbData; int /*<<< orphan*/ * pbData; } ;
typedef  int /*<<< orphan*/  HCRYPTHASH ;
typedef  int DWORD ;
typedef  TYPE_1__ DATA_BLOB ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CryptGetHashParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HP_HASHSIZE ; 
 int /*<<< orphan*/  HP_HASHVAL ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOL convert_hash_to_blob(HCRYPTHASH hHash, DATA_BLOB * blob)
{
    DWORD dwSize;

    TRACE("called\n");

    if (!blob) return FALSE;

    dwSize=sizeof(DWORD);
    if (!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE*)&blob->cbData,
                           &dwSize, 0))
    {
        ERR("failed to get hash size\n");
        return FALSE;
    }

    if (!(blob->pbData=CryptMemAlloc(blob->cbData)))
    {
        ERR("failed to allocate blob memory\n");
        return FALSE;
    }

    dwSize=blob->cbData;
    if (!CryptGetHashParam(hHash, HP_HASHVAL, blob->pbData, &dwSize, 0))
    {
        ERR("failed to get hash value\n");
        CryptMemFree(blob->pbData);
        blob->pbData=NULL;
        blob->cbData=0;
        return FALSE;
    }

    return TRUE;
}