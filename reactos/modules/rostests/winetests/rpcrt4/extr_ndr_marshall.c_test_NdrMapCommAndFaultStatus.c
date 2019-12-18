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
typedef  scalar_t__ ULONG ;
typedef  int RPC_STATUS ;
typedef  int /*<<< orphan*/  RPC_MESSAGE ;
typedef  int /*<<< orphan*/  MIDL_STUB_MESSAGE ;

/* Variables and functions */
#define  EPT_S_NOT_REGISTERED 139 
#define  ERROR_INVALID_HANDLE 138 
 int /*<<< orphan*/  NdrClientInitializeNew (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int NdrMapCommAndFaultStatus (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  Object_StubDesc ; 
#define  RPC_S_CALL_FAILED_DNE 137 
#define  RPC_S_COMM_FAILURE 136 
#define  RPC_S_INVALID_BINDING 135 
 int RPC_S_OK ; 
#define  RPC_S_PROCNUM_OUT_OF_RANGE 134 
#define  RPC_S_PROTOCOL_ERROR 133 
#define  RPC_S_SERVER_TOO_BUSY 132 
#define  RPC_S_SERVER_UNAVAILABLE 131 
#define  RPC_S_UNKNOWN_IF 130 
#define  RPC_S_UNSUPPORTED_TRANS_SYN 129 
#define  RPC_S_UNSUPPORTED_TYPE 128 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void test_NdrMapCommAndFaultStatus(void)
{
    RPC_STATUS rpc_status;
    MIDL_STUB_MESSAGE StubMsg;
    RPC_MESSAGE RpcMessage;

    NdrClientInitializeNew(&RpcMessage, &StubMsg, &Object_StubDesc, 5);

    for (rpc_status = 0; rpc_status < 10000; rpc_status++)
    {
        RPC_STATUS status;
        ULONG comm_status = 0;
        ULONG fault_status = 0;
        ULONG expected_comm_status = 0;
        ULONG expected_fault_status = 0;
        status = NdrMapCommAndFaultStatus(&StubMsg, &comm_status, &fault_status, rpc_status);
        ok(status == RPC_S_OK, "NdrMapCommAndFaultStatus failed with error %d\n", status);
        switch (rpc_status)
        {
        case ERROR_INVALID_HANDLE:
        case RPC_S_INVALID_BINDING:
        case RPC_S_UNKNOWN_IF:
        case RPC_S_SERVER_UNAVAILABLE:
        case RPC_S_SERVER_TOO_BUSY:
        case RPC_S_CALL_FAILED_DNE:
        case RPC_S_PROTOCOL_ERROR:
        case RPC_S_UNSUPPORTED_TRANS_SYN:
        case RPC_S_UNSUPPORTED_TYPE:
        case RPC_S_PROCNUM_OUT_OF_RANGE:
        case EPT_S_NOT_REGISTERED:
        case RPC_S_COMM_FAILURE:
            expected_comm_status = rpc_status;
            break;
        default:
            expected_fault_status = rpc_status;
        }
        ok(comm_status == expected_comm_status, "NdrMapCommAndFaultStatus should have mapped %d to comm status %d instead of %d\n",
            rpc_status, expected_comm_status, comm_status);
        ok(fault_status == expected_fault_status, "NdrMapCommAndFaultStatus should have mapped %d to fault status %d instead of %d\n",
            rpc_status, expected_fault_status, fault_status);
    }
}