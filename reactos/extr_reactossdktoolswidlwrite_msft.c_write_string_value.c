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
typedef  int /*<<< orphan*/  len ;

/* Variables and functions */
 size_t MSFT_SEG_CUSTDATA ; 
 unsigned short VT_BSTR ; 
 int ctl2_alloc_segment (TYPE_1__*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,...) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void write_string_value(msft_typelib_t *typelib, int *out, const char *value)
{
    int len = strlen(value), seg_len = (len + 6 + 3) & ~0x3;
    int offset = ctl2_alloc_segment(typelib, MSFT_SEG_CUSTDATA, seg_len, 0);
    *((unsigned short *)&typelib->typelib_segment_data[MSFT_SEG_CUSTDATA][offset]) = VT_BSTR;
    memcpy(&typelib->typelib_segment_data[MSFT_SEG_CUSTDATA][offset+2], &len, sizeof(len));
    memcpy(&typelib->typelib_segment_data[MSFT_SEG_CUSTDATA][offset+6], value, len);
    len += 6;
    while(len < seg_len) {
        *((char *)&typelib->typelib_segment_data[MSFT_SEG_CUSTDATA][offset+len]) = 0x57;
        len++;
    }
    *out = offset;
}