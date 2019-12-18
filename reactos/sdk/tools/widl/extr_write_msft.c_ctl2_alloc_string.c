#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int** typelib_segment_data; TYPE_1__* typelib_segdir; } ;
typedef  TYPE_2__ msft_typelib_t ;
struct TYPE_5__ {int length; } ;

/* Variables and functions */
 size_t MSFT_SEG_STRING ; 
 int ctl2_alloc_segment (TYPE_2__*,size_t,int,int /*<<< orphan*/ ) ; 
 int ctl2_encode_string (char const*,char**) ; 
 int /*<<< orphan*/  memcmp (char*,int*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,int) ; 

__attribute__((used)) static int ctl2_alloc_string(
	msft_typelib_t *typelib,  /* [I] The type library to allocate in. */
	const char *string)       /* [I] The string to store. */
{
    int length;
    int offset;
    unsigned char *string_space;
    char *encoded_string;

    length = ctl2_encode_string(string, &encoded_string);

    for (offset = 0; offset < typelib->typelib_segdir[MSFT_SEG_STRING].length;
	 offset += (((typelib->typelib_segment_data[MSFT_SEG_STRING][offset + 1] << 8) |
	      typelib->typelib_segment_data[MSFT_SEG_STRING][offset + 0]) + 5) & ~3) {
	if (!memcmp(encoded_string, typelib->typelib_segment_data[MSFT_SEG_STRING] + offset, length)) return offset;
    }

    offset = ctl2_alloc_segment(typelib, MSFT_SEG_STRING, length, 0);

    string_space = typelib->typelib_segment_data[MSFT_SEG_STRING] + offset;
    memcpy(string_space, encoded_string, length);

    return offset;
}