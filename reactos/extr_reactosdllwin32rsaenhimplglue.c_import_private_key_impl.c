#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  e; int /*<<< orphan*/  d; int /*<<< orphan*/  qP; int /*<<< orphan*/  dQ; int /*<<< orphan*/  dP; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  N; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_1__ rsa; } ;
typedef  TYPE_2__ KEY_CONTEXT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MP_OKAY ; 
 int /*<<< orphan*/  NTE_FAIL ; 
 int /*<<< orphan*/  PK_PRIVATE ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int min (int,int) ; 
 scalar_t__ mp_init_multi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_read_unsigned_bin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_set_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reverse_bytes (int /*<<< orphan*/ *,int) ; 

BOOL import_private_key_impl(const BYTE *pbSrc, KEY_CONTEXT *pKeyContext, DWORD dwKeyLen,
                             DWORD dwDataLen, DWORD dwPubExp)
{
    BYTE *pbTemp, *pbBigNum;

    if (mp_init_multi(&pKeyContext->rsa.e, &pKeyContext->rsa.d, &pKeyContext->rsa.N, 
                      &pKeyContext->rsa.dQ,&pKeyContext->rsa.dP,&pKeyContext->rsa.qP, 
                      &pKeyContext->rsa.p, &pKeyContext->rsa.q, NULL) != MP_OKAY)
    {
        SetLastError(NTE_FAIL);
        return FALSE;
    }

    pbTemp = HeapAlloc(GetProcessHeap(), 0, 2*dwKeyLen+5*((dwKeyLen+1)>>1));
    if (!pbTemp) return FALSE;
    memcpy(pbTemp, pbSrc, min(dwDataLen, 2*dwKeyLen+5*((dwKeyLen+1)>>1)));
    pbBigNum = pbTemp;

    pKeyContext->rsa.type = PK_PRIVATE;
    reverse_bytes(pbBigNum, dwKeyLen);
    mp_read_unsigned_bin(&pKeyContext->rsa.N, pbBigNum, dwKeyLen);
    pbBigNum += dwKeyLen;
    reverse_bytes(pbBigNum, (dwKeyLen+1)>>1);
    mp_read_unsigned_bin(&pKeyContext->rsa.p, pbBigNum, (dwKeyLen+1)>>1);
    pbBigNum += (dwKeyLen+1)>>1;
    reverse_bytes(pbBigNum, (dwKeyLen+1)>>1);
    mp_read_unsigned_bin(&pKeyContext->rsa.q, pbBigNum, (dwKeyLen+1)>>1);
    pbBigNum += (dwKeyLen+1)>>1;
    reverse_bytes(pbBigNum, (dwKeyLen+1)>>1);
    mp_read_unsigned_bin(&pKeyContext->rsa.dP, pbBigNum, (dwKeyLen+1)>>1);
    pbBigNum += (dwKeyLen+1)>>1;
    reverse_bytes(pbBigNum, (dwKeyLen+1)>>1);
    mp_read_unsigned_bin(&pKeyContext->rsa.dQ, pbBigNum, (dwKeyLen+1)>>1);
    pbBigNum += (dwKeyLen+1)>>1;
    reverse_bytes(pbBigNum, (dwKeyLen+1)>>1);
    mp_read_unsigned_bin(&pKeyContext->rsa.qP, pbBigNum, (dwKeyLen+1)>>1);
    pbBigNum += (dwKeyLen+1)>>1;
    /* The size of the private exponent d is inferred from the remaining
     * data length.
     */
    dwKeyLen = min(dwKeyLen, dwDataLen - (pbBigNum - pbTemp));
    reverse_bytes(pbBigNum, dwKeyLen);
    mp_read_unsigned_bin(&pKeyContext->rsa.d, pbBigNum, dwKeyLen);
    mp_set_int(&pKeyContext->rsa.e, dwPubExp);
    
    HeapFree(GetProcessHeap(), 0, pbTemp);
    return TRUE;
}