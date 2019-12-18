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
typedef  int /*<<< orphan*/  OrderedDLReader ;

/* Variables and functions */
 scalar_t__ orderedDLReaderCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void orderedDLReaderReorder(OrderedDLReader *p, int n){
  while( n>1 && orderedDLReaderCmp(p, p+1)>0 ){
    OrderedDLReader tmp = p[0];
    p[0] = p[1];
    p[1] = tmp;
    n--;
    p++;
  }
}