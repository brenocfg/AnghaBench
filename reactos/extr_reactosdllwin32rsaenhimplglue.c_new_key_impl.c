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
struct TYPE_3__ {int /*<<< orphan*/  rsa; } ;
typedef  TYPE_1__ KEY_CONTEXT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int ALG_ID ;

/* Variables and functions */
#define  CALG_RSA_KEYX 129 
#define  CALG_RSA_SIGN 128 
 int /*<<< orphan*/  CRYPT_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NTE_FAIL ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  rsa_make_key (int,int,int /*<<< orphan*/ *) ; 

BOOL new_key_impl(ALG_ID aiAlgid, KEY_CONTEXT *pKeyContext, DWORD dwKeyLen) 
{
    switch (aiAlgid)
    {
        case CALG_RSA_KEYX:
        case CALG_RSA_SIGN:
            if (rsa_make_key((int)dwKeyLen, 65537, &pKeyContext->rsa) != CRYPT_OK) {
                SetLastError(NTE_FAIL);
                return FALSE;
            }
            return TRUE;
    }

    return TRUE;
}