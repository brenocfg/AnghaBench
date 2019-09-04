#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct image_section_map {unsigned int sidx; struct image_file_map* fmap; } ;
struct TYPE_7__ {unsigned int NumberOfSections; } ;
struct TYPE_8__ {TYPE_1__ FileHeader; } ;
struct TYPE_11__ {char* strtable; TYPE_4__* sect; TYPE_2__ ntheader; } ;
struct TYPE_12__ {TYPE_5__ pe; } ;
struct image_file_map {TYPE_6__ u; } ;
struct TYPE_9__ {scalar_t__ Name; } ;
struct TYPE_10__ {TYPE_3__ shdr; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IMAGE_SIZEOF_SHORT_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 int atoi (char const*) ; 
 char* memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char const*) ; 

BOOL pe_find_section(struct image_file_map* fmap, const char* name,
                     struct image_section_map* ism)
{
    const char*                 sectname;
    unsigned                    i;
    char                        tmp[IMAGE_SIZEOF_SHORT_NAME + 1];

    for (i = 0; i < fmap->u.pe.ntheader.FileHeader.NumberOfSections; i++)
    {
        sectname = (const char*)fmap->u.pe.sect[i].shdr.Name;
        /* long section names start with a '/' (at least on MinGW32) */
        if (sectname[0] == '/' && fmap->u.pe.strtable)
            sectname = fmap->u.pe.strtable + atoi(sectname + 1);
        else
        {
            /* the section name may not be null terminated */
            sectname = memcpy(tmp, sectname, IMAGE_SIZEOF_SHORT_NAME);
            tmp[IMAGE_SIZEOF_SHORT_NAME] = '\0';
        }
        if (!strcasecmp(sectname, name))
        {
            ism->fmap = fmap;
            ism->sidx = i;
            return TRUE;
        }
    }
    ism->fmap = NULL;
    ism->sidx = -1;

    return FALSE;
}