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
struct TYPE_3__ {int /*<<< orphan*/  sha512; int /*<<< orphan*/  sha384; int /*<<< orphan*/  sha256; int /*<<< orphan*/  sha; int /*<<< orphan*/  md5; int /*<<< orphan*/  md4; int /*<<< orphan*/  md2; } ;
typedef  TYPE_1__ HASH_CONTEXT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int ALG_ID ;

/* Variables and functions */
 int /*<<< orphan*/  A_SHAUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
#define  CALG_MD2 134 
#define  CALG_MD4 133 
#define  CALG_MD5 132 
#define  CALG_SHA 131 
#define  CALG_SHA_256 130 
#define  CALG_SHA_384 129 
#define  CALG_SHA_512 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MD4Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTE_BAD_ALGID ; 
 int /*<<< orphan*/  SHA256_Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA384_Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA512_Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  md2_process (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

BOOL update_hash_impl(ALG_ID aiAlgid, HASH_CONTEXT *pHashContext, const BYTE *pbData,
                      DWORD dwDataLen) 
{
    switch (aiAlgid)
    {
        case CALG_MD2:
            md2_process(&pHashContext->md2, pbData, dwDataLen);
            break;
        
        case CALG_MD4:
            MD4Update(&pHashContext->md4, pbData, dwDataLen);
            break;
    
        case CALG_MD5:
            MD5Update(&pHashContext->md5, pbData, dwDataLen);
            break;
        
        case CALG_SHA:
            A_SHAUpdate(&pHashContext->sha, pbData, dwDataLen);
            break;
        
        case CALG_SHA_256:
            SHA256_Update(&pHashContext->sha256, pbData, dwDataLen);
            break;

        case CALG_SHA_384:
            SHA384_Update(&pHashContext->sha384, pbData, dwDataLen);
            break;

        case CALG_SHA_512:
            SHA512_Update(&pHashContext->sha512, pbData, dwDataLen);
            break;

        default:
            SetLastError(NTE_BAD_ALGID);
            return FALSE;
    }

    return TRUE;
}