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
typedef  int /*<<< orphan*/  PLONG ;
typedef  int /*<<< orphan*/ * PETHREAD ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GspHex2Long (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PsLookupThreadByThreadId (scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

BOOLEAN
GspFindThread(PCHAR Data,
  PETHREAD *Thread)
{
  PETHREAD ThreadInfo = NULL;

  if (strcmp (Data, "-1") == 0)
    {
      /* All threads */
      ThreadInfo = NULL;
    }
  else
    {
      ULONG uThreadId;
      HANDLE ThreadId;
      PCHAR ptr = &Data[0];

      GspHex2Long(&ptr, (PLONG) &uThreadId);
      ThreadId = (HANDLE)uThreadId;

      if (!NT_SUCCESS(PsLookupThreadByThreadId(ThreadId, &ThreadInfo)))
        {
          *Thread = NULL;
          return FALSE;
        }
    }
  *Thread = ThreadInfo;
  return TRUE;
}