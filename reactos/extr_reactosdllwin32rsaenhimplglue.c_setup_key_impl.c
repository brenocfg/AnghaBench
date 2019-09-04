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
struct TYPE_3__ {int /*<<< orphan*/  aes; int /*<<< orphan*/  des; int /*<<< orphan*/  des3; int /*<<< orphan*/  rc2; int /*<<< orphan*/  rc4; } ;
typedef  TYPE_1__ KEY_CONTEXT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int ALG_ID ;

/* Variables and functions */
#define  CALG_3DES 136 
#define  CALG_3DES_112 135 
#define  CALG_AES 134 
#define  CALG_AES_128 133 
#define  CALG_AES_192 132 
#define  CALG_AES_256 131 
#define  CALG_DES 130 
#define  CALG_RC2 129 
#define  CALG_RC4 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  aes_setup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  des3_setup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  des_setup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rc2_setup (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc4_add_entropy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc4_ready (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc4_start (int /*<<< orphan*/ *) ; 

BOOL setup_key_impl(ALG_ID aiAlgid, KEY_CONTEXT *pKeyContext, DWORD dwKeyLen,
                    DWORD dwEffectiveKeyLen, DWORD dwSaltLen, BYTE *abKeyValue)
{
    switch (aiAlgid) 
    {
        case CALG_RC4:
            rc4_start(&pKeyContext->rc4);
            rc4_add_entropy(abKeyValue, dwKeyLen + dwSaltLen, &pKeyContext->rc4);
            rc4_ready(&pKeyContext->rc4);
            break;
        
        case CALG_RC2:
            rc2_setup(abKeyValue, dwKeyLen + dwSaltLen, dwEffectiveKeyLen ?
                      dwEffectiveKeyLen : dwKeyLen << 3, 0, &pKeyContext->rc2);
            break;
        
        case CALG_3DES:
            des3_setup(abKeyValue, 24, 0, &pKeyContext->des3);
            break;

        case CALG_3DES_112:
            memcpy(abKeyValue+16, abKeyValue, 8);
            des3_setup(abKeyValue, 24, 0, &pKeyContext->des3);
            break;
        
        case CALG_DES:
            des_setup(abKeyValue, 8, 0, &pKeyContext->des);
            break;

        case CALG_AES:
        case CALG_AES_128:
            aes_setup(abKeyValue, 16, 0, &pKeyContext->aes);
            break;

        case CALG_AES_192:
            aes_setup(abKeyValue, 24, 0, &pKeyContext->aes);
            break;

        case CALG_AES_256:
            aes_setup(abKeyValue, 32, 0, &pKeyContext->aes);
            break;
    }

    return TRUE;
}