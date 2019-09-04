#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dQ; int /*<<< orphan*/  dP; int /*<<< orphan*/  qP; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  N; int /*<<< orphan*/  d; int /*<<< orphan*/  e; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_1__ rsa; } ;
typedef  TYPE_2__ KEY_CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int ALG_ID ;

/* Variables and functions */
#define  CALG_3DES 138 
#define  CALG_3DES_112 137 
#define  CALG_AES 136 
#define  CALG_AES_128 135 
#define  CALG_AES_192 134 
#define  CALG_AES_256 133 
#define  CALG_DES 132 
#define  CALG_RC2 131 
#define  CALG_RC4 130 
#define  CALG_RSA_KEYX 129 
#define  CALG_RSA_SIGN 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NTE_BAD_ALGID ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mp_init_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL duplicate_key_impl(ALG_ID aiAlgid, const KEY_CONTEXT *pSrcKeyContext,
                        KEY_CONTEXT *pDestKeyContext) 
{
    switch (aiAlgid) 
    {
        case CALG_RC4:
        case CALG_RC2:
        case CALG_3DES:
        case CALG_3DES_112:
        case CALG_DES:
        case CALG_AES:
        case CALG_AES_128:
        case CALG_AES_192:
        case CALG_AES_256:
            *pDestKeyContext = *pSrcKeyContext;
            break;
        case CALG_RSA_KEYX:
        case CALG_RSA_SIGN:
            pDestKeyContext->rsa.type = pSrcKeyContext->rsa.type;
            mp_init_copy(&pDestKeyContext->rsa.e, &pSrcKeyContext->rsa.e);
            mp_init_copy(&pDestKeyContext->rsa.d, &pSrcKeyContext->rsa.d);
            mp_init_copy(&pDestKeyContext->rsa.N, &pSrcKeyContext->rsa.N);
            mp_init_copy(&pDestKeyContext->rsa.p, &pSrcKeyContext->rsa.p);
            mp_init_copy(&pDestKeyContext->rsa.q, &pSrcKeyContext->rsa.q);
            mp_init_copy(&pDestKeyContext->rsa.qP, &pSrcKeyContext->rsa.qP);
            mp_init_copy(&pDestKeyContext->rsa.dP, &pSrcKeyContext->rsa.dP);
            mp_init_copy(&pDestKeyContext->rsa.dQ, &pSrcKeyContext->rsa.dQ);
            break;
        
        default:
            SetLastError(NTE_BAD_ALGID);
            return FALSE;
    }

    return TRUE;
}