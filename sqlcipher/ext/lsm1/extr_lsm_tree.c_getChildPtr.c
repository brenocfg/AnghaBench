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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__* aiChildPtr; scalar_t__ iV2; int iV2Child; scalar_t__ iV2Ptr; } ;
typedef  TYPE_1__ TreeNode ;

/* Variables and functions */
 int array_size (scalar_t__*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static u32 getChildPtr(TreeNode *p, int iVersion, int iCell){
  assert( iVersion>=0 );
  assert( iCell>=0 && iCell<=array_size(p->aiChildPtr) );
  if( p->iV2 && p->iV2<=(u32)iVersion && iCell==p->iV2Child ) return p->iV2Ptr;
  return p->aiChildPtr[iCell];
}