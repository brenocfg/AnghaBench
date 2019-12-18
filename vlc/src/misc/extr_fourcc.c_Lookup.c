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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct fourcc_mapping {char* desc; int /*<<< orphan*/  fourcc; } ;
struct fourcc_desc {char* desc; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 struct fourcc_mapping* bsearch (int /*<<< orphan*/ *,struct fourcc_mapping const*,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fourcc_cmp ; 

__attribute__((used)) static vlc_fourcc_t Lookup(vlc_fourcc_t fourcc, const char **restrict dsc,
                           const struct fourcc_mapping *mapv, size_t mapc,
                           const struct fourcc_desc *dscv, size_t dscc)
{
    const struct fourcc_mapping *mapping;
    const struct fourcc_desc *desc;

    mapping = bsearch(&fourcc, mapv, mapc, sizeof (*mapv), fourcc_cmp);
    if (mapping != NULL)
    {
        if (dsc != NULL)
        {
            desc = bsearch(&fourcc, dscv, dscc, sizeof (*dscv), fourcc_cmp);
            if (desc != NULL)
            {
                *dsc = desc->desc;
                return mapping->fourcc;
            }
        }
        fourcc = mapping->fourcc;
    }

    desc = bsearch(&fourcc, dscv, dscc, sizeof (*dscv), fourcc_cmp);
    if (desc == NULL)
        return 0; /* Unknown FourCC */
    if (dsc != NULL)
        *dsc = desc->desc;
    return fourcc; /* Known FourCC (has a description) */
}