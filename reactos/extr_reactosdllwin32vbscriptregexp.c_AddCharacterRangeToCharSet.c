#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_4__ {int* bits; } ;
struct TYPE_5__ {int length; TYPE_1__ u; } ;
typedef  TYPE_2__ RECharSet ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
AddCharacterRangeToCharSet(RECharSet *cs, UINT c1, UINT c2)
{
    UINT i;

    UINT byteIndex1 = c1 >> 3;
    UINT byteIndex2 = c2 >> 3;

    assert(c2 <= cs->length && c1 <= c2);

    c1 &= 0x7;
    c2 &= 0x7;

    if (byteIndex1 == byteIndex2) {
        cs->u.bits[byteIndex1] |= ((BYTE)0xFF >> (7 - (c2 - c1))) << c1;
    } else {
        cs->u.bits[byteIndex1] |= 0xFF << c1;
        for (i = byteIndex1 + 1; i < byteIndex2; i++)
            cs->u.bits[i] = 0xFF;
        cs->u.bits[byteIndex2] |= (BYTE)0xFF >> (7 - c2);
    }
}