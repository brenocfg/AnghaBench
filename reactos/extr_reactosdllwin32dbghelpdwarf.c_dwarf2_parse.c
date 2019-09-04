#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {struct dwarf2_module_info_s* dwarf2_info; } ;
struct module_format {TYPE_7__ u; struct module* module; int /*<<< orphan*/  loc_compute; int /*<<< orphan*/  remove; } ;
struct TYPE_19__ {char CVSig; void* Publics; void* SourceIndexed; void* TypeInfo; void* GlobalSymbols; int /*<<< orphan*/  SymType; int /*<<< orphan*/  ModuleName; } ;
struct module {TYPE_6__ module; struct module_format** format_info; } ;
struct image_section_map {TYPE_5__* fmap; } ;
struct TYPE_14__ {scalar_t__ elf_start; } ;
struct TYPE_15__ {TYPE_1__ elf; } ;
struct image_file_map {scalar_t__ modtype; int addr_size; TYPE_2__ u; } ;
struct elf_thunk_area {int dummy; } ;
struct TYPE_22__ {scalar_t__ address; scalar_t__ size; } ;
struct dwarf2_module_info_s {int word_size; TYPE_9__ eh_frame; TYPE_9__ debug_frame; TYPE_9__ debug_loc; } ;
struct TYPE_21__ {scalar_t__ data; scalar_t__ end_data; scalar_t__ word_size; } ;
typedef  TYPE_8__ dwarf2_traverse_context_t ;
typedef  TYPE_9__ dwarf2_section_t ;
struct TYPE_16__ {scalar_t__ elf_start; } ;
struct TYPE_17__ {TYPE_3__ elf; } ;
struct TYPE_18__ {TYPE_4__ u; } ;
typedef  void* BOOL ;

/* Variables and functions */
 size_t DFI_DWARF ; 
 scalar_t__ DMT_ELF ; 
 void* FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct module_format* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IMAGE_NO_MAP ; 
 int /*<<< orphan*/  SymDia ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf2_fini_section (TYPE_9__*) ; 
 int /*<<< orphan*/  dwarf2_init_section (TYPE_9__*,struct image_file_map*,char*,char*,struct image_section_map*) ; 
 int /*<<< orphan*/  dwarf2_location_compute ; 
 int /*<<< orphan*/  dwarf2_module_remove ; 
 int /*<<< orphan*/  dwarf2_parse_compilation_unit (TYPE_9__*,struct module*,struct elf_thunk_area const*,TYPE_8__*,unsigned long) ; 
 int /*<<< orphan*/  image_unmap_section (struct image_section_map*) ; 
 size_t section_abbrev ; 
 size_t section_debug ; 
 size_t section_line ; 
 int section_max ; 
 size_t section_ranges ; 
 size_t section_string ; 

BOOL dwarf2_parse(struct module* module, unsigned long load_offset,
                  const struct elf_thunk_area* thunks,
                  struct image_file_map* fmap)
{
    dwarf2_section_t    eh_frame, section[section_max];
    dwarf2_traverse_context_t   mod_ctx;
    struct image_section_map    debug_sect, debug_str_sect, debug_abbrev_sect,
                                debug_line_sect, debug_ranges_sect, eh_frame_sect;
    BOOL                ret = TRUE;
    struct module_format* dwarf2_modfmt;

    dwarf2_init_section(&eh_frame,                fmap, ".eh_frame",     NULL,             &eh_frame_sect);
    dwarf2_init_section(&section[section_debug],  fmap, ".debug_info",   ".zdebug_info",   &debug_sect);
    dwarf2_init_section(&section[section_abbrev], fmap, ".debug_abbrev", ".zdebug_abbrev", &debug_abbrev_sect);
    dwarf2_init_section(&section[section_string], fmap, ".debug_str",    ".zdebug_str",    &debug_str_sect);
    dwarf2_init_section(&section[section_line],   fmap, ".debug_line",   ".zdebug_line",   &debug_line_sect);
    dwarf2_init_section(&section[section_ranges], fmap, ".debug_ranges", ".zdebug_ranges", &debug_ranges_sect);

    /* to do anything useful we need either .eh_frame or .debug_info */
    if ((!eh_frame.address || eh_frame.address == IMAGE_NO_MAP) &&
        (!section[section_debug].address || section[section_debug].address == IMAGE_NO_MAP))
    {
        ret = FALSE;
        goto leave;
    }

    if (fmap->modtype == DMT_ELF && debug_sect.fmap)
    {
        /* debug info might have a different base address than .so file
         * when elf file is prelinked after splitting off debug info
         * adjust symbol base addresses accordingly
         */
        load_offset += fmap->u.elf.elf_start - debug_sect.fmap->u.elf.elf_start;
    }

    TRACE("Loading Dwarf2 information for %s\n", debugstr_w(module->module.ModuleName));

    mod_ctx.data = section[section_debug].address;
    mod_ctx.end_data = mod_ctx.data + section[section_debug].size;
    mod_ctx.word_size = 0; /* will be correctly set later on */

    dwarf2_modfmt = HeapAlloc(GetProcessHeap(), 0,
                              sizeof(*dwarf2_modfmt) + sizeof(*dwarf2_modfmt->u.dwarf2_info));
    if (!dwarf2_modfmt)
    {
        ret = FALSE;
        goto leave;
    }
    dwarf2_modfmt->module = module;
    dwarf2_modfmt->remove = dwarf2_module_remove;
    dwarf2_modfmt->loc_compute = dwarf2_location_compute;
    dwarf2_modfmt->u.dwarf2_info = (struct dwarf2_module_info_s*)(dwarf2_modfmt + 1);
    dwarf2_modfmt->u.dwarf2_info->word_size = 0; /* will be correctly set later on */
    dwarf2_modfmt->module->format_info[DFI_DWARF] = dwarf2_modfmt;

    /* As we'll need later some sections' content, we won't unmap these
     * sections upon existing this function
     */
    dwarf2_init_section(&dwarf2_modfmt->u.dwarf2_info->debug_loc,   fmap, ".debug_loc",   ".zdebug_loc",   NULL);
    dwarf2_init_section(&dwarf2_modfmt->u.dwarf2_info->debug_frame, fmap, ".debug_frame", ".zdebug_frame", NULL);
    dwarf2_modfmt->u.dwarf2_info->eh_frame = eh_frame;

    while (mod_ctx.data < mod_ctx.end_data)
    {
        dwarf2_parse_compilation_unit(section, dwarf2_modfmt->module, thunks, &mod_ctx, load_offset);
    }
    dwarf2_modfmt->module->module.SymType = SymDia;
    dwarf2_modfmt->module->module.CVSig = 'D' | ('W' << 8) | ('A' << 16) | ('R' << 24);
    /* FIXME: we could have a finer grain here */
    dwarf2_modfmt->module->module.GlobalSymbols = TRUE;
    dwarf2_modfmt->module->module.TypeInfo = TRUE;
    dwarf2_modfmt->module->module.SourceIndexed = TRUE;
    dwarf2_modfmt->module->module.Publics = TRUE;

    /* set the word_size for eh_frame parsing */
    dwarf2_modfmt->u.dwarf2_info->word_size = fmap->addr_size / 8;

leave:
    dwarf2_fini_section(&section[section_debug]);
    dwarf2_fini_section(&section[section_abbrev]);
    dwarf2_fini_section(&section[section_string]);
    dwarf2_fini_section(&section[section_line]);
    dwarf2_fini_section(&section[section_ranges]);

    image_unmap_section(&debug_sect);
    image_unmap_section(&debug_abbrev_sect);
    image_unmap_section(&debug_str_sect);
    image_unmap_section(&debug_line_sect);
    image_unmap_section(&debug_ranges_sect);
    if (!ret) image_unmap_section(&eh_frame_sect);

    return ret;
}