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
struct TYPE_3__ {int /*<<< orphan*/ * vals; } ;
typedef  TYPE_1__ paramValues_t ;
typedef  size_t U32 ;

/* Variables and functions */
 int /*<<< orphan*/  BOUNDCHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t NUM_PARAMS ; 
 int /*<<< orphan*/ * maxtable ; 
 int /*<<< orphan*/ * mintable ; 

__attribute__((used)) static int paramValid(const paramValues_t paramTarget)
{
    U32 i;
    for(i = 0; i < NUM_PARAMS; i++) {
        BOUNDCHECK(paramTarget.vals[i], mintable[i], maxtable[i]);
    }
    return 1;
}