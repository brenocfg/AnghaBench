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
struct TYPE_5__ {int /*<<< orphan*/  BaseOfImage; } ;
struct module {TYPE_1__ module; TYPE_4__** format_info; } ;
struct image_section_map {int dummy; } ;
struct image_file_map {int dummy; } ;
struct TYPE_7__ {TYPE_2__* pe_info; } ;
struct TYPE_8__ {TYPE_3__ u; } ;
struct TYPE_6__ {struct image_file_map fmap; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t DFI_PE ; 
 scalar_t__ FALSE ; 
 char const* IMAGE_NO_MAP ; 
 int /*<<< orphan*/  TRACE (char*,char*) ; 
 int /*<<< orphan*/  image_get_map_size (struct image_section_map*) ; 
 char* image_map_section (struct image_section_map*) ; 
 int /*<<< orphan*/  image_unmap_section (struct image_section_map*) ; 
 scalar_t__ pe_find_section (struct image_file_map*,char*,struct image_section_map*) ; 
 scalar_t__ rsym_parse (struct module*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL pe_load_rsym(struct module* module)
{
    struct image_file_map*      fmap = &module->format_info[DFI_PE]->u.pe_info->fmap;
    struct image_section_map    sect_rsym;
    BOOL                        ret = FALSE;

    if (pe_find_section(fmap, ".rossym", &sect_rsym))
    {
        const char* rsym = image_map_section(&sect_rsym);
        if (rsym != IMAGE_NO_MAP)
        {
            ret = rsym_parse(module, module->module.BaseOfImage,
                             rsym, image_get_map_size(&sect_rsym));
        }
        image_unmap_section(&sect_rsym);
    }
    TRACE("%s the RSYM debug info\n", ret ? "successfully loaded" : "failed to load");

    return ret;
}