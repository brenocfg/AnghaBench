#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t PointerToRawData; int SizeOfRawData; int /*<<< orphan*/  Name; } ;
typedef  int /*<<< orphan*/  QUEUEDUPDATES ;
typedef  TYPE_1__ IMAGE_SECTION_HEADER ;
typedef  int /*<<< orphan*/  IMAGE_RESOURCE_DIRECTORY ;
typedef  int /*<<< orphan*/  IMAGE_NT_HEADERS ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,size_t,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  enumerate_mapped_resources (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * get_nt_header (void*,size_t) ; 
 TYPE_1__* get_section_header (void*,size_t,size_t*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static BOOL read_mapped_resources( QUEUEDUPDATES *updates, void *base, DWORD mapping_size )
{
    const IMAGE_RESOURCE_DIRECTORY *root;
    const IMAGE_NT_HEADERS *nt;
    const IMAGE_SECTION_HEADER *sec;
    DWORD num_sections = 0, i;

    nt = get_nt_header( base, mapping_size );
    if (!nt)
        return FALSE;

    sec = get_section_header( base, mapping_size, &num_sections );
    if (!sec)
        return FALSE;

    for (i=0; i<num_sections; i++)
        if (!memcmp(sec[i].Name, ".rsrc", 6))
            break;

    if (i == num_sections)
        return TRUE;

    /* check the resource data is inside the mapping */
    if (sec[i].PointerToRawData > mapping_size ||
        (sec[i].PointerToRawData + sec[i].SizeOfRawData) > mapping_size)
        return TRUE;

    TRACE("found .rsrc at %08x, size %08x\n", sec[i].PointerToRawData, sec[i].SizeOfRawData);

    if (!sec[i].PointerToRawData || sec[i].SizeOfRawData < sizeof(IMAGE_RESOURCE_DIRECTORY))
        return TRUE;

    root = (void*) ((BYTE*)base + sec[i].PointerToRawData);
    enumerate_mapped_resources( updates, base, mapping_size, root );

    return TRUE;
}