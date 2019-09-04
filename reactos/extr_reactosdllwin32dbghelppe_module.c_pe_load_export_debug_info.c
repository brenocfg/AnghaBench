#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct process {int dummy; } ;
struct TYPE_15__ {char BaseOfImage; scalar_t__ SymType; } ;
struct module {TYPE_5__ module; TYPE_3__** format_info; } ;
struct image_file_map {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  size_t WORD ;
struct TYPE_17__ {char const AddressOfFunctions; char const AddressOfNameOrdinals; char const AddressOfNames; unsigned int NumberOfNames; unsigned int NumberOfFunctions; int Base; } ;
struct TYPE_14__ {char const AddressOfEntryPoint; } ;
struct TYPE_16__ {TYPE_4__ OptionalHeader; } ;
struct TYPE_12__ {TYPE_1__* pe_info; } ;
struct TYPE_13__ {TYPE_2__ u; } ;
struct TYPE_11__ {struct image_file_map fmap; } ;
typedef  TYPE_6__ IMAGE_NT_HEADERS ;
typedef  TYPE_7__ IMAGE_EXPORT_DIRECTORY ;
typedef  char DWORD_PTR ;
typedef  char const DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t DFI_PE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IMAGE_DIRECTORY_ENTRY_EXPORT ; 
 TYPE_7__* RtlImageDirectoryEntryToData (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 char* RtlImageRvaToVa (TYPE_6__*,void*,char const,int /*<<< orphan*/ *) ; 
 int SYMOPT_NO_PUBLICS ; 
 scalar_t__ SymDeferred ; 
 scalar_t__ SymExport ; 
 int /*<<< orphan*/  TRUE ; 
 int dbghelp_options ; 
 void* pe_map_full (struct image_file_map*,TYPE_6__**) ; 
 int /*<<< orphan*/  pe_unmap_full (struct image_file_map*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  symt_new_public (struct module*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const,int) ; 

__attribute__((used)) static BOOL pe_load_export_debug_info(const struct process* pcs, struct module* module)
{
    struct image_file_map*              fmap = &module->format_info[DFI_PE]->u.pe_info->fmap;
    unsigned int 		        i;
    const IMAGE_EXPORT_DIRECTORY* 	exports;
    DWORD			        base = module->module.BaseOfImage;
    DWORD                               size;
    IMAGE_NT_HEADERS*                   nth;
    void*                               mapping;

    if (dbghelp_options & SYMOPT_NO_PUBLICS) return TRUE;

    if (!(mapping = pe_map_full(fmap, &nth))) return FALSE;
#if 0
    /* Add start of DLL (better use the (yet unimplemented) Exe SymTag for this) */
    /* FIXME: module.ModuleName isn't correctly set yet if it's passed in SymLoadModule */
    symt_new_public(module, NULL, module->module.ModuleName, FALSE, base, 1);
#endif
    
    /* Add entry point */
    symt_new_public(module, NULL, "EntryPoint", FALSE,
                    base + nth->OptionalHeader.AddressOfEntryPoint, 1);
#if 0
    /* FIXME: we'd better store addresses linked to sections rather than 
       absolute values */
    IMAGE_SECTION_HEADER*       section;
    /* Add start of sections */
    section = (IMAGE_SECTION_HEADER*)
        ((char*)&nth->OptionalHeader + nth->FileHeader.SizeOfOptionalHeader);
    for (i = 0; i < nth->FileHeader.NumberOfSections; i++, section++) 
    {
	symt_new_public(module, NULL, section->Name, FALSE,
                        RtlImageRvaToVa(nth, mapping, section->VirtualAddress, NULL), 1);
    }
#endif

    /* Add exported functions */
    if ((exports = RtlImageDirectoryEntryToData(mapping, FALSE,
                                                IMAGE_DIRECTORY_ENTRY_EXPORT, &size)))
    {
        const WORD*             ordinals = NULL;
        const DWORD_PTR*	functions = NULL;
        const DWORD*		names = NULL;
        unsigned int		j;
        char			buffer[16];

        functions = RtlImageRvaToVa(nth, mapping, exports->AddressOfFunctions, NULL);
        ordinals  = RtlImageRvaToVa(nth, mapping, exports->AddressOfNameOrdinals, NULL);
        names     = RtlImageRvaToVa(nth, mapping, exports->AddressOfNames, NULL);

        if (functions && ordinals && names)
        {
            for (i = 0; i < exports->NumberOfNames; i++)
            {
                if (!names[i]) continue;
                symt_new_public(module, NULL,
                                RtlImageRvaToVa(nth, mapping, names[i], NULL),
                                FALSE,
                                base + functions[ordinals[i]], 1);
            }

            for (i = 0; i < exports->NumberOfFunctions; i++)
            {
                if (!functions[i]) continue;
                /* Check if we already added it with a name */
                for (j = 0; j < exports->NumberOfNames; j++)
                    if ((ordinals[j] == i) && names[j]) break;
                if (j < exports->NumberOfNames) continue;
                snprintf(buffer, sizeof(buffer), "%d", i + exports->Base);
                symt_new_public(module, NULL, buffer, FALSE, base + (DWORD)functions[i], 1);
            }
        }
    }
    /* no real debug info, only entry points */
    if (module->module.SymType == SymDeferred)
        module->module.SymType = SymExport;
    pe_unmap_full(fmap);

    return TRUE;
}