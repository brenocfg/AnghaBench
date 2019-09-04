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
typedef  scalar_t__ RPC_STATUS ;

/* Variables and functions */
 scalar_t__ RPC_S_UNKNOWN_AUTHN_SERVICE ; 
 scalar_t__ RpcServerRegisterAuthInfoW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_RpcServerRegisterAuthInfo(void)
{
    RPC_STATUS status;

    status = RpcServerRegisterAuthInfoW(NULL, 600, NULL, NULL);
    ok(status == RPC_S_UNKNOWN_AUTHN_SERVICE, "status = %x\n", status);
}