#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ IMAGE_SECTION_HEADER ;
typedef  int /*<<< orphan*/  IMAGE_NT_HEADERS ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/ * get_nt_header (void*,size_t) ; 
 TYPE_1__* get_section_header (void*,size_t,size_t*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static IMAGE_SECTION_HEADER *get_resource_section( void *base, DWORD mapping_size )
{
    IMAGE_SECTION_HEADER *sec;
    IMAGE_NT_HEADERS *nt;
    DWORD i, num_sections = 0;

    nt = get_nt_header( base, mapping_size );
    if (!nt)
        return NULL;

    sec = get_section_header( base, mapping_size, &num_sections );
    if (!sec)
        return NULL;

    /* find the resources section */
    for (i=0; i<num_sections; i++)
        if (!memcmp(sec[i].Name, ".rsrc", 6))
            break;

    if (i == num_sections)
        return NULL;

    return &sec[i];
}