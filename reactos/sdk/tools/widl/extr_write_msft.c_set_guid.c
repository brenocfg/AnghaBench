#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int posguid; } ;
struct TYPE_12__ {TYPE_2__ typelib_header; TYPE_1__* typelib; } ;
typedef  TYPE_4__ msft_typelib_t ;
struct TYPE_13__ {int hreftype; int next_hash; void* guid; } ;
struct TYPE_11__ {int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  attrs; } ;
typedef  TYPE_5__ MSFT_GuidEntry ;
typedef  void* GUID ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_UUID ; 
 int ctl2_alloc_guid (TYPE_4__*,TYPE_5__*) ; 
 void* get_attrp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_guid(msft_typelib_t *typelib)
{
    MSFT_GuidEntry guidentry;
    int offset;
    void *ptr;
    GUID guid = {0,0,0,{0,0,0,0,0,0}};

    guidentry.guid = guid;
    guidentry.hreftype = -2;
    guidentry.next_hash = -1;

    ptr = get_attrp( typelib->typelib->attrs, ATTR_UUID );
    if (ptr) guidentry.guid = *(GUID *)ptr;

    offset = ctl2_alloc_guid(typelib, &guidentry);
    typelib->typelib_header.posguid = offset;

    return;
}