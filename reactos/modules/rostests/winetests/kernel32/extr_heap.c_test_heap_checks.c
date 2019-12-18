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
typedef  int SIZE_T ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int HEAP_FREE_CHECKING_ENABLED ; 
 int HEAP_PAGE_ALLOCS ; 
 int /*<<< orphan*/  HEAP_REALLOC_IN_PLACE_ONLY ; 
 int HEAP_TAIL_CHECKING_ENABLED ; 
 int HEAP_VALIDATE ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int HeapSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  HeapValidate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static void test_heap_checks( DWORD flags )
{
    BYTE old, *p, *p2;
    BOOL ret;
    SIZE_T i, size, large_size = 3000 * 1024 + 37;

    if (flags & HEAP_PAGE_ALLOCS) return;  /* no tests for that case yet */
    trace( "testing heap flags %08x\n", flags );

    p = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 17 );
    ok( p != NULL, "HeapAlloc failed\n" );

    ret = HeapValidate( GetProcessHeap(), 0, p );
    ok( ret, "HeapValidate failed\n" );

    size = HeapSize( GetProcessHeap(), 0, p );
    ok( size == 17, "Wrong size %lu\n", size );

    ok( p[14] == 0, "wrong data %x\n", p[14] );
    ok( p[15] == 0, "wrong data %x\n", p[15] );
    ok( p[16] == 0, "wrong data %x\n", p[16] );

    if (flags & HEAP_TAIL_CHECKING_ENABLED)
    {
        ok( p[17] == 0xab, "wrong padding %x\n", p[17] );
        ok( p[18] == 0xab, "wrong padding %x\n", p[18] );
        ok( p[19] == 0xab, "wrong padding %x\n", p[19] );
    }

    p2 = HeapReAlloc( GetProcessHeap(), HEAP_REALLOC_IN_PLACE_ONLY, p, 14 );
    if (p2 == p)
    {
        if (flags & HEAP_TAIL_CHECKING_ENABLED)
        {
            ok( p[14] == 0xab, "wrong padding %x\n", p[14] );
            ok( p[15] == 0xab, "wrong padding %x\n", p[15] );
            ok( p[16] == 0xab, "wrong padding %x\n", p[16] );
        }
        else
        {
            ok( p[14] == 0, "wrong padding %x\n", p[14] );
            ok( p[15] == 0, "wrong padding %x\n", p[15] );
        }
    }
    else skip( "realloc in place failed\n");

    ret = HeapFree( GetProcessHeap(), 0, p );
    ok( ret, "HeapFree failed\n" );

    p = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 17 );
    ok( p != NULL, "HeapAlloc failed\n" );
    old = p[17];
    p[17] = 0xcc;

    if (flags & HEAP_TAIL_CHECKING_ENABLED)
    {
        ret = HeapValidate( GetProcessHeap(), 0, p );
        ok( !ret, "HeapValidate succeeded\n" );

        /* other calls only check when HEAP_VALIDATE is set */
        if (flags & HEAP_VALIDATE)
        {
            size = HeapSize( GetProcessHeap(), 0, p );
            ok( size == ~(SIZE_T)0 || broken(size == ~0u), "Wrong size %lu\n", size );

            p2 = HeapReAlloc( GetProcessHeap(), 0, p, 14 );
            ok( p2 == NULL, "HeapReAlloc succeeded\n" );

            ret = HeapFree( GetProcessHeap(), 0, p );
            ok( !ret || broken(sizeof(void*) == 8), /* not caught on xp64 */
                "HeapFree succeeded\n" );
        }

        p[17] = old;
        size = HeapSize( GetProcessHeap(), 0, p );
        ok( size == 17, "Wrong size %lu\n", size );

        p2 = HeapReAlloc( GetProcessHeap(), 0, p, 14 );
        ok( p2 != NULL, "HeapReAlloc failed\n" );
        p = p2;
    }

    ret = HeapFree( GetProcessHeap(), 0, p );
    ok( ret, "HeapFree failed\n" );

    p = HeapAlloc( GetProcessHeap(), 0, 37 );
    ok( p != NULL, "HeapAlloc failed\n" );
    memset( p, 0xcc, 37 );

    ret = HeapFree( GetProcessHeap(), 0, p );
    ok( ret, "HeapFree failed\n" );

    if (flags & HEAP_FREE_CHECKING_ENABLED)
    {
        ok( p[16] == 0xee, "wrong data %x\n", p[16] );
        ok( p[17] == 0xfe, "wrong data %x\n", p[17] );
        ok( p[18] == 0xee, "wrong data %x\n", p[18] );
        ok( p[19] == 0xfe, "wrong data %x\n", p[19] );

        ret = HeapValidate( GetProcessHeap(), 0, NULL );
        ok( ret, "HeapValidate failed\n" );

        old = p[16];
        p[16] = 0xcc;
        ret = HeapValidate( GetProcessHeap(), 0, NULL );
        ok( !ret, "HeapValidate succeeded\n" );

        p[16] = old;
        ret = HeapValidate( GetProcessHeap(), 0, NULL );
        ok( ret, "HeapValidate failed\n" );
    }

    /* now test large blocks */

    p = HeapAlloc( GetProcessHeap(), 0, large_size );
    ok( p != NULL, "HeapAlloc failed\n" );

    ret = HeapValidate( GetProcessHeap(), 0, p );
    ok( ret, "HeapValidate failed\n" );

    size = HeapSize( GetProcessHeap(), 0, p );
    ok( size == large_size, "Wrong size %lu\n", size );

    ok( p[large_size - 2] == 0, "wrong data %x\n", p[large_size - 2] );
    ok( p[large_size - 1] == 0, "wrong data %x\n", p[large_size - 1] );

    if (flags & HEAP_TAIL_CHECKING_ENABLED)
    {
        /* Windows doesn't do tail checking on large blocks */
        ok( p[large_size] == 0xab || broken(p[large_size] == 0), "wrong data %x\n", p[large_size] );
        ok( p[large_size+1] == 0xab || broken(p[large_size+1] == 0), "wrong data %x\n", p[large_size+1] );
        ok( p[large_size+2] == 0xab || broken(p[large_size+2] == 0), "wrong data %x\n", p[large_size+2] );
        if (p[large_size] == 0xab)
        {
            p[large_size] = 0xcc;
            ret = HeapValidate( GetProcessHeap(), 0, p );
            ok( !ret, "HeapValidate succeeded\n" );

            /* other calls only check when HEAP_VALIDATE is set */
            if (flags & HEAP_VALIDATE)
            {
                size = HeapSize( GetProcessHeap(), 0, p );
                ok( size == ~(SIZE_T)0, "Wrong size %lu\n", size );

                p2 = HeapReAlloc( GetProcessHeap(), 0, p, large_size - 3 );
                ok( p2 == NULL, "HeapReAlloc succeeded\n" );

                ret = HeapFree( GetProcessHeap(), 0, p );
                ok( !ret, "HeapFree succeeded\n" );
            }
            p[large_size] = 0xab;
        }
    }

    ret = HeapFree( GetProcessHeap(), 0, p );
    ok( ret, "HeapFree failed\n" );

    /* test block sizes when tail checking */
    if (flags & HEAP_TAIL_CHECKING_ENABLED)
    {
        for (size = 0; size < 64; size++)
        {
            p = HeapAlloc( GetProcessHeap(), 0, size );
            for (i = 0; i < 32; i++) if (p[size + i] != 0xab) break;
            ok( i >= 8, "only %lu tail bytes for size %lu\n", i, size );
            HeapFree( GetProcessHeap(), 0, p );
        }
    }
}