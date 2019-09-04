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
struct TYPE_3__ {scalar_t__ oStart; scalar_t__ length; scalar_t__ pos; } ;
typedef  TYPE_1__ TLBContext ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 scalar_t__ DO_NOT_SEEK ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TLB_abort () ; 

__attribute__((used)) static inline void MSFT_Seek(TLBContext *pcx, LONG where)
{
    if (where != DO_NOT_SEEK)
    {
        where += pcx->oStart;
        if (where > pcx->length)
        {
            /* FIXME */
            ERR("seek beyond end (%d/%d)\n", where, pcx->length );
            TLB_abort();
        }
        pcx->pos = where;
    }
}