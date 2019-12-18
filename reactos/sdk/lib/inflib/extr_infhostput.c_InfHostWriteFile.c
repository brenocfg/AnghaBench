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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  PINFCACHE ;
typedef  int /*<<< orphan*/  INFSTATUS ;
typedef  scalar_t__ HINF ;
typedef  int /*<<< orphan*/  FILE ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INF_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfpBuildFileBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fwrite (int /*<<< orphan*/ *,size_t,size_t,int /*<<< orphan*/ *) ; 

int
InfHostWriteFile(HINF InfHandle,
                 const CHAR *FileName,
                 const CHAR *HeaderComment)
{
  WCHAR *Buffer;
  ULONG BufferSize;
  INFSTATUS Status;
  FILE *File;

  Status = InfpBuildFileBuffer((PINFCACHE) InfHandle, &Buffer, &BufferSize);
  if (! INF_SUCCESS(Status))
    {
      errno = Status;
      return -1;
    }

  File = fopen(FileName, "wb");
  if (NULL == File)
    {
      FREE(Buffer);
      DPRINT1("fopen() failed (errno %d)\n", errno);
      return -1;
    }

  DPRINT("fopen() successful\n");

  if (NULL != HeaderComment && '\0' != *HeaderComment)
    {
//      fprintf(File, "; %s\r\n\r\n", HeaderComment);
    }

  if (BufferSize != fwrite(Buffer, (size_t)1, (size_t)BufferSize, File))
    {
      DPRINT1("fwrite() failed (errno %d)\n", errno);
      fclose(File);
      FREE(Buffer);
      return -1;
    }

  fclose(File);

  FREE(Buffer);

  return 0;
}