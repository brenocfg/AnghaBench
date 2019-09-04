#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  digest; } ;
typedef  int /*<<< orphan*/  SECURITY_STATUS ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  TYPE_1__ MD4_CTX ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  MD4Final (TYPE_1__*) ; 
 int /*<<< orphan*/  MD4Init (TYPE_1__*) ; 
 int /*<<< orphan*/  MD4Update (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SEC_E_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

SECURITY_STATUS SECUR32_CreateNTLM1SessionKey(PBYTE password, int len, PBYTE session_key)
{
    MD4_CTX ctx;
    BYTE ntlm_hash[16];

    TRACE("(%p, %p)\n", password, session_key);

    MD4Init(&ctx);
    MD4Update(&ctx, password, len);
    MD4Final(&ctx);

    memcpy(ntlm_hash, ctx.digest, 0x10);

    MD4Init(&ctx);
    MD4Update(&ctx, ntlm_hash, 0x10u);
    MD4Final(&ctx);

    memcpy(session_key, ctx.digest, 0x10);

    return SEC_E_OK;
}