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
typedef  int ULONG_PTR ;
typedef  int ULONG ;
typedef  int UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_3__ {int dwPageSize; } ;
typedef  TYPE_1__ SYSTEM_INFO ;
typedef  scalar_t__* LPVOID ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  HEAP_REALLOC_IN_PLACE_ONLY ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__* HeapAlloc (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ HeapCreate (int /*<<< orphan*/ ,int,int) ; 
 int HeapDestroy (scalar_t__) ; 
 int HeapFree (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__* HeapReAlloc (scalar_t__,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int HeapSize (scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_HeapCreate(void)
{
    SYSTEM_INFO sysInfo;
    ULONG memchunk;
    HANDLE heap;
    LPVOID mem1,mem1a,mem3;
    UCHAR *mem2,*mem2a;
    UINT i;
    BOOL error;
    DWORD dwSize;

    /* Retrieve the page size for this system */
    GetSystemInfo(&sysInfo);
    ok(sysInfo.dwPageSize>0,"GetSystemInfo should return a valid page size\n");

    /* Create a Heap with a minimum and maximum size */
    /* Note that Windows and Wine seem to behave a bit differently with respect
       to memory allocation.  In Windows, you can't access all the memory
       specified in the heap (due to overhead), so choosing a reasonable maximum
       size for the heap was done mostly by trial-and-error on Win2k.  It may need
       more tweaking for otherWindows variants.
    */
    memchunk=10*sysInfo.dwPageSize;
    heap=HeapCreate(0,2*memchunk,5*memchunk);
    ok( !((ULONG_PTR)heap & 0xffff), "heap %p not 64K aligned\n", heap );

    /* Check that HeapCreate allocated the right amount of ram */
    mem1=HeapAlloc(heap,0,5*memchunk+1);
    ok(mem1==NULL,"HeapCreate allocated more Ram than it should have\n");
    HeapFree(heap,0,mem1);

    /* Check that a normal alloc works */
    mem1=HeapAlloc(heap,0,memchunk);
    ok(mem1!=NULL,"HeapAlloc failed\n");
    if(mem1) {
      ok(HeapSize(heap,0,mem1)>=memchunk, "HeapAlloc should return a big enough memory block\n");
    }

    /* Check that a 'zeroing' alloc works */
    mem2=HeapAlloc(heap,HEAP_ZERO_MEMORY,memchunk);
    ok(mem2!=NULL,"HeapAlloc failed\n");
    if(mem2) {
      ok(HeapSize(heap,0,mem2)>=memchunk,"HeapAlloc should return a big enough memory block\n");
      error=FALSE;
      for(i=0;i<memchunk;i++) {
        if(mem2[i]!=0) {
          error=TRUE;
        }
      }
      ok(!error,"HeapAlloc should have zeroed out its allocated memory\n");
    }

    /* Check that HeapAlloc returns NULL when requested way too much memory */
    mem3=HeapAlloc(heap,0,5*memchunk);
    ok(mem3==NULL,"HeapAlloc should return NULL\n");
    if(mem3) {
      ok(HeapFree(heap,0,mem3),"HeapFree didn't pass successfully\n");
    }

    /* Check that HeapReAlloc works */
    mem2a=HeapReAlloc(heap,HEAP_ZERO_MEMORY,mem2,memchunk+5*sysInfo.dwPageSize);
    ok(mem2a!=NULL,"HeapReAlloc failed\n");
    if(mem2a) {
      ok(HeapSize(heap,0,mem2a)>=memchunk+5*sysInfo.dwPageSize,"HeapReAlloc failed\n");
      error=FALSE;
      for(i=0;i<5*sysInfo.dwPageSize;i++) {
        if(mem2a[memchunk+i]!=0) {
          error=TRUE;
        }
      }
      ok(!error,"HeapReAlloc should have zeroed out its allocated memory\n");
    }

    /* Check that HeapReAlloc honours HEAP_REALLOC_IN_PLACE_ONLY */
    error=FALSE;
    mem1a=HeapReAlloc(heap,HEAP_REALLOC_IN_PLACE_ONLY,mem1,memchunk+sysInfo.dwPageSize);
    if(mem1a!=NULL) {
      if(mem1a!=mem1) {
        error=TRUE;
      }
    }
    ok(mem1a==NULL || !error,"HeapReAlloc didn't honour HEAP_REALLOC_IN_PLACE_ONLY\n");

    /* Check that HeapFree works correctly */
   if(mem1a) {
     ok(HeapFree(heap,0,mem1a),"HeapFree failed\n");
   } else {
     ok(HeapFree(heap,0,mem1),"HeapFree failed\n");
   }
   if(mem2a) {
     ok(HeapFree(heap,0,mem2a),"HeapFree failed\n");
   } else {
     ok(HeapFree(heap,0,mem2),"HeapFree failed\n");
   }

   /* 0-length buffer */
   mem1 = HeapAlloc(heap, 0, 0);
   ok(mem1 != NULL, "Reserved memory\n");

   dwSize = HeapSize(heap, 0, mem1);
   /* should work with 0-length buffer */
   ok(dwSize < 0xFFFFFFFF, "The size of the 0-length buffer\n");
   ok(HeapFree(heap, 0, mem1), "Freed the 0-length buffer\n");

   /* Check that HeapDestroy works */
   ok(HeapDestroy(heap),"HeapDestroy failed\n");
}