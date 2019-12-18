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
struct TYPE_3__ {int cfFormat; int dwAspect; int lindex; int tymed; int /*<<< orphan*/  ptd; } ;
typedef  TYPE_1__ FORMATETC ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static inline char *dump_fmtetc(FORMATETC *fmt)
{
    static char buf[100];

    sprintf(buf, "cf %04x ptd %p aspect %x lindex %d tymed %x",
             fmt->cfFormat, fmt->ptd, fmt->dwAspect, fmt->lindex, fmt->tymed);
    return buf;
}