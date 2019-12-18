#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* pNext; int /*<<< orphan*/  zPattern; } ;
typedef  TYPE_1__ quotaGroup ;
struct TYPE_5__ {TYPE_1__* pGroup; } ;

/* Variables and functions */
 TYPE_3__ gQuota ; 
 scalar_t__ quotaStrglob (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static quotaGroup *quotaGroupFind(const char *zFilename){
  quotaGroup *p;
  for(p=gQuota.pGroup; p && quotaStrglob(p->zPattern, zFilename)==0;
      p=p->pNext){}
  return p;
}