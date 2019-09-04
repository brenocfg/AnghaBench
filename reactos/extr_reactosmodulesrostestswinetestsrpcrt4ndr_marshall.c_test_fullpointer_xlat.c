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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PFULL_PTR_XLAT_TABLES ;

/* Variables and functions */
 int NdrFullPointerFree (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  NdrFullPointerInsertRefId (int /*<<< orphan*/ ,int,void*) ; 
 int NdrFullPointerQueryPointer (int /*<<< orphan*/ ,void*,int,int*) ; 
 int NdrFullPointerQueryRefId (int /*<<< orphan*/ ,int,int,void**) ; 
 int /*<<< orphan*/  NdrFullPointerXlatFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NdrFullPointerXlatInit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLAT_CLIENT ; 
 int /*<<< orphan*/  XLAT_SERVER ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_fullpointer_xlat(void)
{
    PFULL_PTR_XLAT_TABLES pXlatTables;
    ULONG RefId;
    int ret;
    void *Pointer;

    pXlatTables = NdrFullPointerXlatInit(2, XLAT_CLIENT);

    /* "marshaling" phase */

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xcafebeef, 1, &RefId);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(RefId == 0x1, "RefId should be 0x1 instead of 0x%x\n", RefId);

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xcafebeef, 0, &RefId);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(RefId == 0x1, "RefId should be 0x1 instead of 0x%x\n", RefId);

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xcafebabe, 0, &RefId);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(RefId == 0x2, "RefId should be 0x2 instead of 0x%x\n", RefId);

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xdeadbeef, 0, &RefId);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(RefId == 0x3, "RefId should be 0x3 instead of 0x%x\n", RefId);

    ret = NdrFullPointerQueryPointer(pXlatTables, NULL, 0, &RefId);
    ok(ret == 1, "ret should be 1 instead of 0x%x\n", ret);
    ok(RefId == 0, "RefId should be 0 instead of 0x%x\n", RefId);

    /* "unmarshaling" phase */

    ret = NdrFullPointerQueryRefId(pXlatTables, 0x0, 0, &Pointer);
    ok(ret == 1, "ret should be 1 instead of 0x%x\n", ret);

    ret = NdrFullPointerQueryRefId(pXlatTables, 0x2, 0, &Pointer);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(Pointer == (void *)0xcafebabe, "Pointer should be 0xcafebabe instead of %p\n", Pointer);

    ret = NdrFullPointerQueryRefId(pXlatTables, 0x4, 0, &Pointer);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(Pointer == NULL, "Pointer should be NULL instead of %p\n", Pointer);

    NdrFullPointerInsertRefId(pXlatTables, 0x4, (void *)0xdeadbabe);

    ret = NdrFullPointerQueryRefId(pXlatTables, 0x4, 1, &Pointer);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(Pointer == (void *)0xdeadbabe, "Pointer should be (void *)0xdeadbabe instead of %p\n", Pointer);

    NdrFullPointerXlatFree(pXlatTables);

    pXlatTables = NdrFullPointerXlatInit(2, XLAT_SERVER);

    /* "unmarshaling" phase */

    ret = NdrFullPointerQueryRefId(pXlatTables, 0x2, 1, &Pointer);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(Pointer == NULL, "Pointer should be NULL instead of %p\n", Pointer);

    NdrFullPointerInsertRefId(pXlatTables, 0x2, (void *)0xcafebabe);

    ret = NdrFullPointerQueryRefId(pXlatTables, 0x2, 0, &Pointer);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(Pointer == (void *)0xcafebabe, "Pointer should be (void *)0xcafebabe instead of %p\n", Pointer);

    ret = NdrFullPointerQueryRefId(pXlatTables, 0x2, 1, &Pointer);
    ok(ret == 1, "ret should be 1 instead of 0x%x\n", ret);
    ok(Pointer == (void *)0xcafebabe, "Pointer should be (void *)0xcafebabe instead of %p\n", Pointer);

    /* "marshaling" phase */

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xcafebeef, 1, &RefId);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(RefId == 0x3, "RefId should be 0x3 instead of 0x%x\n", RefId);

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xcafebeef, 1, &RefId);
    ok(ret == 1, "ret should be 1 instead of 0x%x\n", ret);
    ok(RefId == 0x3, "RefId should be 0x3 instead of 0x%x\n", RefId);

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xcafebeef, 0, &RefId);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(RefId == 0x3, "RefId should be 0x3 instead of 0x%x\n", RefId);

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xcafebabe, 0, &RefId);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(RefId == 0x2, "RefId should be 0x2 instead of 0x%x\n", RefId);

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xdeadbeef, 0, &RefId);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(RefId == 0x4, "RefId should be 0x4 instead of 0x%x\n", RefId);

    /* "freeing" phase */

    ret = NdrFullPointerFree(pXlatTables, (void *)0xcafebeef);
    ok(ret == 1, "ret should be 1 instead of 0x%x\n", ret);

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xcafebeef, 0x20, &RefId);
    ok(ret == 1, "ret should be 1 instead of 0x%x\n", ret);
    ok(RefId == 0x3, "RefId should be 0x3 instead of 0x%x\n", RefId);

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xcafebeef, 1, &RefId);
    ok(ret == 1, "ret should be 1 instead of 0x%x\n", ret);
    ok(RefId == 0x3, "RefId should be 0x3 instead of 0x%x\n", RefId);

    ret = NdrFullPointerFree(pXlatTables, (void *)0xcafebabe);
    ok(ret == 1, "ret should be 1 instead of 0x%x\n", ret);

    ret = NdrFullPointerFree(pXlatTables, (void *)0xdeadbeef);
    ok(ret == 1, "ret should be 1 instead of 0x%x\n", ret);

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xdeadbeef, 0x20, &RefId);
    ok(ret == 1, "ret should be 1 instead of 0x%x\n", ret);
    ok(RefId == 0x4, "RefId should be 0x4 instead of 0x%x\n", RefId);

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xdeadbeef, 1, &RefId);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);
    ok(RefId == 0x4, "RefId should be 0x4 instead of 0x%x\n", RefId);

    ret = NdrFullPointerQueryPointer(pXlatTables, (void *)0xdeadbeef, 1, &RefId);
    ok(ret == 1, "ret should be 1 instead of 0x%x\n", ret);
    ok(RefId == 0x4, "RefId should be 0x4 instead of 0x%x\n", RefId);

    ret = NdrFullPointerFree(pXlatTables, (void *)0xdeadbeef);
    ok(ret == 0, "ret should be 0 instead of 0x%x\n", ret);

    NdrFullPointerXlatFree(pXlatTables);
}