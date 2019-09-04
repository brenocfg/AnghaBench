#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct image_section_map {size_t sidx; TYPE_6__* fmap; } ;
struct TYPE_11__ {size_t NumberOfSections; } ;
struct TYPE_10__ {TYPE_5__ FileHeader; } ;
struct TYPE_8__ {TYPE_1__* sect; TYPE_4__ ntheader; } ;
struct TYPE_9__ {TYPE_2__ pe; } ;
struct TYPE_12__ {TYPE_3__ u; } ;
struct TYPE_7__ {scalar_t__ mapped; } ;

/* Variables and functions */
 scalar_t__ IMAGE_NO_MAP ; 
 int /*<<< orphan*/  pe_unmap_full (TYPE_6__*) ; 

void pe_unmap_section(struct image_section_map* ism)
{
    if (ism->sidx >= 0 && ism->sidx < ism->fmap->u.pe.ntheader.FileHeader.NumberOfSections &&
        ism->fmap->u.pe.sect[ism->sidx].mapped != IMAGE_NO_MAP)
    {
        pe_unmap_full(ism->fmap);
        ism->fmap->u.pe.sect[ism->sidx].mapped = IMAGE_NO_MAP;
    }
}