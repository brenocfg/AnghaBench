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
typedef  int /*<<< orphan*/ * HLOCAL ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int LMEM_MOVEABLE ; 
 int LMEM_ZEROINIT ; 
 int /*<<< orphan*/ * LocalAlloc (int,size_t) ; 
 int /*<<< orphan*/ * LocalDiscard (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LocalHandle (scalar_t__*) ; 
 scalar_t__* LocalLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LocalReAlloc (int /*<<< orphan*/ *,int,int) ; 
 int LocalSize (int /*<<< orphan*/ *) ; 
 scalar_t__ LocalUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_ERROR ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_LocalAlloc(void)
{
    ULONG memchunk;
    HLOCAL mem1,mem2,mem2a,mem2b;
    UCHAR *mem2ptr;
    UINT i;
    BOOL error;
    memchunk=100000;

    /* Check that a normal alloc works */
    mem1=LocalAlloc(0,memchunk);
    ok(mem1!=NULL,"LocalAlloc failed: error=%d\n",GetLastError());
    if(mem1) {
      ok(LocalSize(mem1)>=memchunk, "LocalAlloc should return a big enough memory block\n");
    }

    /* Check that a 'zeroing' and lock alloc works */
    mem2=LocalAlloc(LMEM_ZEROINIT|LMEM_MOVEABLE,memchunk);
    ok(mem2!=NULL,"LocalAlloc failed: error=%d\n",GetLastError());
    if(mem2) {
      ok(LocalSize(mem2)>=memchunk,"LocalAlloc should return a big enough memory block\n");
      mem2ptr=LocalLock(mem2);
      ok(mem2ptr!=NULL,"LocalLock: error=%d\n",GetLastError());
      if(mem2ptr) {
        error=FALSE;
        for(i=0;i<memchunk;i++) {
          if(mem2ptr[i]!=0) {
            error=TRUE;
          }
        }
        ok(!error,"LocalAlloc should have zeroed out its allocated memory\n");
        SetLastError(0);
        error=LocalUnlock(mem2);
        ok(!error && GetLastError()==NO_ERROR,
           "LocalUnlock Failed: rc=%d err=%d\n",error,GetLastError());
      }
    }
   mem2a=LocalFree(mem2);
   ok(mem2a==NULL, "LocalFree failed: %p\n",mem2a);

   /* Reallocate mem2 as moveable memory */
   mem2=LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT,memchunk);
   ok(mem2!=NULL, "LocalAlloc failed to create moveable memory, error=%d\n",GetLastError());

   /* Check that ReAllocing memory works as expected */
    mem2a=LocalReAlloc(mem2,2*memchunk,LMEM_MOVEABLE | LMEM_ZEROINIT);
    ok(mem2a!=NULL,"LocalReAlloc failed, error=%d\n",GetLastError());
    if(mem2a) {
      ok(LocalSize(mem2a)>=2*memchunk,"LocalReAlloc failed\n");
      mem2ptr=LocalLock(mem2a);
      ok(mem2ptr!=NULL,"LocalLock Failed\n");
      if(mem2ptr) {
        error=FALSE;
        for(i=0;i<memchunk;i++) {
          if(mem2ptr[memchunk+i]!=0) {
            error=TRUE;
          }
        }
        ok(!error,"LocalReAlloc should have zeroed out its allocated memory\n");
        /* Check that LocalHandle works */
        mem2b=LocalHandle(mem2ptr);
        ok(mem2b==mem2a,"LocalHandle didn't return the correct memory handle %p/%p for %p\n",
           mem2a, mem2b, mem2ptr);
        /* Check that we can't discard locked memory */
        mem2b=LocalDiscard(mem2a);
        ok(mem2b==NULL,"Discarded memory we shouldn't have\n");
        SetLastError(NO_ERROR);
        ok(!LocalUnlock(mem2a) && GetLastError()==NO_ERROR, "LocalUnlock Failed\n");
      }
    }
    if(mem1) {
      ok(LocalFree(mem1)==NULL,"LocalFree failed\n");
    }
    if(mem2a) {
      ok(LocalFree(mem2a)==NULL,"LocalFree failed\n");
    } else {
      ok(LocalFree(mem2)==NULL,"LocalFree failed\n");
    }
}