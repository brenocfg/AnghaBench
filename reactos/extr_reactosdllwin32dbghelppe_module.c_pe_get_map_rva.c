#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct image_section_map {size_t sidx; TYPE_7__* fmap; } ;
struct TYPE_8__ {size_t NumberOfSections; } ;
struct TYPE_9__ {TYPE_1__ FileHeader; } ;
struct TYPE_12__ {TYPE_4__* sect; TYPE_2__ ntheader; } ;
struct TYPE_13__ {TYPE_5__ pe; } ;
struct TYPE_14__ {TYPE_6__ u; } ;
struct TYPE_10__ {int /*<<< orphan*/  VirtualAddress; } ;
struct TYPE_11__ {TYPE_3__ shdr; } ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */

DWORD_PTR pe_get_map_rva(const struct image_section_map* ism)
{
    if (ism->sidx < 0 || ism->sidx >= ism->fmap->u.pe.ntheader.FileHeader.NumberOfSections)
        return 0;
    return ism->fmap->u.pe.sect[ism->sidx].shdr.VirtualAddress;
}