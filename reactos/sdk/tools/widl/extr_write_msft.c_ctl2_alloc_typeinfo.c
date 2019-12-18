#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nrtypeinfos; } ;
struct TYPE_7__ {int* typelib_typeinfo_offsets; TYPE_1__ typelib_header; scalar_t__* typelib_segment_data; } ;
typedef  TYPE_2__ msft_typelib_t ;
struct TYPE_8__ {int typekind; int memoffset; int res3; int res4; int posguid; int NameOffset; int docstringoffs; int oCustData; int datatype1; int res19; scalar_t__ res18; scalar_t__ datatype2; scalar_t__ size; scalar_t__ cImplTypes; scalar_t__ cbSizeVft; scalar_t__ helpcontext; scalar_t__ helpstringcontext; scalar_t__ version; scalar_t__ flags; scalar_t__ resA; scalar_t__ res9; scalar_t__ res8; scalar_t__ res7; scalar_t__ cElement; scalar_t__ res5; scalar_t__ res2; } ;
typedef  TYPE_3__ MSFT_TypeInfoBase ;

/* Variables and functions */
 size_t MSFT_SEG_TYPEINFO ; 
 int ctl2_alloc_segment (TYPE_2__*,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ctl2_alloc_typeinfo(
	msft_typelib_t *typelib,   /* [I] The type library to allocate in. */
	int nameoffset)            /* [I] The offset of the name for this typeinfo. */
{
    int offset;
    MSFT_TypeInfoBase *typeinfo;

    offset = ctl2_alloc_segment(typelib, MSFT_SEG_TYPEINFO, sizeof(MSFT_TypeInfoBase), 0);

    typelib->typelib_typeinfo_offsets[typelib->typelib_header.nrtypeinfos++] = offset;

    typeinfo = (void *)(typelib->typelib_segment_data[MSFT_SEG_TYPEINFO] + offset);

    typeinfo->typekind = (typelib->typelib_header.nrtypeinfos - 1) << 16;
    typeinfo->memoffset = -1; /* should be EOF if no elements */
    typeinfo->res2 = 0;
    typeinfo->res3 = -1;
    typeinfo->res4 = 3;
    typeinfo->res5 = 0;
    typeinfo->cElement = 0;
    typeinfo->res7 = 0;
    typeinfo->res8 = 0;
    typeinfo->res9 = 0;
    typeinfo->resA = 0;
    typeinfo->posguid = -1;
    typeinfo->flags = 0;
    typeinfo->NameOffset = nameoffset;
    typeinfo->version = 0;
    typeinfo->docstringoffs = -1;
    typeinfo->helpstringcontext = 0;
    typeinfo->helpcontext = 0;
    typeinfo->oCustData = -1;
    typeinfo->cbSizeVft = 0;
    typeinfo->cImplTypes = 0;
    typeinfo->size = 0;
    typeinfo->datatype1 = -1;
    typeinfo->datatype2 = 0;
    typeinfo->res18 = 0;
    typeinfo->res19 = -1;

    return offset;
}