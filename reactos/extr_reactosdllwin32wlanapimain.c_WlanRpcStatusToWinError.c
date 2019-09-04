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
typedef  int RPC_STATUS ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_ADDRESS ; 
 int /*<<< orphan*/  ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
#define  RPC_S_INVALID_BINDING 132 
#define  RPC_X_BYTE_COUNT_TOO_SMALL 131 
#define  RPC_X_ENUM_VALUE_OUT_OF_RANGE 130 
#define  RPC_X_NULL_REF_POINTER 129 
#define  RPC_X_SS_IN_NULL_CONTEXT 128 

DWORD
WlanRpcStatusToWinError(RPC_STATUS Status)
{
    switch (Status)
    {
        case RPC_S_INVALID_BINDING:
        case RPC_X_SS_IN_NULL_CONTEXT:
            return ERROR_INVALID_HANDLE;

        case RPC_X_ENUM_VALUE_OUT_OF_RANGE:
        case RPC_X_BYTE_COUNT_TOO_SMALL:
            return ERROR_INVALID_PARAMETER;

        case RPC_X_NULL_REF_POINTER:
            return ERROR_INVALID_ADDRESS;

        default:
            return (DWORD)Status;
    }
}