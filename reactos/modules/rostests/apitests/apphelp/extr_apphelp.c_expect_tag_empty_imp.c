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
struct TYPE_3__ {scalar_t__ type; scalar_t__ flags; scalar_t__ qwattr; } ;
typedef  int /*<<< orphan*/  TAG ;
typedef  TYPE_1__* PATTRINFO ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ TAG_NULL ; 
 size_t find_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winetest_ok (int,char*,size_t,scalar_t__) ; 

__attribute__((used)) static void expect_tag_empty_imp(PATTRINFO pattr, TAG tag)
{
    DWORD num = find_tag(tag);
    PATTRINFO p;

    if (num == ~0)
        return;

    p = &pattr[num];
    winetest_ok(p->type == TAG_NULL, "expected entry #%d to be TAG_NULL, was %x\n", num, p->type);
    winetest_ok(p->flags == 0, "expected entry #%d to be 0, was %d\n", num, p->flags);
    winetest_ok(p->qwattr == 0, "expected entry #%d to be 0, was 0x%I64x\n", num, p->qwattr);
}