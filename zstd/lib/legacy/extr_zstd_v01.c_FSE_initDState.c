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
struct TYPE_5__ {int /*<<< orphan*/  const* table; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  tableLog; } ;
typedef  TYPE_1__ FSE_DTableHeader ;
typedef  int /*<<< orphan*/  FSE_DTable ;
typedef  int /*<<< orphan*/  FSE_DStream_t ;
typedef  TYPE_2__ FSE_DState_t ;

/* Variables and functions */
 int /*<<< orphan*/  FSE_readBits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSE_reloadDStream (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void FSE_initDState(FSE_DState_t* DStatePtr, FSE_DStream_t* bitD, const FSE_DTable* dt)
{
    const void* ptr = dt;
    const FSE_DTableHeader* const DTableH = (const FSE_DTableHeader*)ptr;
    DStatePtr->state = FSE_readBits(bitD, DTableH->tableLog);
    FSE_reloadDStream(bitD);
    DStatePtr->table = dt + 1;
}