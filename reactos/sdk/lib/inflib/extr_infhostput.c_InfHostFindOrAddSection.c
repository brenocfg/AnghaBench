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
typedef  int /*<<< orphan*/  PINFCONTEXT ;
typedef  int /*<<< orphan*/  PINFCACHE ;
typedef  int /*<<< orphan*/  INFSTATUS ;
typedef  scalar_t__ HINF ;

/* Variables and functions */
 scalar_t__ INF_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InfpFindOrAddSection (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 

int
InfHostFindOrAddSection(HINF InfHandle,
                        const WCHAR *Section,
                        PINFCONTEXT *Context)
{
  INFSTATUS Status;

  Status = InfpFindOrAddSection((PINFCACHE) InfHandle, Section, Context);
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