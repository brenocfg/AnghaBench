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
struct TYPE_2__ {scalar_t__* glyph_ids; } ;
typedef  TYPE_1__ cmap_format_0 ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL get_first_last_from_cmap0(void *ptr, DWORD *first, DWORD *last)
{
    int i;
    cmap_format_0 *cmap = (cmap_format_0*)ptr;

    *first = 256;

    for(i = 0; i < 256; i++)
    {
        if(cmap->glyph_ids[i] == 0) continue;
        *last = i;
        if(*first == 256) *first = i;
    }
    if(*first == 256) return FALSE;
    return TRUE;
}