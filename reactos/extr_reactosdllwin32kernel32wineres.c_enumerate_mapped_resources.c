#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource_data {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  CodePage; int /*<<< orphan*/  OffsetToData; } ;
struct TYPE_8__ {scalar_t__ NumberOfNamedEntries; scalar_t__ NumberOfIdEntries; int /*<<< orphan*/  MinorVersion; int /*<<< orphan*/  MajorVersion; } ;
struct TYPE_7__ {int OffsetToDirectory; int OffsetToData; int /*<<< orphan*/  Id; } ;
typedef  int /*<<< orphan*/  QUEUEDUPDATES ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LANGID ;
typedef  TYPE_1__ IMAGE_RESOURCE_DIRECTORY_ENTRY ;
typedef  TYPE_2__ IMAGE_RESOURCE_DIRECTORY ;
typedef  TYPE_3__ IMAGE_RESOURCE_DATA_ENTRY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource_data*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 void* address_from_rva (void*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource_data* allocate_resource_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_free_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_dup_string (TYPE_2__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  update_add_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL enumerate_mapped_resources( QUEUEDUPDATES *updates,
                             void *base, DWORD mapping_size,
                             const IMAGE_RESOURCE_DIRECTORY *root )
{
    const IMAGE_RESOURCE_DIRECTORY *namedir, *langdir;
    const IMAGE_RESOURCE_DIRECTORY_ENTRY *e1, *e2, *e3;
    const IMAGE_RESOURCE_DATA_ENTRY *data;
    DWORD i, j, k;

    TRACE("version (%d.%d) %d named %d id entries\n",
          root->MajorVersion, root->MinorVersion, root->NumberOfNamedEntries, root->NumberOfIdEntries);

    for (i = 0; i< root->NumberOfNamedEntries + root->NumberOfIdEntries; i++)
    {
        LPWSTR Type;

        e1 = (const IMAGE_RESOURCE_DIRECTORY_ENTRY*)(root + 1) + i;

        Type = resource_dup_string( root, e1 );

        namedir = (const IMAGE_RESOURCE_DIRECTORY *)((const char *)root + e1->OffsetToDirectory);
        for (j = 0; j < namedir->NumberOfNamedEntries + namedir->NumberOfIdEntries; j++)
        {
            LPWSTR Name;

            e2 = (const IMAGE_RESOURCE_DIRECTORY_ENTRY*)(namedir + 1) + j;

            Name = resource_dup_string( root, e2 );

            langdir = (const IMAGE_RESOURCE_DIRECTORY *)((const char *)root + e2->OffsetToDirectory);
            for (k = 0; k < langdir->NumberOfNamedEntries + langdir->NumberOfIdEntries; k++)
            {
                LANGID Lang;
                void *p;
                struct resource_data *resdata;

                e3 = (const IMAGE_RESOURCE_DIRECTORY_ENTRY*)(langdir + 1) + k;

                Lang = e3->Id;

                data = (const IMAGE_RESOURCE_DATA_ENTRY *)((const char *)root + e3->OffsetToData);

                p = address_from_rva( base, mapping_size, data->OffsetToData, data->Size );

                resdata = allocate_resource_data( Lang, data->CodePage, p, data->Size, FALSE );
                if (resdata)
                {
                    if (!update_add_resource( updates, Type, Name, Lang, resdata, FALSE ))
                        HeapFree( GetProcessHeap(), 0, resdata );
                }
            }
            res_free_str( Name );
        }
        res_free_str( Type );
    }

    return TRUE;
}