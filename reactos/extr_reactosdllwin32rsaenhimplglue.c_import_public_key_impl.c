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
struct TYPE_4__ {int /*<<< orphan*/  e; int /*<<< orphan*/  N; int /*<<< orphan*/  type; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  qP; int /*<<< orphan*/  dP; int /*<<< orphan*/  dQ; int /*<<< orphan*/  d; } ;
struct TYPE_5__ {TYPE_1__ rsa; } ;
typedef  TYPE_2__ KEY_CONTEXT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MP_OKAY ; 
 int /*<<< orphan*/  NTE_FAIL ; 
 int /*<<< orphan*/  PK_PUBLIC ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_init_multi (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_read_unsigned_bin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_set_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reverse_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOL import_public_key_impl(const BYTE *pbSrc, KEY_CONTEXT *pKeyContext, DWORD dwKeyLen,
                            DWORD dwPubExp)
{
    BYTE *pbTemp;

    if (mp_init_multi(&pKeyContext->rsa.e, &pKeyContext->rsa.d, &pKeyContext->rsa.N, 
                      &pKeyContext->rsa.dQ,&pKeyContext->rsa.dP,&pKeyContext->rsa.qP, 
                      &pKeyContext->rsa.p, &pKeyContext->rsa.q, NULL) != MP_OKAY)
    {
        SetLastError(NTE_FAIL);
        return FALSE;
    }

    pbTemp = HeapAlloc(GetProcessHeap(), 0, dwKeyLen);
    if (!pbTemp) return FALSE;
    memcpy(pbTemp, pbSrc, dwKeyLen);
    
    pKeyContext->rsa.type = PK_PUBLIC;
    reverse_bytes(pbTemp, dwKeyLen);
    mp_read_unsigned_bin(&pKeyContext->rsa.N, pbTemp, dwKeyLen);
    HeapFree(GetProcessHeap(), 0, pbTemp);
    mp_set_int(&pKeyContext->rsa.e, dwPubExp);

    return TRUE;    
}