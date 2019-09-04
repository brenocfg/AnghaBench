#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct assembly_identity {int dummy; } ;
struct actctx_loader {int dummy; } ;
struct TYPE_13__ {scalar_t__ Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int ULONG_PTR ;
typedef  void* ULONG ;
struct TYPE_15__ {int /*<<< orphan*/  Size; } ;
struct TYPE_14__ {int Type; int Name; void* Language; } ;
typedef  scalar_t__ NTSTATUS ;
typedef  char* LPCWSTR ;
typedef  TYPE_2__ LDR_RESOURCE_INFO ;
typedef  TYPE_3__ IMAGE_RESOURCE_DATA_ENTRY ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HIWORD (void*) ; 
 scalar_t__ LdrAccessResource (int /*<<< orphan*/ ,TYPE_3__*,void**,int /*<<< orphan*/ *) ; 
 scalar_t__ LdrFindResource_U (int /*<<< orphan*/ ,TYPE_2__*,int,TYPE_3__**) ; 
 scalar_t__ RT_MANIFEST ; 
 int /*<<< orphan*/  RtlCreateUnicodeString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (TYPE_1__*) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,char*) ; 
 scalar_t__ RtlUnicodeStringToInteger (TYPE_1__*,int,void**) ; 
 int /*<<< orphan*/  RtlUpcaseUnicodeString (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ STATUS_INVALID_PARAMETER ; 
 scalar_t__ STATUS_SUCCESS ; 
 scalar_t__ parse_manifest (struct actctx_loader*,struct assembly_identity*,char*,char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static NTSTATUS get_manifest_in_module( struct actctx_loader* acl, struct assembly_identity* ai,
                                        LPCWSTR filename, LPCWSTR directory, BOOL shared,
                                        HANDLE hModule, LPCWSTR resname, ULONG lang )
{
    NTSTATUS status;
    UNICODE_STRING nameW;
    LDR_RESOURCE_INFO info;
    IMAGE_RESOURCE_DATA_ENTRY* entry = NULL;
    void *ptr;

    //DPRINT( "looking for res %s in module %p %s\n", resname,
    //                hModule, filename );
    DPRINT("get_manifest_in_module %p\n", hModule);

#if 0
    if (TRACE_ON(actctx))
    {
        if (!filename && !get_module_filename( hModule, &nameW, 0 ))
        {
            DPRINT( "looking for res %s in module %p %s\n", debugstr_w(resname),
                   hModule, debugstr_w(nameW.Buffer) );
            RtlFreeUnicodeString( &nameW );
        }
        else DPRINT( "looking for res %s in module %p %s\n", debugstr_w(resname),
                    hModule, debugstr_w(filename) );
    }
#endif

    if (!resname) return STATUS_INVALID_PARAMETER;

    info.Type = (ULONG_PTR)RT_MANIFEST;
    info.Language = lang;
    if (!((ULONG_PTR)resname >> 16))
    {
        info.Name = (ULONG_PTR)resname;
        status = LdrFindResource_U(hModule, &info, 3, &entry);
    }
    else if (resname[0] == '#')
    {
        ULONG value;
        RtlInitUnicodeString(&nameW, resname + 1);
        if (RtlUnicodeStringToInteger(&nameW, 10, &value) != STATUS_SUCCESS || HIWORD(value))
            return STATUS_INVALID_PARAMETER;
        info.Name = value;
        status = LdrFindResource_U(hModule, &info, 3, &entry);
    }
    else
    {
        RtlCreateUnicodeString(&nameW, resname);
        RtlUpcaseUnicodeString(&nameW, &nameW, FALSE);
        info.Name = (ULONG_PTR)nameW.Buffer;
        status = LdrFindResource_U(hModule, &info, 3, &entry);
        RtlFreeUnicodeString(&nameW);
    }
    if (status == STATUS_SUCCESS) status = LdrAccessResource(hModule, entry, &ptr, NULL);

    if (status == STATUS_SUCCESS)
        status = parse_manifest(acl, ai, filename, directory, shared, ptr, entry->Size);

    return status;
}