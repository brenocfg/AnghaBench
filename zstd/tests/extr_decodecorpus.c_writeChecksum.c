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
struct TYPE_3__ {int /*<<< orphan*/ * data; scalar_t__ srcStart; scalar_t__ src; } ;
typedef  TYPE_1__ frame_t ;
typedef  scalar_t__ U64 ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,unsigned int) ; 
 int /*<<< orphan*/  MEM_writeLE32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ XXH64 (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void writeChecksum(frame_t* frame)
{
    /* write checksum so implementations can verify their output */
    U64 digest = XXH64(frame->srcStart, (BYTE*)frame->src-(BYTE*)frame->srcStart, 0);
    DISPLAYLEVEL(3, "  checksum: %08x\n", (unsigned)digest);
    MEM_writeLE32(frame->data, (U32)digest);
    frame->data = (BYTE*)frame->data + 4;
}