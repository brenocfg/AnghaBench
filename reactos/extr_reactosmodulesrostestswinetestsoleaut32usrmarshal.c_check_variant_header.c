#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int clSize; scalar_t__ rpcReserved; int vt; int wReserved1; int wReserved2; int wReserved3; int switch_is; } ;
typedef  TYPE_1__ variant_wire_t ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int ULONG ;
struct TYPE_4__ {int wReserved1; int wReserved2; int wReserved3; } ;
typedef  int DWORD ;

/* Variables and functions */
 int VT_ARRAY ; 
 int VT_TYPEMASK ; 
 TYPE_2__ V_U2 (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static DWORD *check_variant_header(DWORD *wirev, VARIANT *v, ULONG size)
{
    const variant_wire_t *header = (const variant_wire_t*)wirev;
    DWORD switch_is;

    ok(header->clSize == (size + 7) >> 3, "wv[0] %08x, expected %08x\n", header->clSize, (size + 7) >> 3);
    ok(header->rpcReserved == 0, "wv[1] %08x\n", header->rpcReserved);
    ok(header->vt == V_VT(v), "vt %04x expected %04x\n", header->vt, V_VT(v));
    ok(header->wReserved1 == V_U2(v).wReserved1, "res1 %04x expected %04x\n", header->wReserved1, V_U2(v).wReserved1);
    ok(header->wReserved2 == V_U2(v).wReserved2, "res2 %04x expected %04x\n", header->wReserved2, V_U2(v).wReserved2);
    ok(header->wReserved3 == V_U2(v).wReserved3, "res3 %04x expected %04x\n", header->wReserved3, V_U2(v).wReserved3);

    switch_is = V_VT(v);
    if(switch_is & VT_ARRAY)
        switch_is &= ~VT_TYPEMASK;
    ok(header->switch_is == switch_is, "switch_is %08x expected %08x\n", header->switch_is, switch_is);

    return (DWORD*)((unsigned char*)wirev + sizeof(variant_wire_t));
}