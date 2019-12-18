#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* xSize ) (void*) ;int (* xRoundup ) (int) ;void* (* xRealloc ) (void*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,int) ; 
 TYPE_1__ memtraceBase ; 
 int /*<<< orphan*/  memtraceFree (void*) ; 
 void* memtraceMalloc (int) ; 
 scalar_t__ memtraceOut ; 
 int stub1 (void*) ; 
 int stub2 (int) ; 
 int stub3 (void*) ; 
 int stub4 (int) ; 
 void* stub5 (void*,int) ; 

__attribute__((used)) static void *memtraceRealloc(void *p, int n){
  if( p==0 ) return memtraceMalloc(n);
  if( n==0 ){
    memtraceFree(p);
    return 0;
  }
  if( memtraceOut ){
    fprintf(memtraceOut, "MEMTRACE: resize %d -> %d bytes\n",
            memtraceBase.xSize(p), memtraceBase.xRoundup(n));
  }
  return memtraceBase.xRealloc(p, n);
}