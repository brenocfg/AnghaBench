#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
typedef  int UINT ;
struct TYPE_5__ {int Length; int /*<<< orphan*/ * Buffer; } ;
typedef  int /*<<< orphan*/ * PWCHAR ;
typedef  TYPE_1__* PUNICODE_STRING ;
typedef  int /*<<< orphan*/  PINFCACHE ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  IO_STATUS_BLOCK ;
typedef  int /*<<< orphan*/  INFSTATUS ;
typedef  scalar_t__ HINF ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 int FILE_NON_DIRECTORY_FILE ; 
 int FILE_SYNCHRONOUS_IO_NONALERT ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  INF_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfpBuildFileBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MALLOC (int) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtOpenFile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NtWriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int SYNCHRONIZE ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,char*) ; 

NTSTATUS
InfWriteFile(HINF InfHandle,
             PUNICODE_STRING FileName,
             PUNICODE_STRING HeaderComment)
{
  OBJECT_ATTRIBUTES ObjectAttributes;
  IO_STATUS_BLOCK IoStatusBlock;
  HANDLE FileHandle;
  NTSTATUS Status;
  INFSTATUS InfStatus;
  PWCHAR Buffer;
  ULONG BufferSize;
  PWCHAR HeaderBuffer;
  ULONG HeaderBufferSize;
  UINT Index;

  InfStatus = InfpBuildFileBuffer((PINFCACHE) InfHandle, &Buffer, &BufferSize);
  if (! INF_SUCCESS(InfStatus))
    {
      DPRINT("Failed to create buffer (Status 0x%lx)\n", InfStatus);
      return InfStatus;
    }

  /* Open the inf file */
  InitializeObjectAttributes(&ObjectAttributes,
                             FileName,
                             0,
                             NULL,
                             NULL);

  Status = NtOpenFile(&FileHandle,
                      GENERIC_WRITE | SYNCHRONIZE,
                      &ObjectAttributes,
                      &IoStatusBlock,
                      0,
                      FILE_SYNCHRONOUS_IO_NONALERT | FILE_NON_DIRECTORY_FILE);
  if (!INF_SUCCESS(Status))
    {
      DPRINT1("NtOpenFile() failed (Status %lx)\n", Status);
      FREE(Buffer);
      return Status;
    }

  DPRINT("NtOpenFile() successful\n");

  if (NULL != HeaderComment && 0 != HeaderComment->Length)
    {
      /* This is just a comment header, don't abort on errors here */
      HeaderBufferSize = HeaderComment->Length + 7 * sizeof(WCHAR);
      HeaderBuffer = MALLOC(HeaderBufferSize);
      if (NULL != HeaderBuffer)
        {
          strcpyW(HeaderBuffer, L"; ");
          for (Index = 0; Index < HeaderComment->Length / sizeof(WCHAR); Index++)
            {
              HeaderBuffer[2 + Index] = HeaderComment->Buffer[Index];
            }
          strcpyW(HeaderBuffer + (2 + HeaderComment->Length / sizeof(WCHAR)),
                  L"\r\n\r\n");
          NtWriteFile(FileHandle,
                      NULL,
                      NULL,
                      NULL,
                      &IoStatusBlock,
                      HeaderBuffer,
                      HeaderBufferSize,
                      NULL,
                      NULL);
          FREE(HeaderBuffer);
        }
    }

  /* Write main contents */
  Status = NtWriteFile(FileHandle,
                       NULL,
                       NULL,
                       NULL,
                       &IoStatusBlock,
                       Buffer,
                       BufferSize,
                       NULL,
                       NULL);

  NtClose(FileHandle);
  FREE(Buffer);

  if (!INF_SUCCESS(Status))
    {
      DPRINT1("NtWriteFile() failed (Status %lx)\n", Status);
      return(Status);
    }

  return STATUS_SUCCESS;
}