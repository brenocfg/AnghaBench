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
struct TYPE_4__ {scalar_t__* rep; } ;
typedef  TYPE_1__ repcodes_t ;
typedef  int /*<<< orphan*/  newReps ;
typedef  scalar_t__ U32 ;

/* Variables and functions */
 scalar_t__ const ZSTD_REP_MOVE ; 
 scalar_t__ const ZSTD_REP_NUM ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,scalar_t__ const*,int) ; 

__attribute__((used)) static repcodes_t ZSTD_updateRep(U32 const rep[3], U32 const offset, U32 const ll0)
{
    repcodes_t newReps;
    if (offset >= ZSTD_REP_NUM) {  /* full offset */
        newReps.rep[2] = rep[1];
        newReps.rep[1] = rep[0];
        newReps.rep[0] = offset - ZSTD_REP_MOVE;
    } else {   /* repcode */
        U32 const repCode = offset + ll0;
        if (repCode > 0) {  /* note : if repCode==0, no change */
            U32 const currentOffset = (repCode==ZSTD_REP_NUM) ? (rep[0] - 1) : rep[repCode];
            newReps.rep[2] = (repCode >= 2) ? rep[1] : rep[2];
            newReps.rep[1] = rep[0];
            newReps.rep[0] = currentOffset;
        } else {   /* repCode == 0 */
            memcpy(&newReps, rep, sizeof(newReps));
        }
    }
    return newReps;
}