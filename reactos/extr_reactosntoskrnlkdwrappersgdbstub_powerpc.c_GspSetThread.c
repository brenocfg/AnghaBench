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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/ * PETHREAD ;
typedef  int* PCHAR ;

/* Variables and functions */
 int /*<<< orphan*/ * GspDbgThread ; 
 int /*<<< orphan*/  GspFindThread (int*,int /*<<< orphan*/ **) ; 
 char* GspOutBuffer ; 
 int /*<<< orphan*/ * GspRunThread ; 
 int /*<<< orphan*/  ObDereferenceObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ObReferenceObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PsGetCurrentThread () ; 

VOID
GspSetThread(PCHAR Request)
{
  PETHREAD ThreadInfo;
  PCHAR ptr = &Request[1];

  switch (Request[0])
  {
    case 'c': /* Run thread */
      if (GspFindThread(ptr, &ThreadInfo))
        {
          GspOutBuffer[0] = 'O';
          GspOutBuffer[1] = 'K';

          if (NULL != GspRunThread)
            {
              ObDereferenceObject(GspRunThread);
            }
          GspRunThread = ThreadInfo;
          if (NULL != GspRunThread)
            {
              ObReferenceObject(GspRunThread);
            }
        }
      else
        {
          GspOutBuffer[0] = 'E';
        }
      break;
    case 'g': /* Debug thread */
      if (GspFindThread(ptr, &ThreadInfo))
        {
          GspOutBuffer[0] = 'O';
          GspOutBuffer[1] = 'K';

          if (NULL != GspDbgThread)
            {
              ObDereferenceObject(GspDbgThread);
            }

          if (ThreadInfo == PsGetCurrentThread())
            {
              GspDbgThread = NULL;
              ObDereferenceObject(ThreadInfo);
            }
          else
            {
              GspDbgThread = ThreadInfo;
            }
        }
      else
        {
          GspOutBuffer[0] = 'E';
        }
      break;
    default:
      break;
  }
}