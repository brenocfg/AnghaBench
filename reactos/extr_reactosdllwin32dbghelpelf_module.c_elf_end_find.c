#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct image_section_map {int /*<<< orphan*/  sidx; struct image_file_map* fmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  e_shstrndx; } ;
struct TYPE_5__ {struct image_file_map* alternate; int /*<<< orphan*/  shstrtab; TYPE_1__ elfhdr; } ;
struct TYPE_6__ {TYPE_2__ elf; } ;
struct image_file_map {TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMAGE_NO_MAP ; 
 int /*<<< orphan*/  elf_unmap_section (struct image_section_map*) ; 

__attribute__((used)) static void elf_end_find(struct image_file_map* fmap)
{
    struct image_section_map      ism;

    while (fmap)
    {
        ism.fmap = fmap;
        ism.sidx = fmap->u.elf.elfhdr.e_shstrndx;
        elf_unmap_section(&ism);
        fmap->u.elf.shstrtab = IMAGE_NO_MAP;
        fmap = fmap->u.elf.alternate;
    }
}