#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rScore; scalar_t__ iLevel; } ;
typedef  TYPE_1__ RtreeSearchPoint ;

/* Variables and functions */

__attribute__((used)) static int rtreeSearchPointCompare(
  const RtreeSearchPoint *pA,
  const RtreeSearchPoint *pB
){
  if( pA->rScore<pB->rScore ) return -1;
  if( pA->rScore>pB->rScore ) return +1;
  if( pA->iLevel<pB->iLevel ) return -1;
  if( pA->iLevel>pB->iLevel ) return +1;
  return 0;
}