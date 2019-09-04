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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PINFCONTEXT ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  INFSTATUS ;

/* Variables and functions */
 scalar_t__ INF_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfpGetIntField (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 

int
InfHostGetIntField(PINFCONTEXT Context,
                   ULONG FieldIndex,
                   INT *IntegerValue)
{
  INFSTATUS Status;

  Status = InfpGetIntField(Context, FieldIndex, IntegerValue);
  if (INF_SUCCESS(Status))
    {
      return 0;
    }
  else
    {
      errno = Status;
      return -1;
    }
}