#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* recv_seal_key; void* recv_sign_key; void* send_seal_key; void* send_sign_key; } ;
struct TYPE_6__ {TYPE_1__ ntlm2; } ;
struct TYPE_7__ {scalar_t__ mode; TYPE_2__ crypt; int /*<<< orphan*/  session_key; } ;
typedef  int /*<<< orphan*/  SECURITY_STATUS ;
typedef  TYPE_3__* PNegoHelper ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NTLM_CLIENT ; 
 int /*<<< orphan*/  SECUR32_CalcNTLM2Subkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  SEC_E_OK ; 
 int /*<<< orphan*/  client_to_server_seal_constant ; 
 int /*<<< orphan*/  client_to_server_sign_constant ; 
 int /*<<< orphan*/  server_to_client_seal_constant ; 
 int /*<<< orphan*/  server_to_client_sign_constant ; 

SECURITY_STATUS SECUR32_CreateNTLM2SubKeys(PNegoHelper helper)
{
    helper->crypt.ntlm2.send_sign_key = HeapAlloc(GetProcessHeap(), 0, 16);
    helper->crypt.ntlm2.send_seal_key = HeapAlloc(GetProcessHeap(), 0, 16);
    helper->crypt.ntlm2.recv_sign_key = HeapAlloc(GetProcessHeap(), 0, 16);
    helper->crypt.ntlm2.recv_seal_key = HeapAlloc(GetProcessHeap(), 0, 16);

    if(helper->mode == NTLM_CLIENT)
    {
        SECUR32_CalcNTLM2Subkey(helper->session_key, client_to_server_sign_constant,
                helper->crypt.ntlm2.send_sign_key);
        SECUR32_CalcNTLM2Subkey(helper->session_key, client_to_server_seal_constant,
                helper->crypt.ntlm2.send_seal_key);
        SECUR32_CalcNTLM2Subkey(helper->session_key, server_to_client_sign_constant,
                helper->crypt.ntlm2.recv_sign_key);
        SECUR32_CalcNTLM2Subkey(helper->session_key, server_to_client_seal_constant,
                helper->crypt.ntlm2.recv_seal_key);
    }
    else
    {
        SECUR32_CalcNTLM2Subkey(helper->session_key, server_to_client_sign_constant,
                helper->crypt.ntlm2.send_sign_key);
        SECUR32_CalcNTLM2Subkey(helper->session_key, server_to_client_seal_constant,
                helper->crypt.ntlm2.send_seal_key);
        SECUR32_CalcNTLM2Subkey(helper->session_key, client_to_server_sign_constant,
                helper->crypt.ntlm2.recv_sign_key);
        SECUR32_CalcNTLM2Subkey(helper->session_key, client_to_server_seal_constant,
                helper->crypt.ntlm2.recv_seal_key);
    }

    return SEC_E_OK;
}