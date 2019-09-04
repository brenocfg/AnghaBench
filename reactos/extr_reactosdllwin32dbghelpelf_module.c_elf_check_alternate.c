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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ModuleName; int /*<<< orphan*/  LoadedImageName; } ;
struct module {TYPE_1__ module; } ;
struct image_section_map {int dummy; } ;
struct image_file_map {int dummy; } ;
typedef  int DWORD_PTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int const* IMAGE_NO_MAP ; 
 int const NT_GNU_BUILD_ID ; 
 int /*<<< orphan*/  SHT_NULL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ elf_find_section (struct image_file_map*,char*,int /*<<< orphan*/ ,struct image_section_map*) ; 
 scalar_t__ elf_locate_build_id_target (struct image_file_map*,int /*<<< orphan*/  const*,int const) ; 
 scalar_t__ elf_locate_debug_link (struct image_file_map*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ image_map_section (struct image_section_map*) ; 
 int /*<<< orphan*/  image_unmap_section (struct image_section_map*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static BOOL elf_check_alternate(struct image_file_map* fmap, const struct module* module)
{
    BOOL ret = FALSE;
    BOOL found = FALSE;
    struct image_section_map buildid_sect, debuglink_sect;

    /* if present, add the .gnu_debuglink file as an alternate to current one */
    if (elf_find_section(fmap, ".note.gnu.build-id", SHT_NULL, &buildid_sect))
    {
        const uint32_t* note;

        found = TRUE;
        note = (const uint32_t*)image_map_section(&buildid_sect);
        if (note != IMAGE_NO_MAP)
        {
            /* the usual ELF note structure: name-size desc-size type <name> <desc> */
            if (note[2] == NT_GNU_BUILD_ID)
            {
                ret = elf_locate_build_id_target(fmap, (const BYTE*)(note + 3 + ((note[0] + 3) >> 2)), note[1]);
            }
        }
        image_unmap_section(&buildid_sect);
    }
    /* if present, add the .gnu_debuglink file as an alternate to current one */
    if (!ret && elf_find_section(fmap, ".gnu_debuglink", SHT_NULL, &debuglink_sect))
    {
        const char* dbg_link;

        found = TRUE;
        dbg_link = (const char*)image_map_section(&debuglink_sect);
        if (dbg_link != IMAGE_NO_MAP)
        {
            /* The content of a debug link section is:
             * 1/ a NULL terminated string, containing the file name for the
             *    debug info
             * 2/ padding on 4 byte boundary
             * 3/ CRC of the linked ELF file
             */
            DWORD crc = *(const DWORD*)(dbg_link + ((DWORD_PTR)(strlen(dbg_link) + 4) & ~3));
            ret = elf_locate_debug_link(fmap, dbg_link, module->module.LoadedImageName, crc);
            if (!ret)
                WARN("Couldn't load linked debug file for %s\n",
                     debugstr_w(module->module.ModuleName));
        }
        image_unmap_section(&debuglink_sect);
    }
    return found ? ret : TRUE;
}