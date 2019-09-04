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
typedef  int /*<<< orphan*/ * PCRYPT_DATA_BLOB ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CRYPT_DATA_BLOB ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CRYPT_ConstructBlob (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * CryptMemAlloc (int) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL CRYPT_ConstructBlobArray(DWORD *outCBlobs,
 PCRYPT_DATA_BLOB *outPBlobs, DWORD cBlobs, const CRYPT_DATA_BLOB *pBlobs)
{
    BOOL ret = TRUE;

    *outCBlobs = cBlobs;
    if (cBlobs)
    {
        *outPBlobs = CryptMemAlloc(cBlobs * sizeof(CRYPT_DATA_BLOB));
        if (*outPBlobs)
        {
            DWORD i;

            memset(*outPBlobs, 0, cBlobs * sizeof(CRYPT_DATA_BLOB));
            for (i = 0; ret && i < cBlobs; i++)
                ret = CRYPT_ConstructBlob(&(*outPBlobs)[i], &pBlobs[i]);
        }
        else
            ret = FALSE;
    }
    return ret;
}