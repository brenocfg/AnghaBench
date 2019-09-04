#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int dispatchpos; } ;
struct TYPE_15__ {TYPE_2__ typelib_header; } ;
typedef  TYPE_3__ msft_typelib_t ;
struct TYPE_17__ {int hreftype; int next_hash; void* guid; } ;
struct TYPE_16__ {int flags; int oImpFile; int oGuid; } ;
struct TYPE_13__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
typedef  TYPE_4__ MSFT_ImpInfo ;
typedef  TYPE_5__ MSFT_GuidEntry ;
typedef  void* GUID ;

/* Variables and functions */
 int MSFT_IMPINFO_OFFSET_IS_GUID ; 
 int TKIND_INTERFACE ; 
 int alloc_importfile (TYPE_3__*,int,int,int /*<<< orphan*/ ,char*) ; 
 int alloc_msft_importinfo (TYPE_3__*,TYPE_4__*) ; 
 int ctl2_alloc_guid (TYPE_3__*,TYPE_5__*) ; 
 int ctl2_find_guid (TYPE_3__*,int,void**) ; 
 int ctl2_hash_guid (void**) ; 

__attribute__((used)) static void add_dispatch(msft_typelib_t *typelib)
{
    int guid_offset, impfile_offset, hash_key;
    MSFT_GuidEntry guidentry;
    MSFT_ImpInfo impinfo;
    GUID stdole =        {0x00020430,0x0000,0x0000,{0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
    GUID iid_idispatch = {0x00020400,0x0000,0x0000,{0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

    if(typelib->typelib_header.dispatchpos != -1) return;

    guidentry.guid = stdole;
    guidentry.hreftype = 2;
    guidentry.next_hash = -1;
    hash_key = ctl2_hash_guid(&guidentry.guid);
    guid_offset = ctl2_find_guid(typelib, hash_key, &guidentry.guid);
    if (guid_offset == -1)
        guid_offset = ctl2_alloc_guid(typelib, &guidentry);
    impfile_offset = alloc_importfile(typelib, guid_offset, 2, 0, "stdole2.tlb");

    guidentry.guid = iid_idispatch;
    guidentry.hreftype = 1;
    guidentry.next_hash = -1;
    impinfo.flags = TKIND_INTERFACE << 24 | MSFT_IMPINFO_OFFSET_IS_GUID;
    impinfo.oImpFile = impfile_offset;
    hash_key = ctl2_hash_guid(&guidentry.guid);
    guid_offset = ctl2_find_guid(typelib, hash_key, &guidentry.guid);
    if (guid_offset == -1)
        guid_offset = ctl2_alloc_guid(typelib, &guidentry);
    impinfo.oGuid = guid_offset;
    typelib->typelib_header.dispatchpos = alloc_msft_importinfo(typelib, &impinfo) | 0x01;
}