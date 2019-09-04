#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct symt_compiland {int dummy; } ;
struct TYPE_14__ {void* Publics; void* SourceIndexed; void* TypeInfo; void* GlobalSymbols; void* LineNumbers; int /*<<< orphan*/  SymType; scalar_t__ BaseOfImage; } ;
struct module {TYPE_10__ module; TYPE_3__** format_info; } ;
struct TYPE_20__ {int NumberOfSymbols; int PointerToSymbolTable; int NumberOfSections; } ;
struct TYPE_21__ {TYPE_4__ FileHeader; } ;
struct TYPE_22__ {TYPE_5__ ntheader; } ;
struct TYPE_23__ {TYPE_6__ pe; } ;
struct image_file_map {TYPE_7__ u; } ;
struct TYPE_24__ {int Long; scalar_t__ Short; } ;
struct TYPE_25__ {TYPE_8__ Name; int /*<<< orphan*/  ShortName; } ;
struct TYPE_18__ {TYPE_1__* pe_info; } ;
struct TYPE_19__ {TYPE_2__ u; } ;
struct TYPE_17__ {struct image_file_map fmap; } ;
struct TYPE_16__ {scalar_t__ VirtualAddress; } ;
struct TYPE_15__ {scalar_t__ StorageClass; int SectionNumber; int NumberOfAuxSymbols; scalar_t__ Value; TYPE_9__ N; } ;
typedef  TYPE_11__ IMAGE_SYMBOL ;
typedef  TYPE_12__ IMAGE_SECTION_HEADER ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  void* BOOL ;

/* Variables and functions */
 size_t DFI_PE ; 
 void* FALSE ; 
 TYPE_12__* IMAGE_FIRST_SECTION (int /*<<< orphan*/ ) ; 
 scalar_t__ IMAGE_SYM_CLASS_EXTERNAL ; 
 scalar_t__ IMAGE_SYM_CLASS_FILE ; 
 int /*<<< orphan*/  RtlImageNtHeader (int /*<<< orphan*/ ) ; 
 int SYMOPT_NO_PUBLICS ; 
 int /*<<< orphan*/  SymCoff ; 
 void* TRUE ; 
 int dbghelp_options ; 
 char* memcpy (char*,int /*<<< orphan*/ ,int) ; 
 char* pe_map_full (struct image_file_map*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pe_unmap_full (struct image_file_map*) ; 
 int /*<<< orphan*/  source_new (struct module*,int /*<<< orphan*/ *,char const*) ; 
 struct symt_compiland* symt_new_compiland (struct module*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symt_new_public (struct module*,struct symt_compiland*,char const*,void*,scalar_t__,int) ; 

__attribute__((used)) static BOOL pe_load_coff_symbol_table(struct module* module)
{
    struct image_file_map* fmap = &module->format_info[DFI_PE]->u.pe_info->fmap;
    const IMAGE_SYMBOL* isym;
    int                 i, numsym, naux;
    const char*         strtable;
    char                tmp[9];
    const char*         name;
    const char*         lastfilename = NULL;
    struct symt_compiland*   compiland = NULL;
    const IMAGE_SECTION_HEADER* sect;
    const char*         mapping;

    numsym = fmap->u.pe.ntheader.FileHeader.NumberOfSymbols;
    if (!fmap->u.pe.ntheader.FileHeader.PointerToSymbolTable || !numsym)
        return TRUE;
    if (!(mapping = pe_map_full(fmap, NULL))) return FALSE;
    isym = (const IMAGE_SYMBOL*)((const char*)mapping + fmap->u.pe.ntheader.FileHeader.PointerToSymbolTable);
    /* FIXME: no way to get strtable size */
    strtable = (const char*)&isym[numsym];
    sect = IMAGE_FIRST_SECTION(RtlImageNtHeader((HMODULE)mapping));

    for (i = 0; i < numsym; i+= naux, isym += naux)
    {
        if (isym->StorageClass == IMAGE_SYM_CLASS_FILE)
        {
            lastfilename = (const char*)(isym + 1);
            compiland = NULL;
        }
        if (isym->StorageClass == IMAGE_SYM_CLASS_EXTERNAL &&
            isym->SectionNumber > 0 && isym->SectionNumber <= fmap->u.pe.ntheader.FileHeader.NumberOfSections)
        {
            if (isym->N.Name.Short)
            {
                name = memcpy(tmp, isym->N.ShortName, 8);
                tmp[8] = '\0';
            }
            else name = strtable + isym->N.Name.Long;
            if (name[0] == '_') name++;

            if (!compiland && lastfilename)
                compiland = symt_new_compiland(module, 0,
                                               source_new(module, NULL, lastfilename));

            if (!(dbghelp_options & SYMOPT_NO_PUBLICS))
                symt_new_public(module, compiland, name, FALSE,
                                module->module.BaseOfImage + sect[isym->SectionNumber - 1].VirtualAddress +
                                    isym->Value,
                                1);
        }
        naux = isym->NumberOfAuxSymbols + 1;
    }
    module->module.SymType = SymCoff;
    module->module.LineNumbers = FALSE;
    module->module.GlobalSymbols = FALSE;
    module->module.TypeInfo = FALSE;
    module->module.SourceIndexed = FALSE;
    module->module.Publics = TRUE;
    pe_unmap_full(fmap);

    return TRUE;
}