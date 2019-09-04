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
typedef  unsigned int UINT ;
struct TYPE_4__ {unsigned int container_count; void* containers; int /*<<< orphan*/ * container_formats; int /*<<< orphan*/  classkey; } ;
typedef  TYPE_1__ MetadataReaderInfo ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ComponentInfo_GetGuidList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  containers_keyname ; 
 void* heap_calloc (unsigned int,int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_metadata_patterns (TYPE_1__*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static BOOL read_metadata_info(MetadataReaderInfo *info)
{
    UINT format_count;
    GUID *formats;
    HRESULT hr;

    hr = ComponentInfo_GetGuidList(info->classkey, containers_keyname, 0, NULL, &format_count);
    if (FAILED(hr)) return TRUE;

    formats = heap_calloc(format_count, sizeof(*formats));
    if (!formats) return FALSE;

    hr = ComponentInfo_GetGuidList(info->classkey, containers_keyname, format_count, formats,
                                   &format_count);
    if (FAILED(hr))
    {
        heap_free(formats);
        return FALSE;
    }

    info->container_formats = formats;
    info->container_count = format_count;

    if (format_count)
    {
        unsigned i;

        info->containers = heap_calloc(format_count, sizeof(*info->containers));
        if (!info->containers) return FALSE;

        for (i = 0; i < format_count; i++)
            read_metadata_patterns(info, info->container_formats + i, info->containers + i);
    }

    return TRUE;
}