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
typedef  int uint32_t ;
struct CPpmdRAR_RangeDec {int Low; int Range; int Code; TYPE_1__* Stream; } ;
typedef  scalar_t__ int32_t ;
typedef  int UInt32 ;
struct TYPE_2__ {int (* Read ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static void Range_Decode_RAR(void *p, UInt32 start, UInt32 size)
{
    struct CPpmdRAR_RangeDec *self = p;
    self->Low += start * self->Range;
    self->Code -= start * self->Range;
    self->Range *= size;
    for (;;) {
        if ((self->Low ^ (self->Low + self->Range)) >= (1 << 24)) {
            if (self->Range >= (1 << 15))
                break;
            self->Range = ((uint32_t)(-(int32_t)self->Low)) & ((1 << 15) - 1);
        }
        self->Code = (self->Code << 8) | self->Stream->Read(self->Stream);
        self->Range <<= 8;
        self->Low <<= 8;
    }
}