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
typedef  scalar_t__ U32 ;
struct TYPE_3__ {int /*<<< orphan*/  bitsConsumed; } ;
typedef  TYPE_1__ FSE_DStream_t ;

/* Variables and functions */

__attribute__((used)) static void FSE_skipBits(FSE_DStream_t* bitD, U32 nbBits)
{
    bitD->bitsConsumed += nbBits;
}