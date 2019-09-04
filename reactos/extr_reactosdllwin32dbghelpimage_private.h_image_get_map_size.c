#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct image_section_map {TYPE_1__* fmap; } ;
struct TYPE_2__ {int modtype; } ;

/* Variables and functions */
#define  DMT_ELF 130 
#define  DMT_MACHO 129 
#define  DMT_PE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int elf_get_map_size (struct image_section_map const*) ; 
 int macho_get_map_size (struct image_section_map const*) ; 
 int pe_get_map_size (struct image_section_map const*) ; 

__attribute__((used)) static inline unsigned image_get_map_size(const struct image_section_map* ism)
{
    if (!ism->fmap) return 0;
    switch (ism->fmap->modtype)
    {
#ifndef DBGHELP_STATIC_LIB
    case DMT_ELF:   return elf_get_map_size(ism);
    case DMT_MACHO: return macho_get_map_size(ism);
#endif
    case DMT_PE:    return pe_get_map_size(ism);
    default: assert(0); return 0;
    }
}