#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int A; scalar_t__ CT; int C; } ;
typedef  TYPE_1__ Jbig2ArithState ;

/* Variables and functions */
 int /*<<< orphan*/  jbig2_arith_bytein (TYPE_1__*) ; 

__attribute__((used)) static void
jbig2_arith_renormd(Jbig2ArithState *as)
{
    /* Figure E.18 */
    do {
        if (as->CT == 0)
            jbig2_arith_bytein(as);
        as->A <<= 1;
        as->C <<= 1;
        as->CT--;
    } while ((as->A & 0x8000) == 0);
}