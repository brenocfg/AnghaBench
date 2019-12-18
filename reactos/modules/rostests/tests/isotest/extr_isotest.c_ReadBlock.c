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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {scalar_t__ Status; int /*<<< orphan*/  Information; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  int /*<<< orphan*/  PLARGE_INTEGER ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_1__ IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_ALL_ACCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (scalar_t__) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 scalar_t__ NtCreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NtReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NtWaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ STATUS_END_OF_FILE ; 
 scalar_t__ STATUS_PENDING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  printf (char*,...) ; 

BOOL
ReadBlock(HANDLE FileHandle,
	  PVOID Buffer,
	  PLARGE_INTEGER Offset,
	  ULONG Length,
	  PULONG BytesRead)
{
  IO_STATUS_BLOCK IoStatusBlock;
  OBJECT_ATTRIBUTES ObjectAttributes;
  NTSTATUS Status;
  HANDLE EventHandle;

  InitializeObjectAttributes(&ObjectAttributes,
			     NULL, 0, NULL, NULL);

  Status = NtCreateEvent(&EventHandle,
			 EVENT_ALL_ACCESS,
			 &ObjectAttributes,
			 TRUE,
			 FALSE);
  if (!NT_SUCCESS(Status))
    {
      printf("NtCreateEvent() failed\n");
      return(FALSE);
    }

  Status = NtReadFile(FileHandle,
		      EventHandle,
		      NULL,
		      NULL,
		      &IoStatusBlock,
		      Buffer,
		      Length,
		      Offset,
		      NULL);
  if (Status == STATUS_PENDING)
    {
      NtWaitForSingleObject(EventHandle, FALSE, NULL);
      Status = IoStatusBlock.Status;
    }

  NtClose(EventHandle);

  if (Status != STATUS_PENDING && BytesRead != NULL)
    {
      *BytesRead = IoStatusBlock.Information;
    }
  if (!NT_SUCCESS(Status) && Status != STATUS_END_OF_FILE)
    {
      printf("ReadBlock() failed (Status: %lx)\n", Status);
      return(FALSE);
    }

  return(TRUE);
}