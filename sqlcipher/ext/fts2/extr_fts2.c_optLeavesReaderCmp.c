#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int segment; } ;
typedef  TYPE_1__ OptLeavesReader ;

/* Variables and functions */
 int optLeavesReaderTermCmp (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int optLeavesReaderCmp(OptLeavesReader *lr1, OptLeavesReader *lr2){
  int c = optLeavesReaderTermCmp(lr1, lr2);
  if( c!=0 ) return c;
  return lr1->segment-lr2->segment;
}