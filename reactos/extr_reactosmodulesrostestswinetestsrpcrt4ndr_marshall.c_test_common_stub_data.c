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
typedef  int /*<<< orphan*/  unset_ptr ;
typedef  int ULONG_PTR ;
struct TYPE_3__ {void* BufferMark; int MemorySize; void* Memory; int pAllocAllNodesContext; void* pPointerQueueState; int IgnoreEmbeddedPointers; int PointerBufferMark; int uFlags; int MaxCount; int Offset; int ActualCount; int StackTop; void* pPresentedType; void* pTransmitType; void* SavedHandle; int FullPtrRefId; int PointerLength; int fInDontFree; int fDontCallFreeInst; int fHasReturn; int fHasExtensions; int fHasNewCorrDesc; int fIsIn; int fIsOicf; int fBufferValid; int fNeedMCCP; int fUnused; int fUnused2; int dwDestContext; int pvDestContext; void* SavedContextHandles; int ParamNumber; int pRpcChannelBuffer; int pArrayInfo; void* SizePtrCountArray; void* SizePtrOffsetArray; void* SizePtrLengthArray; void* pArgQueue; int dwStubPhase; void* pAsyncMsg; void* pCorrInfo; void* pCorrMemory; void* pMemoryList; void* pCSInfo; void* ConformanceMark; void* VarianceMark; int Unused; void* pContext; void* ContextHandleHash; void* pUserMarshalList; int Reserved51_3; int Reserved51_4; int Reserved51_5; int /*<<< orphan*/  LowStackMark; int /*<<< orphan*/ * StubDesc; int /*<<< orphan*/  pfnFree; int /*<<< orphan*/  pfnAllocate; } ;
typedef  TYPE_1__ MIDL_STUB_MESSAGE ;

/* Variables and functions */
 int MSHCTX_DIFFERENTMACHINE ; 
 int /*<<< orphan*/  Object_StubDesc ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memset (void**,int,int) ; 
 int /*<<< orphan*/  my_alloc ; 
 int /*<<< orphan*/  my_free ; 
 int /*<<< orphan*/  ok (int,char*,char const*,int,...) ; 
 int /*<<< orphan*/  trace (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_common_stub_data( const char *prefix, const MIDL_STUB_MESSAGE *stubMsg )
{
    void *unset_ptr;

    memset(&unset_ptr, 0xcc, sizeof(unset_ptr));

#define TEST_ZERO(field, fmt) ok(stubMsg->field == 0, "%s: " #field " should have been set to zero instead of " fmt "\n", prefix, stubMsg->field)
#define TEST_POINTER_UNSET(field) ok(stubMsg->field == unset_ptr, "%s: " #field " should have been unset instead of %p\n", prefix, stubMsg->field)
#define TEST_ULONG_UNSET(field) ok(stubMsg->field == 0xcccccccc, "%s: " #field " should have been unset instead of 0x%x\n", prefix, stubMsg->field)
#define TEST_ULONG_PTR_UNSET(field) ok(stubMsg->field == (ULONG_PTR)unset_ptr, "%s: " #field " should have been unset instead of 0x%lx\n", prefix, stubMsg->field)

    TEST_POINTER_UNSET(BufferMark);
    TEST_ULONG_UNSET(MemorySize);
    TEST_POINTER_UNSET(Memory);
    TEST_ZERO(pAllocAllNodesContext, "%p");
    ok(stubMsg->pPointerQueueState == 0 ||
       broken(stubMsg->pPointerQueueState == unset_ptr), /* win2k */
       "%s: pPointerQueueState should have been unset instead of %p\n",
       prefix, stubMsg->pPointerQueueState);
    TEST_ZERO(IgnoreEmbeddedPointers, "%d");
    TEST_ZERO(PointerBufferMark, "%p");
    ok( stubMsg->uFlags == 0 ||
        broken(stubMsg->uFlags == 0xcc), /* win9x */
        "%s: uFlags should have been set to zero instead of 0x%x\n", prefix, stubMsg->uFlags );
    /* FIXME: UniquePtrCount */
    TEST_ULONG_PTR_UNSET(MaxCount);
    TEST_ULONG_UNSET(Offset);
    TEST_ULONG_UNSET(ActualCount);
    ok(stubMsg->pfnAllocate == my_alloc, "%s: pfnAllocate should have been %p instead of %p\n",
       prefix, my_alloc, stubMsg->pfnAllocate);
    ok(stubMsg->pfnFree == my_free, "%s: pfnFree should have been %p instead of %p\n",
       prefix, my_free, stubMsg->pfnFree);
    TEST_ZERO(StackTop, "%p");
    TEST_POINTER_UNSET(pPresentedType);
    TEST_POINTER_UNSET(pTransmitType);
    TEST_POINTER_UNSET(SavedHandle);
    ok(stubMsg->StubDesc == &Object_StubDesc, "%s: StubDesc should have been %p instead of %p\n",
       prefix, &Object_StubDesc, stubMsg->StubDesc);
    TEST_ZERO(FullPtrRefId, "%d");
    ok( stubMsg->PointerLength == 0 ||
        broken(stubMsg->PointerLength == 1), /* win9x, nt4 */
        "%s: pAsyncMsg should have been set to zero instead of %d\n", prefix, stubMsg->PointerLength );
    TEST_ZERO(fInDontFree, "%d");
    TEST_ZERO(fDontCallFreeInst, "%d");
    ok( stubMsg->fHasReturn == 0 || broken(stubMsg->fHasReturn), /* win9x, nt4 */
        "%s: fHasReturn should have been set to zero instead of %d\n", prefix, stubMsg->fHasReturn );
    TEST_ZERO(fHasExtensions, "%d");
    TEST_ZERO(fHasNewCorrDesc, "%d");
    ok(stubMsg->fIsIn == 0 || broken(stubMsg->fIsIn), /* win9x, nt4 */
       "%s: fIsIn should have been set to 0 instead of %d\n", prefix, stubMsg->fIsIn);
    TEST_ZERO(fIsOicf, "%d");
    ok(stubMsg->fBufferValid == 0,
       "%s: fBufferValid should have been set to 0 instead of %d\n", prefix, stubMsg->fBufferValid);
    TEST_ZERO(fNeedMCCP, "%d");
    ok(stubMsg->fUnused == 0 ||
       stubMsg->fUnused == -2, /* Vista */
       "%s: fUnused should have been set to 0 or -2 instead of %d\n", prefix, stubMsg->fUnused);
    ok(stubMsg->fUnused2 == 0xffffcccc, "%s: fUnused2 should have been 0xffffcccc instead of 0x%x\n",
       prefix, stubMsg->fUnused2);
    ok(stubMsg->dwDestContext == MSHCTX_DIFFERENTMACHINE,
       "%s: dwDestContext should have been MSHCTX_DIFFERENTMACHINE instead of %d\n",
       prefix, stubMsg->dwDestContext);
    TEST_ZERO(pvDestContext, "%p");
    TEST_POINTER_UNSET(SavedContextHandles);
    TEST_ULONG_UNSET(ParamNumber);
    TEST_ZERO(pRpcChannelBuffer, "%p");
    TEST_ZERO(pArrayInfo, "%p");
    TEST_POINTER_UNSET(SizePtrCountArray);
    TEST_POINTER_UNSET(SizePtrOffsetArray);
    TEST_POINTER_UNSET(SizePtrLengthArray);
    TEST_POINTER_UNSET(pArgQueue);
    TEST_ZERO(dwStubPhase, "%d");
    /* FIXME: where does this value come from? */
    trace("%s: LowStackMark is %p\n", prefix, stubMsg->LowStackMark);
    ok( stubMsg->pAsyncMsg == 0 || broken(stubMsg->pAsyncMsg == unset_ptr), /* win9x, nt4 */
        "%s: pAsyncMsg should have been set to zero instead of %p\n", prefix, stubMsg->pAsyncMsg );
    ok( stubMsg->pCorrInfo == 0 || broken(stubMsg->pCorrInfo == unset_ptr), /* win9x, nt4 */
        "%s: pCorrInfo should have been set to zero instead of %p\n", prefix, stubMsg->pCorrInfo );
    ok( stubMsg->pCorrMemory == 0 || broken(stubMsg->pCorrMemory == unset_ptr), /* win9x, nt4 */
        "%s: pCorrMemory should have been set to zero instead of %p\n", prefix, stubMsg->pCorrMemory );
    ok( stubMsg->pMemoryList == 0 || broken(stubMsg->pMemoryList == unset_ptr), /* win9x, nt4 */
        "%s: pMemoryList should have been set to zero instead of %p\n", prefix, stubMsg->pMemoryList );
    TEST_POINTER_UNSET(pCSInfo);
    TEST_POINTER_UNSET(ConformanceMark);
    TEST_POINTER_UNSET(VarianceMark);
    ok(stubMsg->Unused == (ULONG_PTR)unset_ptr, "%s: Unused should have be unset instead of 0x%lx\n",
       prefix, stubMsg->Unused);
    TEST_POINTER_UNSET(pContext);
    TEST_POINTER_UNSET(ContextHandleHash);
    TEST_POINTER_UNSET(pUserMarshalList);
    TEST_ULONG_PTR_UNSET(Reserved51_3);
    TEST_ULONG_PTR_UNSET(Reserved51_4);
    TEST_ULONG_PTR_UNSET(Reserved51_5);

#undef TEST_ULONG_PTR_UNSET
#undef TEST_ULONG_UNSET
#undef TEST_POINTER_UNSET
#undef TEST_ZERO
}