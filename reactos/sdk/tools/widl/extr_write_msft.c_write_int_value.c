#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ ** typelib_segment_data; } ;
typedef  TYPE_1__ msft_typelib_t ;

/* Variables and functions */
 size_t MSFT_SEG_CUSTDATA ; 
 int ctl2_alloc_segment (TYPE_1__*,size_t,int,int /*<<< orphan*/ ) ; 
 unsigned int get_ulong_val (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void write_int_value(msft_typelib_t *typelib, int *out, int vt, int value)
{
    const unsigned int lv = get_ulong_val(value, vt);
    if ((lv & 0x3ffffff) == lv) {
        *out = 0x80000000;
        *out |= vt << 26;
        *out |= lv;
    } else {
        int offset = ctl2_alloc_segment(typelib, MSFT_SEG_CUSTDATA, 8, 0);
        *((unsigned short *)&typelib->typelib_segment_data[MSFT_SEG_CUSTDATA][offset]) = vt;
        memcpy(&typelib->typelib_segment_data[MSFT_SEG_CUSTDATA][offset+2], &value, 4);
        *((unsigned short *)&typelib->typelib_segment_data[MSFT_SEG_CUSTDATA][offset+6]) = 0x5757;
        *out = offset;
    }
}