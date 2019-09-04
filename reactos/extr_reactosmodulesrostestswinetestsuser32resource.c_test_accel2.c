#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cmd; int fVirt; int key; } ;
typedef  int /*<<< orphan*/ * HACCEL ;
typedef  TYPE_1__ ACCEL ;

/* Variables and functions */
 int CopyAcceleratorTableA (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * CreateAcceleratorTableA (TYPE_1__*,int) ; 
 int DestroyAcceleratorTable (int /*<<< orphan*/ *) ; 
 void* FVIRTKEY ; 
 scalar_t__ broken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_accel2(void)
{
    ACCEL ac[2], out[2];
    HACCEL hac;
    int res;

    ac[0].cmd   = 0;
    ac[0].fVirt = 0;
    ac[0].key   = 0;

    ac[1].cmd   = 0;
    ac[1].fVirt = 0;
    ac[1].key   = 0;

    /*
     * crashes on win2k
     * hac = CreateAcceleratorTable( NULL, 1 );
     */

    /* try a zero count */
    hac = CreateAcceleratorTableA( &ac[0], 0 );
    ok( !hac || broken(hac != NULL), /* nt4 */ "fail\n");
    if (!hac) ok( !DestroyAcceleratorTable( hac ), "destroy failed\n");

    /* creating one accelerator should work */
    hac = CreateAcceleratorTableA( &ac[0], 1 );
    ok( hac != NULL , "fail\n");
    ok( 1 == CopyAcceleratorTableA( hac, out, 1 ), "copy failed\n");
    ok( DestroyAcceleratorTable( hac ), "destroy failed\n");

    /* how about two of the same type? */
    hac = CreateAcceleratorTableA( &ac[0], 2);
    ok( hac != NULL , "fail\n");
    res = CopyAcceleratorTableA( hac, NULL, 100 );
    ok( res == 2, "copy null failed %d\n", res);
    res = CopyAcceleratorTableA( hac, NULL, 0 );
    ok( res == 2, "copy null failed %d\n", res);
    res = CopyAcceleratorTableA( hac, NULL, 1 );
    ok( res == 2, "copy null failed %d\n", res);
    ok( 1 == CopyAcceleratorTableA( hac, out, 1 ), "copy 1 failed\n");
    ok( 2 == CopyAcceleratorTableA( hac, out, 2 ), "copy 2 failed\n");
    ok( DestroyAcceleratorTable( hac ), "destroy failed\n");
    /* ok( !memcmp( ac, out, sizeof ac ), "tables different\n"); */

    /* how about two of the same type with a non-zero key? */
    ac[0].key = 0x20;
    ac[1].key = 0x20;
    hac = CreateAcceleratorTableA( &ac[0], 2);
    ok( hac != NULL , "fail\n");
    ok( 2 == CopyAcceleratorTableA( hac, out, 2 ), "copy 2 failed\n");
    ok( DestroyAcceleratorTable( hac ), "destroy failed\n");
    /* ok( !memcmp( ac, out, sizeof ac ), "tables different\n"); */

    /* how about two of the same type with a non-zero virtual key? */
    ac[0].fVirt = FVIRTKEY;
    ac[0].key = 0x40;
    ac[1].fVirt = FVIRTKEY;
    ac[1].key = 0x40;
    hac = CreateAcceleratorTableA( &ac[0], 2);
    ok( hac != NULL , "fail\n");
    ok( 2 == CopyAcceleratorTableA( hac, out, 2 ), "copy 2 failed\n");
    /* ok( !memcmp( ac, out, sizeof ac ), "tables different\n"); */
    ok( DestroyAcceleratorTable( hac ), "destroy failed\n");

    /* how virtual key codes */
    ac[0].fVirt = FVIRTKEY;
    hac = CreateAcceleratorTableA( &ac[0], 1);
    ok( hac != NULL , "fail\n");
    ok( 1 == CopyAcceleratorTableA( hac, out, 2 ), "copy 2 failed\n");
    /* ok( !memcmp( ac, out, sizeof ac/2 ), "tables different\n"); */
    ok( DestroyAcceleratorTable( hac ), "destroy failed\n");

    /* how turning on all bits? */
    ac[0].cmd   = 0xffff;
    ac[0].fVirt = 0xff;
    ac[0].key   = 0xffff;
    hac = CreateAcceleratorTableA( &ac[0], 1);
    ok( hac != NULL , "fail\n");
    ok( 1 == CopyAcceleratorTableA( hac, out, 1 ), "copy 1 failed\n");
    /* ok( memcmp( ac, out, sizeof ac/2 ), "tables not different\n"); */
    ok( out[0].cmd == ac[0].cmd, "cmd modified\n");
    ok( out[0].fVirt == (ac[0].fVirt&0x7f), "fVirt not modified\n");
    ok( out[0].key == ac[0].key, "key modified\n");
    ok( DestroyAcceleratorTable( hac ), "destroy failed\n");

    /* how turning on all bits? */
    memset( ac, 0xff, sizeof ac );
    hac = CreateAcceleratorTableA( &ac[0], 2);
    ok( hac != NULL , "fail\n");
    res = CopyAcceleratorTableA( hac, out, 2 );
    ok( res == 2, "copy 2 failed %d\n", res);
    /* ok( memcmp( ac, out, sizeof ac ), "tables not different\n"); */
    ok( out[0].cmd == ac[0].cmd, "cmd modified\n");
    ok( out[0].fVirt == (ac[0].fVirt&0x7f), "fVirt not modified\n");
    ok( out[0].key == ac[0].key, "key modified\n");
    if (res == 2)
    {
        ok( out[1].cmd == ac[1].cmd, "cmd modified\n");
        ok( out[1].fVirt == (ac[1].fVirt&0x7f), "fVirt not modified\n");
        ok( out[1].key == ac[1].key, "key modified\n");
    }
    ok( DestroyAcceleratorTable( hac ), "destroy failed\n");
}