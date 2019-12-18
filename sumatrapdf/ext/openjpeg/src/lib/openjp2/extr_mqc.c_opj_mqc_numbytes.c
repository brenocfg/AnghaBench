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
typedef  int ptrdiff_t ;
struct TYPE_3__ {int bp; int start; } ;
typedef  TYPE_1__ opj_mqc_t ;
typedef  int /*<<< orphan*/  OPJ_UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

OPJ_UINT32 opj_mqc_numbytes(opj_mqc_t *mqc)
{
    const ptrdiff_t diff = mqc->bp - mqc->start;
#if 0
    assert(diff <= 0xffffffff && diff >= 0);   /* UINT32_MAX */
#endif
    return (OPJ_UINT32)diff;
}