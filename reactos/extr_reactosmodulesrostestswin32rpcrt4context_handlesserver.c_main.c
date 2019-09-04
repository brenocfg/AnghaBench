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

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int RpcServerListen (int,int,int /*<<< orphan*/ ) ; 
 int RpcServerRegisterIf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int RpcServerUseProtseqEp (char*,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  hello_v1_0_s_ifspec ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  scanf (char*,int*) ; 

void main()
{
	RPC_STATUS status;
	unsigned int    cMinCalls      = 1;
	unsigned int    cMaxCalls      = 20;
	int i;

	status = RpcServerUseProtseqEp("ncacn_np", 20, "\\pipe\\hello", NULL);

	if (status)
	{
		printf("RpcServerUseProtseqEp %x\n", status);
		exit(status);
	}

	status = RpcServerRegisterIf(hello_v1_0_s_ifspec, NULL, NULL);

	if (status)
	{
		printf("RpcServerRegisterIf %x\n", status);
	exit(status);
	}

	status = RpcServerListen(1, 20, FALSE);

	if (status)
	{
		printf("RpcServerListen %x", status);
		exit(status);
	}

	scanf("%d", &i);
}