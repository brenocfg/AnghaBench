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
struct TYPE_3__ {scalar_t__ ct; scalar_t__ buf; int /*<<< orphan*/ * bp; int /*<<< orphan*/ * end; int /*<<< orphan*/ * start; } ;
typedef  TYPE_1__ opj_bio_t ;
typedef  int OPJ_UINT32 ;
typedef  int /*<<< orphan*/  OPJ_BYTE ;

/* Variables and functions */

void opj_bio_init_dec(opj_bio_t *bio, OPJ_BYTE *bp, OPJ_UINT32 len)
{
    bio->start = bp;
    bio->end = bp + len;
    bio->bp = bp;
    bio->buf = 0;
    bio->ct = 0;
}