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
typedef  int USHORT ;
typedef  int SHORT ;
typedef  int /*<<< orphan*/  IMAGE_BASE_RELOCATION ;
typedef  int DWORD ;

/* Variables and functions */
 int IMAGE_REL_BASED_HIGH ; 
 int IMAGE_REL_BASED_HIGHLOW ; 
 int IMAGE_REL_BASED_LOW ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/ * pLdrProcessRelocationBlock (int*,int,int*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_LdrProcessRelocationBlock(void)
{
    IMAGE_BASE_RELOCATION *ret;
    USHORT reloc;
    DWORD addr32;
    SHORT addr16;

    if(!pLdrProcessRelocationBlock) {
        win_skip("LdrProcessRelocationBlock not available\n");
        return;
    }

    addr32 = 0x50005;
    reloc = IMAGE_REL_BASED_HIGHLOW<<12;
    ret = pLdrProcessRelocationBlock(&addr32, 1, &reloc, 0x500050);
    ok((USHORT*)ret == &reloc+1, "ret = %p, expected %p\n", ret, &reloc+1);
    ok(addr32 == 0x550055, "addr32 = %x, expected 0x550055\n", addr32);

    addr16 = 0x505;
    reloc = IMAGE_REL_BASED_HIGH<<12;
    ret = pLdrProcessRelocationBlock(&addr16, 1, &reloc, 0x500060);
    ok((USHORT*)ret == &reloc+1, "ret = %p, expected %p\n", ret, &reloc+1);
    ok(addr16 == 0x555, "addr16 = %x, expected 0x555\n", addr16);

    addr16 = 0x505;
    reloc = IMAGE_REL_BASED_LOW<<12;
    ret = pLdrProcessRelocationBlock(&addr16, 1, &reloc, 0x500060);
    ok((USHORT*)ret == &reloc+1, "ret = %p, expected %p\n", ret, &reloc+1);
    ok(addr16 == 0x565, "addr16 = %x, expected 0x565\n", addr16);
}