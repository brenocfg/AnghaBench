#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_3__ {int Length; char* Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int /*<<< orphan*/  UNICODE_NULL ;
typedef  int NTSTATUS ;
typedef  char* LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  NT_SUCCESS (int) ; 
 int NtLoadDriver (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  wcslen (char*) ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 
 int /*<<< orphan*/  wsprintf (char*,char*,char*) ; 

int wmain(int argc, WCHAR * argv[])
{
   NTSTATUS Status;
   UNICODE_STRING ServiceName;

   if (argc != 2)
   {
      wprintf(L"Usage: load <ServiceName>\n");
      return 0;
   }
   ServiceName.Length = (wcslen(argv[1]) + 52) * sizeof(WCHAR);
   ServiceName.Buffer = (LPWSTR)malloc(ServiceName.Length + sizeof(UNICODE_NULL));
   wsprintf(ServiceName.Buffer,
      L"\\Registry\\Machine\\System\\CurrentControlSet\\Services\\%S",
      argv[1]);
   wprintf(L"%s %u %Id\n", ServiceName.Buffer, ServiceName.Length, wcslen(ServiceName.Buffer));
   Status = NtLoadDriver(&ServiceName);
   free(ServiceName.Buffer);
   if (!NT_SUCCESS(Status))
   {
      wprintf(L"Failed: %x\n", Status);
      return 1;
   }
   return 0;
}