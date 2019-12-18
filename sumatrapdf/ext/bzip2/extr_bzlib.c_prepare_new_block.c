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
struct TYPE_3__ {int /*<<< orphan*/  blockNo; int /*<<< orphan*/ * inUse; int /*<<< orphan*/  blockCRC; scalar_t__ state_out_pos; scalar_t__ numZ; scalar_t__ nblock; } ;
typedef  int Int32 ;
typedef  TYPE_1__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  BZ_INITIALISE_CRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  False ; 

__attribute__((used)) static
void prepare_new_block ( EState* s )
{
   Int32 i;
   s->nblock = 0;
   s->numZ = 0;
   s->state_out_pos = 0;
   BZ_INITIALISE_CRC ( s->blockCRC );
   for (i = 0; i < 256; i++) s->inUse[i] = False;
   s->blockNo++;
}