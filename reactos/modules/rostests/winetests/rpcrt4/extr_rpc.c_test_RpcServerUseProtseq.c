#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ULONG ;
struct TYPE_4__ {size_t Count; int /*<<< orphan*/ * BindingH; } ;
typedef  scalar_t__ RPC_STATUS ;
typedef  scalar_t__ RPC_CSTR ;
typedef  TYPE_1__ RPC_BINDING_VECTOR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ RPC_S_INVALID_ENDPOINT_FORMAT ; 
 scalar_t__ RPC_S_NO_BINDINGS ; 
 scalar_t__ RPC_S_OK ; 
 scalar_t__ RPC_S_PROTSEQ_NOT_SUPPORTED ; 
 scalar_t__ RpcBindingToStringBindingA (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  RpcBindingVectorFree (TYPE_1__**) ; 
 scalar_t__ RpcServerInqBindings (TYPE_1__**) ; 
 scalar_t__ RpcServerUseProtseqA (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RpcServerUseProtseqEpA (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcStringFreeA (scalar_t__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ broken (int) ; 
 int lstrlenA (char const*) ; 
 int /*<<< orphan*/  memcmp (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,size_t,...) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RpcServerUseProtseq(void)
{
    RPC_STATUS status;
    RPC_BINDING_VECTOR *bindings;
    ULONG i;
    ULONG binding_count_before;
    ULONG binding_count_after1;
    ULONG binding_count_after2;
    ULONG endpoints_registered = 0;
    static unsigned char iptcp[] = "ncacn_ip_tcp";
    static unsigned char np[] = "ncacn_np";
    static unsigned char ncalrpc[] = "ncalrpc";
    BOOL iptcp_registered = FALSE, np_registered = FALSE, ncalrpc_registered = FALSE;

    status = RpcServerInqBindings(&bindings);
    if (status == RPC_S_NO_BINDINGS)
        binding_count_before = 0;
    else
    {
        binding_count_before = bindings->Count;
        ok(status == RPC_S_OK, "RpcServerInqBindings failed with status %d\n", status);
        for (i = 0; i < bindings->Count; i++)
        {
            RPC_CSTR str_bind;
            status = RpcBindingToStringBindingA(bindings->BindingH[i], &str_bind);
            ok(status == RPC_S_OK, "RpcBindingToStringBinding failed with status %d\n", status);
            if (lstrlenA((const char *)str_bind) > 12 && !memcmp(str_bind, "ncacn_ip_tcp", 12))
                iptcp_registered = TRUE;
            if (lstrlenA((const char *)str_bind) > 8 && !memcmp(str_bind, "ncacn_np", 8))
                np_registered = TRUE;
            if (lstrlenA((const char *)str_bind) > 7 && !memcmp(str_bind, "ncalrpc", 7))
                ncalrpc_registered = TRUE;
            RpcStringFreeA(&str_bind);
        }
        RpcBindingVectorFree(&bindings);
    }

    /* show that RpcServerUseProtseqEp(..., NULL, ...) is the same as
     * RpcServerUseProtseq(...) */
    status = RpcServerUseProtseqEpA(ncalrpc, 0, NULL, NULL);
    ok(status == RPC_S_OK || broken(status == RPC_S_INVALID_ENDPOINT_FORMAT),
       "RpcServerUseProtseqEp with NULL endpoint failed with status %d\n",
       status);

    /* register protocol sequences without explicit endpoints */
    status = RpcServerUseProtseqA(np, 0, NULL);
    if (status == RPC_S_PROTSEQ_NOT_SUPPORTED)
        win_skip("ncacn_np not supported\n");
    else
        ok(status == RPC_S_OK, "RpcServerUseProtseq(ncacn_np) failed with status %d\n", status);
    if (status == RPC_S_OK && !np_registered) endpoints_registered++;

    status = RpcServerUseProtseqA(iptcp, 0, NULL);
    ok(status == RPC_S_OK, "RpcServerUseProtseq(ncacn_ip_tcp) failed with status %d\n", status);
    if (status == RPC_S_OK && !iptcp_registered) endpoints_registered++;

    status = RpcServerUseProtseqA(ncalrpc, 0, NULL);
    ok(status == RPC_S_OK, "RpcServerUseProtseqEp(ncalrpc) failed with status %d\n", status);
    if (status == RPC_S_OK && !ncalrpc_registered) endpoints_registered++;

    status = RpcServerInqBindings(&bindings);
    ok(status == RPC_S_OK, "RpcServerInqBindings failed with status %d\n", status);
    binding_count_after1 = bindings->Count;
    ok(binding_count_after1 == binding_count_before + endpoints_registered,
       "wrong binding count - before: %u, after %u, endpoints registered %u\n",
       binding_count_before, binding_count_after1, endpoints_registered);
    for (i = 0; i < bindings->Count; i++)
    {
        RPC_CSTR str_bind;
        status = RpcBindingToStringBindingA(bindings->BindingH[i], &str_bind);
        ok(status == RPC_S_OK, "RpcBindingToStringBinding failed with status %d\n", status);
        trace("string binding: %s\n", str_bind);
        RpcStringFreeA(&str_bind);
    }
    RpcBindingVectorFree(&bindings);

    /* re-register - endpoints should be reused */
    status = RpcServerUseProtseqA(np, 0, NULL);
    if (status == RPC_S_PROTSEQ_NOT_SUPPORTED)
        win_skip("ncacn_np not supported\n");
    else
        ok(status == RPC_S_OK, "RpcServerUseProtseq(ncacn_np) failed with status %d\n", status);

    status = RpcServerUseProtseqA(iptcp, 0, NULL);
    ok(status == RPC_S_OK, "RpcServerUseProtseq(ncacn_ip_tcp) failed with status %d\n", status);

    status = RpcServerUseProtseqA(ncalrpc, 0, NULL);
    ok(status == RPC_S_OK, "RpcServerUseProtseqEp(ncalrpc) failed with status %d\n", status);

    status = RpcServerInqBindings(&bindings);
    ok(status == RPC_S_OK, "RpcServerInqBindings failed with status %d\n", status);
    binding_count_after2 = bindings->Count;
    ok(binding_count_after2 == binding_count_after1,
       "bindings should have been re-used - after1: %u after2: %u\n",
       binding_count_after1, binding_count_after2);
    RpcBindingVectorFree(&bindings);
}