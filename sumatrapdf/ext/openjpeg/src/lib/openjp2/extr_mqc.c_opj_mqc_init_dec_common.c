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
struct TYPE_3__ {int* start; int* end; int* bp; int /*<<< orphan*/  backup; } ;
typedef  TYPE_1__ opj_mqc_t ;
typedef  scalar_t__ OPJ_UINT32 ;
typedef  int OPJ_BYTE ;

/* Variables and functions */
 scalar_t__ OPJ_COMMON_CBLK_DATA_EXTRA ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,scalar_t__) ; 

__attribute__((used)) static void opj_mqc_init_dec_common(opj_mqc_t *mqc,
                                    OPJ_BYTE *bp,
                                    OPJ_UINT32 len,
                                    OPJ_UINT32 extra_writable_bytes)
{
    (void)extra_writable_bytes;

    assert(extra_writable_bytes >= OPJ_COMMON_CBLK_DATA_EXTRA);
    mqc->start = bp;
    mqc->end = bp + len;
    /* Insert an artificial 0xFF 0xFF marker at end of the code block */
    /* data so that the bytein routines stop on it. This saves us comparing */
    /* the bp and end pointers */
    /* But before inserting it, backup th bytes we will overwrite */
    memcpy(mqc->backup, mqc->end, OPJ_COMMON_CBLK_DATA_EXTRA);
    mqc->end[0] = 0xFF;
    mqc->end[1] = 0xFF;
    mqc->bp = bp;
}