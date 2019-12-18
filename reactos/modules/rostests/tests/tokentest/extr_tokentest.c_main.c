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
typedef  int NTSTATUS ;
typedef  int HANDLE ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int) ; 
 int CreateInitialSystemToken (int*) ; 
 int /*<<< orphan*/  DisplayToken (int) ; 
 int /*<<< orphan*/  EnablePrivilege (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ NT_SUCCESS (int) ; 
 int /*<<< orphan*/  SE_CREATE_TOKEN_NAME ; 
 int TOKEN_QUERY ; 
 int TOKEN_QUERY_SOURCE ; 
 int ZwOpenProcessToken (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  gets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
main(int argc, char* argv[])
{
	NTSTATUS Status;
	HANDLE hSystemToken;
	CHAR buffer[512];
	HANDLE hOurToken;

        printf("Current process Token:\n");

        Status=ZwOpenProcessToken(GetCurrentProcess(), TOKEN_QUERY|TOKEN_QUERY_SOURCE, &hOurToken);
	if ( NT_SUCCESS(Status) )
	{
	  DisplayToken(hOurToken);
	  CloseHandle(hOurToken);
	}
	else
	{
	  printf("ZwOpenProcessToken() failed: 0x%08x\n", Status);
	}

//#define ENABLE_PRIVILEGE
#ifdef ENABLE_PRIVILEGE
    EnablePrivilege(SE_CREATE_TOKEN_NAME);
#endif

	// Now do the other one
	Status = CreateInitialSystemToken(&hSystemToken);
	if ( NT_SUCCESS(Status) )
	{
		printf("System Token: 0x%08x\n", hSystemToken);
		DisplayToken(hSystemToken);
		CloseHandle(hSystemToken);
	}
	else
	{
		printf("CreateInitialSystemToken() return: 0x%08x\n", Status);
	}

	printf("press return");
	gets(buffer);

	return 0;
}