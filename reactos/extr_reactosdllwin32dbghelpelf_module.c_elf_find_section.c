#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct image_section_map {unsigned int sidx; struct image_file_map* fmap; int /*<<< orphan*/  member_1; struct image_file_map* member_0; } ;
struct TYPE_6__ {unsigned int e_shnum; int /*<<< orphan*/  e_shstrndx; } ;
struct elf_file_map {scalar_t__ shstrtab; struct image_file_map* alternate; TYPE_4__* sect; TYPE_2__ elfhdr; } ;
struct TYPE_5__ {struct elf_file_map elf; } ;
struct image_file_map {TYPE_1__ u; } ;
struct TYPE_7__ {scalar_t__ sh_name; unsigned int sh_type; } ;
struct TYPE_8__ {TYPE_3__ shdr; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IMAGE_NO_MAP ; 
 unsigned int SHT_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ elf_map_section (struct image_section_map*) ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

BOOL elf_find_section(struct image_file_map* _fmap, const char* name,
                      unsigned sht, struct image_section_map* ism)
{
    struct elf_file_map*        fmap;
    unsigned i;

    while (_fmap)
    {
        fmap = &_fmap->u.elf;
        if (fmap->shstrtab == IMAGE_NO_MAP)
        {
            struct image_section_map  hdr_ism = {_fmap, fmap->elfhdr.e_shstrndx};
            if ((fmap->shstrtab = elf_map_section(&hdr_ism)) == IMAGE_NO_MAP) break;
        }
        for (i = 0; i < fmap->elfhdr.e_shnum; i++)
        {
            if (strcmp(fmap->shstrtab + fmap->sect[i].shdr.sh_name, name) == 0 &&
                (sht == SHT_NULL || sht == fmap->sect[i].shdr.sh_type))
            {
                ism->fmap = _fmap;
                ism->sidx = i;
                return TRUE;
            }
        }
        _fmap = fmap->alternate;
    }
    ism->fmap = NULL;
    ism->sidx = -1;
    return FALSE;
}