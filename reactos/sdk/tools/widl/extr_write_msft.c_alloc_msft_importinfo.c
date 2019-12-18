#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  nimpinfos; } ;
struct TYPE_11__ {int /*<<< orphan*/ ** typelib_segment_data; TYPE_1__ typelib_header; TYPE_2__* typelib_segdir; } ;
typedef  TYPE_3__ msft_typelib_t ;
struct TYPE_12__ {int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {int length; } ;
typedef  TYPE_4__ MSFT_ImpInfo ;

/* Variables and functions */
 size_t MSFT_SEG_IMPORTINFO ; 
 int ctl2_alloc_segment (TYPE_3__*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,TYPE_4__*,int) ; 

__attribute__((used)) static int alloc_msft_importinfo(
        msft_typelib_t *typelib,   /* [I] The type library to allocate in. */
        MSFT_ImpInfo *impinfo)     /* [I] The import information to store. */
{
    int offset;
    MSFT_ImpInfo *impinfo_space;

    for (offset = 0;
	 offset < typelib->typelib_segdir[MSFT_SEG_IMPORTINFO].length;
	 offset += sizeof(MSFT_ImpInfo)) {
	if (!memcmp(&(typelib->typelib_segment_data[MSFT_SEG_IMPORTINFO][offset]),
		    impinfo, sizeof(MSFT_ImpInfo))) {
	    return offset;
	}
    }

    impinfo->flags |= typelib->typelib_header.nimpinfos++;

    offset = ctl2_alloc_segment(typelib, MSFT_SEG_IMPORTINFO, sizeof(MSFT_ImpInfo), 0);

    impinfo_space = (void *)(typelib->typelib_segment_data[MSFT_SEG_IMPORTINFO] + offset);
    *impinfo_space = *impinfo;

    return offset;
}