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

/* Variables and functions */
 int /*<<< orphan*/  LSM_MIN (int,int) ; 
 int memcmp (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xCmp(void *p1, int n1, void *p2, int n2){
  int res;
  res = memcmp(p1, p2, LSM_MIN(n1, n2));
  if( res==0 ) res = (n1-n2);
  return res;
}