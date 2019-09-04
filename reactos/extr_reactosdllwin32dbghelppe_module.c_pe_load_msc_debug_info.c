#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct process {int dummy; } ;
struct TYPE_19__ {int /*<<< orphan*/  ModuleName; } ;
struct module {TYPE_4__ module; TYPE_3__** format_info; } ;
struct image_file_map {int dummy; } ;
struct TYPE_24__ {int PointerToRawData; scalar_t__ Type; } ;
struct TYPE_23__ {scalar_t__ DataType; scalar_t__ Data; } ;
struct TYPE_21__ {int Characteristics; int SizeOfOptionalHeader; int /*<<< orphan*/  NumberOfSections; int /*<<< orphan*/  TimeDateStamp; } ;
struct TYPE_20__ {TYPE_10__* DataDirectory; } ;
struct TYPE_22__ {TYPE_6__ FileHeader; TYPE_5__ OptionalHeader; } ;
struct TYPE_17__ {TYPE_1__* pe_info; } ;
struct TYPE_18__ {TYPE_2__ u; } ;
struct TYPE_16__ {struct image_file_map fmap; } ;
struct TYPE_15__ {int Size; int /*<<< orphan*/  VirtualAddress; } ;
typedef  int /*<<< orphan*/  IMAGE_SECTION_HEADER ;
typedef  TYPE_7__ IMAGE_NT_HEADERS ;
typedef  TYPE_8__ IMAGE_DEBUG_MISC ;
typedef  TYPE_9__ IMAGE_DEBUG_DIRECTORY ;
typedef  TYPE_10__ IMAGE_DATA_DIRECTORY ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t DFI_PE ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IMAGE_DEBUG_MISC_EXENAME ; 
 scalar_t__ IMAGE_DEBUG_TYPE_MISC ; 
 int IMAGE_DIRECTORY_ENTRY_DEBUG ; 
 int IMAGE_FILE_DEBUG_STRIPPED ; 
 TYPE_9__* RtlImageRvaToVa (TYPE_7__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pe_load_dbg_file (struct process const*,struct module*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pe_load_debug_directory (struct process const*,struct module*,void*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_9__ const*,int) ; 
 void* pe_map_full (struct image_file_map*,TYPE_7__**) ; 
 int /*<<< orphan*/  pe_unmap_full (struct image_file_map*) ; 

__attribute__((used)) static BOOL pe_load_msc_debug_info(const struct process* pcs, struct module* module)
{
    struct image_file_map*      fmap = &module->format_info[DFI_PE]->u.pe_info->fmap;
    BOOL                        ret = FALSE;
    const IMAGE_DATA_DIRECTORY* dir;
    const IMAGE_DEBUG_DIRECTORY*dbg = NULL;
    int                         nDbg;
    void*                       mapping;
    IMAGE_NT_HEADERS*           nth;

    if (!(mapping = pe_map_full(fmap, &nth))) return FALSE;
    /* Read in debug directory */
    dir = nth->OptionalHeader.DataDirectory + IMAGE_DIRECTORY_ENTRY_DEBUG;
    nDbg = dir->Size / sizeof(IMAGE_DEBUG_DIRECTORY);
    if (!nDbg) goto done;

    dbg = RtlImageRvaToVa(nth, mapping, dir->VirtualAddress, NULL);

#ifdef __REACTOS__
    if (!dbg)
    {
        ERR("Debug directory not found in module %s\n",
            debugstr_w(module->module.ModuleName));
        goto done;
    }
#endif

    /* Parse debug directory */
    if (nth->FileHeader.Characteristics & IMAGE_FILE_DEBUG_STRIPPED)
    {
        /* Debug info is stripped to .DBG file */
        const IMAGE_DEBUG_MISC* misc = (const IMAGE_DEBUG_MISC*)
            ((const char*)mapping + dbg->PointerToRawData);

        if (nDbg != 1 || dbg->Type != IMAGE_DEBUG_TYPE_MISC ||
            misc->DataType != IMAGE_DEBUG_MISC_EXENAME)
        {
            ERR("-Debug info stripped, but no .DBG file in module %s\n",
                debugstr_w(module->module.ModuleName));
        }
        else
        {
            ret = pe_load_dbg_file(pcs, module, (const char*)misc->Data, nth->FileHeader.TimeDateStamp);
        }
    }
    else
    {
        const IMAGE_SECTION_HEADER *sectp = (const IMAGE_SECTION_HEADER*)((const char*)&nth->OptionalHeader + nth->FileHeader.SizeOfOptionalHeader);
        /* Debug info is embedded into PE module */
        ret = pe_load_debug_directory(pcs, module, mapping, sectp,
                                      nth->FileHeader.NumberOfSections, dbg, nDbg);
    }
done:
    pe_unmap_full(fmap);
    return ret;
}