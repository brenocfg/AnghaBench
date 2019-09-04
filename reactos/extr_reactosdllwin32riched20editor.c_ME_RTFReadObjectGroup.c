#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ rtfClass; scalar_t__ rtfMajor; int /*<<< orphan*/  rtfMinor; } ;
typedef  TYPE_1__ RTF_Info ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ RTFCheckCM (TYPE_1__*,scalar_t__,scalar_t__) ; 
 scalar_t__ RTFCheckCMM (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RTFGetToken (TYPE_1__*) ; 
 int /*<<< orphan*/  RTFRouteToken (TYPE_1__*) ; 
 int /*<<< orphan*/  RTFSkipGroup (TYPE_1__*) ; 
 scalar_t__ rtfBeginGroup ; 
 scalar_t__ rtfControl ; 
 int /*<<< orphan*/  rtfDestination ; 
 scalar_t__ rtfEOF ; 
 scalar_t__ rtfEndGroup ; 
 scalar_t__ rtfGroup ; 
 scalar_t__ rtfObjAttr ; 
 int /*<<< orphan*/  rtfObjResult ; 

__attribute__((used)) static void ME_RTFReadObjectGroup(RTF_Info *info)
{
  for (;;)
  {
    RTFGetToken (info);
    if (info->rtfClass == rtfEOF)
      return;
    if (RTFCheckCM(info, rtfGroup, rtfEndGroup))
      break;
    if (RTFCheckCM(info, rtfGroup, rtfBeginGroup))
    {
      RTFGetToken (info);
      if (info->rtfClass == rtfEOF)
        return;
      if (RTFCheckCMM(info, rtfControl, rtfDestination, rtfObjResult))
      {
	int	level = 1;

	while (RTFGetToken (info) != rtfEOF)
	{
          if (info->rtfClass == rtfGroup)
          {
            if (info->rtfMajor == rtfBeginGroup) level++;
            else if (info->rtfMajor == rtfEndGroup && --level < 0) break;
          }
          RTFRouteToken(info);
	}
      }
      else RTFSkipGroup(info);
      continue;
    }
    if (!RTFCheckCM (info, rtfControl, rtfObjAttr))
    {
      FIXME("Non supported attribute: %d %d %d\n", info->rtfClass, info->rtfMajor, info->rtfMinor);
      return;
    }
  }
  RTFRouteToken(info);	/* feed "}" back to router */
}