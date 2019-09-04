#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct image_section_map {int dummy; } ;
struct image_file_map {int modtype; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  DMT_ELF 130 
#define  DMT_MACHO 129 
#define  DMT_PE 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SHT_NULL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_find_section (struct image_file_map*,char const*,int /*<<< orphan*/ ,struct image_section_map*) ; 
 int /*<<< orphan*/  macho_find_section (struct image_file_map*,int /*<<< orphan*/ *,char const*,struct image_section_map*) ; 
 int /*<<< orphan*/  pe_find_section (struct image_file_map*,char const*,struct image_section_map*) ; 

__attribute__((used)) static inline BOOL image_find_section(struct image_file_map* fmap, const char* name,
                                      struct image_section_map* ism)
{
    switch (fmap->modtype)
    {
#ifndef DBGHELP_STATIC_LIB
    case DMT_ELF:   return elf_find_section(fmap, name, SHT_NULL, ism);
    case DMT_MACHO: return macho_find_section(fmap, NULL, name, ism);
#endif
    case DMT_PE:    return pe_find_section(fmap, name, ism);
    default: assert(0); return FALSE;
    }
}