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

/* Variables and functions */
 int /*<<< orphan*/  test_pack_ARRAY_INFO () ; 
 int /*<<< orphan*/  test_pack_COMM_FAULT_OFFSETS () ; 
 int /*<<< orphan*/  test_pack_CS_STUB_INFO () ; 
 int /*<<< orphan*/  test_pack_EXPR_EVAL () ; 
 int /*<<< orphan*/  test_pack_FULL_PTR_TO_REFID_ELEMENT () ; 
 int /*<<< orphan*/  test_pack_FULL_PTR_XLAT_TABLES () ; 
 int /*<<< orphan*/  test_pack_GENERIC_BINDING_INFO () ; 
 int /*<<< orphan*/  test_pack_GENERIC_BINDING_ROUTINE_PAIR () ; 
 int /*<<< orphan*/  test_pack_I_RPC_HANDLE () ; 
 int /*<<< orphan*/  test_pack_MALLOC_FREE_STRUCT () ; 
 int /*<<< orphan*/  test_pack_MIDL_FORMAT_STRING () ; 
 int /*<<< orphan*/  test_pack_MIDL_SERVER_INFO () ; 
 int /*<<< orphan*/  test_pack_MIDL_STUBLESS_PROXY_INFO () ; 
 int /*<<< orphan*/  test_pack_MIDL_STUB_DESC () ; 
 int /*<<< orphan*/  test_pack_MIDL_STUB_MESSAGE () ; 
 int /*<<< orphan*/  test_pack_MIDL_SYNTAX_INFO () ; 
 int /*<<< orphan*/  test_pack_NDR_CCONTEXT () ; 
 int /*<<< orphan*/  test_pack_NDR_NOTIFY2_ROUTINE () ; 
 int /*<<< orphan*/  test_pack_NDR_NOTIFY_ROUTINE () ; 
 int /*<<< orphan*/  test_pack_NDR_RUNDOWN () ; 
 int /*<<< orphan*/  test_pack_NDR_SCONTEXT () ; 
 int /*<<< orphan*/  test_pack_NDR_USER_MARSHAL_INFO () ; 
 int /*<<< orphan*/  test_pack_NDR_USER_MARSHAL_INFO_LEVEL1 () ; 
 int /*<<< orphan*/  test_pack_PARRAY_INFO () ; 
 int /*<<< orphan*/  test_pack_PFORMAT_STRING () ; 
 int /*<<< orphan*/  test_pack_PFULL_PTR_TO_REFID_ELEMENT () ; 
 int /*<<< orphan*/  test_pack_PFULL_PTR_XLAT_TABLES () ; 
 int /*<<< orphan*/  test_pack_PGENERIC_BINDING_INFO () ; 
 int /*<<< orphan*/  test_pack_PGENERIC_BINDING_ROUTINE_PAIR () ; 
 int /*<<< orphan*/  test_pack_PMIDL_SERVER_INFO () ; 
 int /*<<< orphan*/  test_pack_PMIDL_STUBLESS_PROXY_INFO () ; 
 int /*<<< orphan*/  test_pack_PMIDL_STUB_DESC () ; 
 int /*<<< orphan*/  test_pack_PMIDL_STUB_MESSAGE () ; 
 int /*<<< orphan*/  test_pack_PMIDL_SYNTAX_INFO () ; 
 int /*<<< orphan*/  test_pack_PNDR_ASYNC_MESSAGE () ; 
 int /*<<< orphan*/  test_pack_PNDR_CORRELATION_INFO () ; 
 int /*<<< orphan*/  test_pack_PRPC_CLIENT_INTERFACE () ; 
 int /*<<< orphan*/  test_pack_PRPC_DISPATCH_TABLE () ; 
 int /*<<< orphan*/  test_pack_PRPC_MESSAGE () ; 
 int /*<<< orphan*/  test_pack_PRPC_POLICY () ; 
 int /*<<< orphan*/  test_pack_PRPC_PROTSEQ_ENDPOINT () ; 
 int /*<<< orphan*/  test_pack_PRPC_SERVER_INTERFACE () ; 
 int /*<<< orphan*/  test_pack_PRPC_STUB_FUNCTION () ; 
 int /*<<< orphan*/  test_pack_PRPC_SYNTAX_IDENTIFIER () ; 
 int /*<<< orphan*/  test_pack_PSCONTEXT_QUEUE () ; 
 int /*<<< orphan*/  test_pack_PXMIT_ROUTINE_QUINTUPLE () ; 
 int /*<<< orphan*/  test_pack_RPC_AUTHZ_HANDLE () ; 
 int /*<<< orphan*/  test_pack_RPC_AUTH_IDENTITY_HANDLE () ; 
 int /*<<< orphan*/  test_pack_RPC_AUTH_KEY_RETRIEVAL_FN () ; 
 int /*<<< orphan*/  test_pack_RPC_BINDING_HANDLE () ; 
 int /*<<< orphan*/  test_pack_RPC_BINDING_VECTOR () ; 
 int /*<<< orphan*/  test_pack_RPC_CLIENT_INTERFACE () ; 
 int /*<<< orphan*/  test_pack_RPC_DISPATCH_FUNCTION () ; 
 int /*<<< orphan*/  test_pack_RPC_DISPATCH_TABLE () ; 
 int /*<<< orphan*/  test_pack_RPC_IF_HANDLE () ; 
 int /*<<< orphan*/  test_pack_RPC_IF_ID () ; 
 int /*<<< orphan*/  test_pack_RPC_MESSAGE () ; 
 int /*<<< orphan*/  test_pack_RPC_POLICY () ; 
 int /*<<< orphan*/  test_pack_RPC_PROTSEQ_ENDPOINT () ; 
 int /*<<< orphan*/  test_pack_RPC_SERVER_INTERFACE () ; 
 int /*<<< orphan*/  test_pack_RPC_STATUS () ; 
 int /*<<< orphan*/  test_pack_RPC_SYNTAX_IDENTIFIER () ; 
 int /*<<< orphan*/  test_pack_RPC_VERSION () ; 
 int /*<<< orphan*/  test_pack_SCONTEXT_QUEUE () ; 
 int /*<<< orphan*/  test_pack_SERVER_ROUTINE () ; 
 int /*<<< orphan*/  test_pack_STUB_THUNK () ; 
 int /*<<< orphan*/  test_pack_USER_MARSHAL_CB () ; 
 int /*<<< orphan*/  test_pack_USER_MARSHAL_FREEING_ROUTINE () ; 
 int /*<<< orphan*/  test_pack_USER_MARSHAL_MARSHALLING_ROUTINE () ; 
 int /*<<< orphan*/  test_pack_USER_MARSHAL_ROUTINE_QUADRUPLE () ; 
 int /*<<< orphan*/  test_pack_USER_MARSHAL_SIZING_ROUTINE () ; 
 int /*<<< orphan*/  test_pack_USER_MARSHAL_UNMARSHALLING_ROUTINE () ; 
 int /*<<< orphan*/  test_pack_UUID_VECTOR () ; 
 int /*<<< orphan*/  test_pack_XMIT_HELPER_ROUTINE () ; 
 int /*<<< orphan*/  test_pack_XMIT_ROUTINE_QUINTUPLE () ; 

__attribute__((used)) static void test_pack(void)
{
    test_pack_ARRAY_INFO();
    test_pack_COMM_FAULT_OFFSETS();
    test_pack_CS_STUB_INFO();
    test_pack_EXPR_EVAL();
    test_pack_FULL_PTR_TO_REFID_ELEMENT();
    test_pack_FULL_PTR_XLAT_TABLES();
    test_pack_GENERIC_BINDING_INFO();
    test_pack_GENERIC_BINDING_ROUTINE_PAIR();
    test_pack_I_RPC_HANDLE();
    test_pack_MALLOC_FREE_STRUCT();
    test_pack_MIDL_FORMAT_STRING();
    test_pack_MIDL_SERVER_INFO();
    test_pack_MIDL_STUBLESS_PROXY_INFO();
    test_pack_MIDL_STUB_DESC();
    test_pack_MIDL_STUB_MESSAGE();
    test_pack_MIDL_SYNTAX_INFO();
    test_pack_NDR_CCONTEXT();
    test_pack_NDR_NOTIFY2_ROUTINE();
    test_pack_NDR_NOTIFY_ROUTINE();
    test_pack_NDR_RUNDOWN();
    test_pack_NDR_SCONTEXT();
    test_pack_NDR_USER_MARSHAL_INFO();
    test_pack_NDR_USER_MARSHAL_INFO_LEVEL1();
    test_pack_PARRAY_INFO();
    test_pack_PFORMAT_STRING();
    test_pack_PFULL_PTR_TO_REFID_ELEMENT();
    test_pack_PFULL_PTR_XLAT_TABLES();
    test_pack_PGENERIC_BINDING_INFO();
    test_pack_PGENERIC_BINDING_ROUTINE_PAIR();
    test_pack_PMIDL_SERVER_INFO();
    test_pack_PMIDL_STUBLESS_PROXY_INFO();
    test_pack_PMIDL_STUB_DESC();
    test_pack_PMIDL_STUB_MESSAGE();
    test_pack_PMIDL_SYNTAX_INFO();
    test_pack_PNDR_ASYNC_MESSAGE();
    test_pack_PNDR_CORRELATION_INFO();
    test_pack_PRPC_CLIENT_INTERFACE();
    test_pack_PRPC_DISPATCH_TABLE();
    test_pack_PRPC_MESSAGE();
    test_pack_PRPC_POLICY();
    test_pack_PRPC_PROTSEQ_ENDPOINT();
    test_pack_PRPC_SERVER_INTERFACE();
    test_pack_PRPC_STUB_FUNCTION();
    test_pack_PRPC_SYNTAX_IDENTIFIER();
    test_pack_PSCONTEXT_QUEUE();
    test_pack_PXMIT_ROUTINE_QUINTUPLE();
    test_pack_RPC_AUTHZ_HANDLE();
    test_pack_RPC_AUTH_IDENTITY_HANDLE();
    test_pack_RPC_AUTH_KEY_RETRIEVAL_FN();
    test_pack_RPC_BINDING_HANDLE();
    test_pack_RPC_BINDING_VECTOR();
    test_pack_RPC_CLIENT_INTERFACE();
    test_pack_RPC_DISPATCH_FUNCTION();
    test_pack_RPC_DISPATCH_TABLE();
    test_pack_RPC_IF_HANDLE();
    test_pack_RPC_IF_ID();
    test_pack_RPC_MESSAGE();
    test_pack_RPC_POLICY();
    test_pack_RPC_PROTSEQ_ENDPOINT();
    test_pack_RPC_SERVER_INTERFACE();
    test_pack_RPC_STATUS();
    test_pack_RPC_SYNTAX_IDENTIFIER();
    test_pack_RPC_VERSION();
    test_pack_SCONTEXT_QUEUE();
    test_pack_SERVER_ROUTINE();
    test_pack_STUB_THUNK();
    test_pack_USER_MARSHAL_CB();
    test_pack_USER_MARSHAL_FREEING_ROUTINE();
    test_pack_USER_MARSHAL_MARSHALLING_ROUTINE();
    test_pack_USER_MARSHAL_ROUTINE_QUADRUPLE();
    test_pack_USER_MARSHAL_SIZING_ROUTINE();
    test_pack_USER_MARSHAL_UNMARSHALLING_ROUTINE();
    test_pack_UUID_VECTOR();
    test_pack_XMIT_HELPER_ROUTINE();
    test_pack_XMIT_ROUTINE_QUINTUPLE();
}