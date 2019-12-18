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
struct strsection_header {int size; unsigned int count; unsigned int global_offset; unsigned int global_len; unsigned int index_offset; int /*<<< orphan*/  magic; } ;
struct string_index {int dummy; } ;
struct dll_redirect {int /*<<< orphan*/  entities; } ;
struct assembly {unsigned int num_dlls; struct dll_redirect* dlls; int /*<<< orphan*/  entities; } ;
typedef  unsigned int ULONG ;
struct TYPE_4__ {unsigned int num_assemblies; struct assembly* assemblies; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_1__ ACTIVATION_CONTEXT ;

/* Variables and functions */
 struct strsection_header* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STRSECTION_MAGIC ; 
 int /*<<< orphan*/  add_progid_record (TYPE_1__*,struct strsection_header*,int /*<<< orphan*/ *,struct string_index**,unsigned int*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  get_progid_datalen (int /*<<< orphan*/ *,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  memset (struct strsection_header*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static NTSTATUS build_progid_section(ACTIVATION_CONTEXT* actctx, struct strsection_header **section)
{
    unsigned int i, j, total_len = 0, count = 0;
    struct strsection_header *header;
    ULONG data_offset, global_offset;
    struct string_index *index;

    /* compute section length */
    for (i = 0; i < actctx->num_assemblies; i++)
    {
        struct assembly *assembly = &actctx->assemblies[i];

        get_progid_datalen(&assembly->entities, &count, &total_len);
        for (j = 0; j < assembly->num_dlls; j++)
        {
            struct dll_redirect *dll = &assembly->dlls[j];
            get_progid_datalen(&dll->entities, &count, &total_len);
        }
    }

    total_len += sizeof(*header);

    header = RtlAllocateHeap(RtlGetProcessHeap(), 0, total_len);
    if (!header) return STATUS_NO_MEMORY;

    memset(header, 0, sizeof(*header));
    header->magic = STRSECTION_MAGIC;
    header->size  = sizeof(*header);
    header->count = count;
    header->global_offset = header->size;
    header->global_len = count*sizeof(GUID);
    header->index_offset = header->size + header->global_len;

    index = (struct string_index*)((BYTE*)header + header->index_offset);
    data_offset = header->index_offset + count*sizeof(*index);
    global_offset = header->global_offset;

    for (i = 0; i < actctx->num_assemblies; i++)
    {
        struct assembly *assembly = &actctx->assemblies[i];

        add_progid_record(actctx, header, &assembly->entities, &index, &data_offset, &global_offset, i + 1);
        for (j = 0; j < assembly->num_dlls; j++)
        {
            struct dll_redirect *dll = &assembly->dlls[j];
            add_progid_record(actctx, header, &dll->entities, &index, &data_offset, &global_offset, i + 1);
        }
    }

    *section = header;

    return STATUS_SUCCESS;
}