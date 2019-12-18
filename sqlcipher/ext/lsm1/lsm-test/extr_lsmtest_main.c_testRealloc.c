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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ realloc (int /*<<< orphan*/ *,int) ; 
 void* testMalloc (int) ; 

void *testRealloc(void *ptr, int n){
  if( ptr ){
    u8 *p = (u8*)ptr - 8;
    int nOrig =  *(int*)p;
    p = (u8*)realloc(p, n+8);
    if( nOrig<n ){
      memset(&p[8+nOrig], 0, n-nOrig);
    }
    *(int*)p = n;
    return (void*)&p[8];
  }
  return testMalloc(n);
}