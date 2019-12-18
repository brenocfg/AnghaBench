#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {scalar_t__ DataSize; scalar_t__ MessageSize; } ;
struct TYPE_6__ {TYPE_4__ Header; scalar_t__ Data; } ;
typedef  TYPE_1__ SECURITY_QUALITY_OF_SERVICE ;
typedef  int NTSTATUS ;
typedef  int /*<<< orphan*/  LPC_MESSAGE ;
typedef  TYPE_1__ LPC_MAX_MESSAGE ;
typedef  int HANDLE ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  GetCommandLineA () ; 
 char* MyName ; 
 int /*<<< orphan*/  NT_SUCCESS (int) ; 
 int /*<<< orphan*/  NtClose (int) ; 
 int NtConnectPort (int*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int NtRequestPort (int,TYPE_4__*) ; 
 int /*<<< orphan*/  ROS_STRING_INITIALIZER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 char* TEST_PORT_NAME ; 
 int /*<<< orphan*/  TEST_PORT_NAME_U ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  strcpy (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (scalar_t__) ; 

int main(int argc, char* argv[])
{
   UNICODE_STRING PortName = ROS_STRING_INITIALIZER(TEST_PORT_NAME_U);
   NTSTATUS Status;
   HANDLE PortHandle;
   LPC_MAX_MESSAGE Request;
   ULONG ConnectInfo;
   ULONG ConnectInfoLength = 0;
   SECURITY_QUALITY_OF_SERVICE Sqos;

   printf("%s: Lpc test client\n", MyName);

   printf("%s: Connecting to port \"%s\"...\n", MyName, TEST_PORT_NAME);
   ConnectInfoLength = 0;
   ZeroMemory (& Sqos, sizeof Sqos);
   Status = NtConnectPort(&PortHandle,
			  &PortName,
			  & Sqos,
			  0,
			  0,
			  0,
			  NULL,
			  &ConnectInfoLength);
   if (!NT_SUCCESS(Status))
     {
	printf("%s: NtConnectPort() failed with status = 0x%08X.\n", MyName, Status);
	return EXIT_FAILURE;
     }

   printf("%s: Connected to \"%s\" with anonymous port 0x%x.\n", MyName, TEST_PORT_NAME, PortHandle);

   ZeroMemory(& Request, sizeof Request);
   strcpy(Request.Data, GetCommandLineA());
   Request.Header.DataSize = strlen(Request.Data);
   Request.Header.MessageSize = sizeof(LPC_MESSAGE) +
     Request.Header.DataSize;

   printf("%s: Sending to port 0x%x message \"%s\"...\n",
          MyName,
          PortHandle,
	  (char *) Request.Data);
   Status = NtRequestPort(PortHandle,
			  &Request.Header);
   if (!NT_SUCCESS(Status))
     {
	printf("%s: NtRequestPort(0x%x) failed with status = 0x%8X.\n",
               MyName,
               PortHandle,
	       Status);
	return EXIT_FAILURE;
     }

   printf("%s: Sending datagram to port 0x%x succeeded.\n", MyName, PortHandle);

   Sleep(2000);

   printf("%s: Disconnecting...", MyName);
   NtClose (PortHandle);

   return EXIT_SUCCESS;
}