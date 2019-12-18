#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct CPpmdRAR_RangeDec {int Code; int Range; TYPE_1__* Stream; scalar_t__ Low; } ;
struct TYPE_2__ {int (* Read ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static void PpmdRAR_RangeDec_Init(struct CPpmdRAR_RangeDec *p)
{
    int i;
    p->Code = 0;
    p->Low = 0;
    p->Range = 0xFFFFFFFF;
    for (i = 0; i < 4; i++) {
        p->Code = (p->Code << 8) | p->Stream->Read(p->Stream);
    }
}