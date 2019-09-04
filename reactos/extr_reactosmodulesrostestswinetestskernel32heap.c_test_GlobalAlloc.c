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
typedef  size_t ULONG ;
typedef  size_t UINT ;
typedef  scalar_t__ UCHAR ;
typedef  scalar_t__* HGLOBAL ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int GMEM_MODIFY ; 
 int GMEM_MOVEABLE ; 
 int GMEM_ZEROINIT ; 
 scalar_t__ GetLastError () ; 
 scalar_t__* GlobalAlloc (int,size_t) ; 
 scalar_t__* GlobalDiscard (scalar_t__*) ; 
 int /*<<< orphan*/ * GlobalFree (scalar_t__*) ; 
 scalar_t__* GlobalHandle (scalar_t__*) ; 
 scalar_t__* GlobalLock (scalar_t__*) ; 
 scalar_t__* GlobalReAlloc (scalar_t__*,int,int) ; 
 int GlobalSize (scalar_t__*) ; 
 int /*<<< orphan*/  GlobalUnlock (scalar_t__*) ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_GlobalAlloc(void)
{
    ULONG memchunk;
    HGLOBAL mem1,mem2,mem2a,mem2b;
    UCHAR *mem2ptr;
    UINT i;
    BOOL error;
    memchunk=100000;

    SetLastError(NO_ERROR);
    /* Check that a normal alloc works */
    mem1=GlobalAlloc(0,memchunk);
    ok(mem1!=NULL,"GlobalAlloc failed\n");
    if(mem1) {
      ok(GlobalSize(mem1)>=memchunk, "GlobalAlloc should return a big enough memory block\n");
    }

    /* Check that a 'zeroing' alloc works */
    mem2=GlobalAlloc(GMEM_ZEROINIT,memchunk);
    ok(mem2!=NULL,"GlobalAlloc failed: error=%d\n",GetLastError());
    if(mem2) {
      ok(GlobalSize(mem2)>=memchunk,"GlobalAlloc should return a big enough memory block\n");
      mem2ptr=GlobalLock(mem2);
      ok(mem2ptr==mem2,"GlobalLock should have returned the same memory as was allocated\n");
      if(mem2ptr) {
        error=FALSE;
        for(i=0;i<memchunk;i++) {
          if(mem2ptr[i]!=0) {
            error=TRUE;
          }
        }
        ok(!error,"GlobalAlloc should have zeroed out its allocated memory\n");
      }
   }
    /* Check that GlobalReAlloc works */
    /* Check that we can change GMEM_FIXED to GMEM_MOVEABLE */
    mem2a=GlobalReAlloc(mem2,0,GMEM_MODIFY | GMEM_MOVEABLE);
    if(mem2a!=NULL) {
      mem2=mem2a;
      mem2ptr=GlobalLock(mem2a);
      ok(mem2ptr!=NULL && !GlobalUnlock(mem2a)&&GetLastError()==NO_ERROR,
         "Converting from FIXED to MOVEABLE didn't REALLY work\n");
    }

    /* Check that ReAllocing memory works as expected */
    mem2a=GlobalReAlloc(mem2,2*memchunk,GMEM_MOVEABLE | GMEM_ZEROINIT);
    ok(mem2a!=NULL,"GlobalReAlloc failed\n");
    if(mem2a) {
      ok(GlobalSize(mem2a)>=2*memchunk,"GlobalReAlloc failed\n");
      mem2ptr=GlobalLock(mem2a);
      ok(mem2ptr!=NULL,"GlobalLock Failed\n");
      if(mem2ptr) {
        error=FALSE;
        for(i=0;i<memchunk;i++) {
          if(mem2ptr[memchunk+i]!=0) {
            error=TRUE;
          }
        }
        ok(!error,"GlobalReAlloc should have zeroed out its allocated memory\n");

        /* Check that GlobalHandle works */
        mem2b=GlobalHandle(mem2ptr);
        ok(mem2b==mem2a,"GlobalHandle didn't return the correct memory handle %p/%p for %p\n",
           mem2a, mem2b, mem2ptr);
        /* Check that we can't discard locked memory */
        mem2b=GlobalDiscard(mem2a);
        if(mem2b==NULL) {
          ok(!GlobalUnlock(mem2a) && GetLastError()==NO_ERROR,"GlobalUnlock Failed\n");
        }
      }
    }
    if(mem1) {
      ok(GlobalFree(mem1)==NULL,"GlobalFree failed\n");
    }
    if(mem2a) {
      ok(GlobalFree(mem2a)==NULL,"GlobalFree failed\n");
    } else {
      ok(GlobalFree(mem2)==NULL,"GlobalFree failed\n");
    }
}