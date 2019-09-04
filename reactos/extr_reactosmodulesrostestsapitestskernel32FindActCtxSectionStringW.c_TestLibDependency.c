#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct strsection_header {int size; int count; int /*<<< orphan*/  magic; } ;
struct dllredirect_data {int size; } ;
struct TYPE_6__ {scalar_t__ QuadPart; } ;
struct assemply_data {int size; int ulEncodedAssemblyIdentityLength; int ulManifestPathLength; int ulAssemblyDirectoryNameLength; int ulEncodedAssemblyIdentityOffset; int ulManifestPathOffset; int ulAssemblyDirectoryNameOffset; scalar_t__ ulFlags; scalar_t__ ulManifestPathType; TYPE_1__ liManifestLastWriteTime; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_9__ {int cbSize; int ulDataFormatVersion; scalar_t__ hActCtx; int ulLength; int /*<<< orphan*/  ulAssemblyRosterIndex; int /*<<< orphan*/ * lpData; int /*<<< orphan*/ * lpSectionBase; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {scalar_t__ QuadPart; } ;
struct TYPE_8__ {scalar_t__ ulFlags; int ulEncodedAssemblyIdentityLength; scalar_t__ ulManifestPathType; int ulManifestPathLength; int ulAssemblyDirectoryNameLength; int /*<<< orphan*/  lpAssemblyEncodedAssemblyIdentity; int /*<<< orphan*/  lpAssemblyManifestPath; int /*<<< orphan*/  lpAssemblyDirectoryName; TYPE_2__ liManifestLastWriteTime; } ;
typedef  TYPE_3__* PACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  KeyedData ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;
typedef  TYPE_4__ ACTCTX_SECTION_KEYED_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION ; 
 int /*<<< orphan*/  ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION ; 
 int /*<<< orphan*/  AssemblyDetailedInformationInActivationContext ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIND_ACTCTX_SECTION_KEY_RETURN_HACTCTX ; 
 scalar_t__ FindActCtxSectionStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int GetLastError () ; 
 scalar_t__ QueryActCtxW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STRSECTION_MAGIC ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ TRUE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 scalar_t__ wcscmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

VOID TestLibDependency(HANDLE h)
{
    ACTCTX_SECTION_KEYED_DATA KeyedData = { 0 };
    BOOL res;
    struct strsection_header *SectionHeader;
    struct dllredirect_data *redirData;
    struct assemply_data *assemplyData;   
    
    SetLastError(0xdeaddead);
    KeyedData.cbSize = sizeof(KeyedData);
    res = FindActCtxSectionStringW(FIND_ACTCTX_SECTION_KEY_RETURN_HACTCTX,
                                   NULL,
                                   ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION,
                                   L"dep1.dll",
                                   &KeyedData);
    ok(res == TRUE, "FindActCtxSectionString failed\n");
    ok(GetLastError() == 0xdeaddead, "Wrong last error. Expected %lu, got %lu\n", (DWORD)(0xdeaddead), GetLastError());
    
    ok(KeyedData.ulDataFormatVersion == 1, "Wrong format version: %lu", KeyedData.ulDataFormatVersion);
    ok(KeyedData.hActCtx == h, "Wrong handle\n");
    ok(KeyedData.lpSectionBase != NULL, "Expected non null lpSectionBase\n");
    ok(KeyedData.lpData != NULL, "Expected non null lpData\n");
    SectionHeader = (struct strsection_header*)KeyedData.lpSectionBase;
    redirData = (struct dllredirect_data *)KeyedData.lpData;

    if(res == FALSE || KeyedData.ulDataFormatVersion != 1 || SectionHeader == NULL || redirData == NULL)
    {
        skip("Can't read data for dep1.dll. Skipping\n");
    }
    else
    {
        ok(SectionHeader->magic == STRSECTION_MAGIC, "%lu\n", SectionHeader->magic );
        ok(SectionHeader->size == sizeof(*SectionHeader), "Got %lu instead of %d\n", SectionHeader->size, sizeof(*SectionHeader));
        ok(SectionHeader->count == 2, "%lu\n", SectionHeader->count ); /* 2 dlls? */  
        ok(redirData->size == sizeof(*redirData), "Got %lu instead of %d\n", redirData->size, sizeof(*redirData));
    }
    
    SetLastError(0xdeaddead);
    KeyedData.cbSize = sizeof(KeyedData);
    res = FindActCtxSectionStringW(FIND_ACTCTX_SECTION_KEY_RETURN_HACTCTX,
                                   NULL,
                                   ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION,
                                   L"dep1",
                                   &KeyedData);
    ok(res == TRUE, "FindActCtxSectionString failed\n");
    ok(GetLastError() == 0xdeaddead, "Wrong last error. Expected %lu, got %lu\n", (DWORD)(0xdeaddead), GetLastError());
    ok(KeyedData.ulDataFormatVersion == 1, "Wrong format version: %lu", KeyedData.ulDataFormatVersion);
    ok(KeyedData.hActCtx == h, "Wrong handle\n");
    ok(KeyedData.lpSectionBase != NULL, "Expected non null lpSectionBase\n");
    ok(KeyedData.lpData != NULL, "Expected non null lpData\n");
    SectionHeader = (struct strsection_header*)KeyedData.lpSectionBase;
    assemplyData = (struct assemply_data*)KeyedData.lpData;;

    if(res == FALSE || KeyedData.ulDataFormatVersion != 1 || SectionHeader == NULL || assemplyData == NULL)
    {
        skip("Can't read data for dep1. Skipping\n");
    }
    else
    {
        LPCWSTR AssemblyIdentity, ManifestPath, AssemblyDirectory;
        int data_lenght;
        DWORD buffer[256];
        PACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION details = (PACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION)buffer;
        
        ok(SectionHeader->magic == STRSECTION_MAGIC, "%lu\n", SectionHeader->magic );
        ok(SectionHeader->size == sizeof(*SectionHeader), "Got %lu instead of %d\n", SectionHeader->size, sizeof(*SectionHeader));
        ok(SectionHeader->count == 2, "%lu\n", SectionHeader->count ); /* 2 dlls? */  

        data_lenght = assemplyData->size + 
                      assemplyData->ulEncodedAssemblyIdentityLength + 
                      assemplyData->ulManifestPathLength +
                      assemplyData->ulAssemblyDirectoryNameLength + 2 * sizeof(WCHAR);
        ok(assemplyData->size == sizeof(*assemplyData), "Got %lu instead of %d\n", assemplyData->size, sizeof(*assemplyData));
        ok(KeyedData.ulLength == data_lenght, "Got lenght %lu instead of %d\n", KeyedData.ulLength, data_lenght);

        AssemblyIdentity = (WCHAR*)((BYTE*)SectionHeader + assemplyData->ulEncodedAssemblyIdentityOffset);
        ManifestPath = (WCHAR*)((BYTE*)SectionHeader + assemplyData->ulManifestPathOffset);
        AssemblyDirectory = (WCHAR*)((BYTE*)SectionHeader + assemplyData->ulAssemblyDirectoryNameOffset);
        
        /* Use AssemblyDetailedInformationInActivationContext so as to infer the contents of assemplyData */
        res = QueryActCtxW(0, h, &KeyedData.ulAssemblyRosterIndex, 
                           AssemblyDetailedInformationInActivationContext, 
                           &buffer, sizeof(buffer), NULL);
        ok(res == TRUE, "QueryActCtxW failed\n");
        ok(assemplyData->ulFlags == details->ulFlags, "\n");
        ok(assemplyData->ulEncodedAssemblyIdentityLength == details->ulEncodedAssemblyIdentityLength, "\n");
        ok(assemplyData->ulManifestPathType == details->ulManifestPathType, "\n");
        ok(assemplyData->ulManifestPathLength == details->ulManifestPathLength, "\n");
        ok(assemplyData->ulAssemblyDirectoryNameLength == details->ulAssemblyDirectoryNameLength, "\n");
        ok(assemplyData->liManifestLastWriteTime.QuadPart == details->liManifestLastWriteTime.QuadPart, "\n");

        ok(wcscmp(ManifestPath, details->lpAssemblyManifestPath) == 0, "Expected path %S, got %S\n", details->lpAssemblyManifestPath, ManifestPath);
        ok(wcscmp(AssemblyDirectory, details->lpAssemblyDirectoryName) == 0, "Expected path %S, got %S\n", details->lpAssemblyManifestPath, ManifestPath);

        /* It looks like that AssemblyIdentity isn't null terminated */
        ok(memcmp(AssemblyIdentity, details->lpAssemblyEncodedAssemblyIdentity, assemplyData->ulEncodedAssemblyIdentityLength) == 0, "Got wrong AssemblyIdentity\n");
    }    
}