#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t* vals; } ;
typedef  TYPE_1__ paramValues_t ;
struct TYPE_7__ {int tableType; int tableLen; int /*<<< orphan*/ * table; int /*<<< orphan*/  varLen; int /*<<< orphan*/  varArray; } ;
typedef  TYPE_2__ memoTable_t ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int NUM_PARAMS ; 
 int XXH64 (size_t**,int,int /*<<< orphan*/ ) ; 
#define  directMap 130 
 size_t memoTableIndDirect (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  noMemo 129 
 size_t strt_ind ; 
#define  xxhashMap 128 

__attribute__((used)) static void memoTableSet(const memoTable_t* memoTableArray, const paramValues_t p, const BYTE value) {
    const memoTable_t mt = memoTableArray[p.vals[strt_ind]];
    switch(mt.tableType) {
        case directMap:
            mt.table[memoTableIndDirect(&p, mt.varArray, mt.varLen)] = value; break;
        case xxhashMap:
            mt.table[(XXH64(&p.vals, sizeof(U32) * NUM_PARAMS, 0) >> 3) % mt.tableLen] = value; break;
        case noMemo:
            break;
    }
}