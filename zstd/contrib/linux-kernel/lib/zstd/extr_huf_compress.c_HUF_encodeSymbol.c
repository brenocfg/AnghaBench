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
typedef  size_t U32 ;
struct TYPE_3__ {int /*<<< orphan*/  nbBits; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ HUF_CElt ;
typedef  int /*<<< orphan*/  BIT_CStream_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_addBitsFast (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void HUF_encodeSymbol(BIT_CStream_t *bitCPtr, U32 symbol, const HUF_CElt *CTable)
{
	BIT_addBitsFast(bitCPtr, CTable[symbol].val, CTable[symbol].nbBits);
}