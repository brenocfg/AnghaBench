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
struct tlibredirect_data {int size; int name_len; int name_offset; int help_len; int help_offset; int /*<<< orphan*/  minor_version; int /*<<< orphan*/  major_version; int /*<<< orphan*/  flags; scalar_t__ langid; scalar_t__ res; } ;
struct guidsection_header {int size; unsigned int count; int index_offset; int /*<<< orphan*/  magic; } ;
struct guid_index {int data_offset; int data_len; unsigned int rosterindex; int /*<<< orphan*/  guid; } ;
struct TYPE_7__ {scalar_t__* helpdir; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  flags; int /*<<< orphan*/  tlbid; } ;
struct TYPE_8__ {TYPE_2__ typelib; } ;
struct entity {scalar_t__ kind; TYPE_3__ u; } ;
struct TYPE_6__ {unsigned int num; struct entity* base; } ;
struct dll_redirect {scalar_t__* name; TYPE_1__ entities; } ;
struct assembly {unsigned int num_dlls; struct dll_redirect* dlls; } ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_9__ {unsigned int num_assemblies; struct assembly* assemblies; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_4__ ACTIVATION_CONTEXT ;

/* Variables and functions */
 scalar_t__ ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION ; 
 int /*<<< orphan*/  GUIDSECTION_MAGIC ; 
 struct guidsection_header* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  RtlGUIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int aligned_string_len (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (struct guidsection_header*,int /*<<< orphan*/ ,int) ; 
 int strlenW (scalar_t__*) ; 

__attribute__((used)) static NTSTATUS build_tlib_section(ACTIVATION_CONTEXT* actctx, struct guidsection_header **section)
{
    unsigned int i, j, k, total_len = 0, tlib_count = 0, names_len = 0;
    struct guidsection_header *header;
    ULONG module_offset, data_offset;
    struct tlibredirect_data *data;
    struct guid_index *index;

    /* compute section length */
    for (i = 0; i < actctx->num_assemblies; i++)
    {
        struct assembly *assembly = &actctx->assemblies[i];
        for (j = 0; j < assembly->num_dlls; j++)
        {
            struct dll_redirect *dll = &assembly->dlls[j];
            for (k = 0; k < dll->entities.num; k++)
            {
                struct entity *entity = &dll->entities.base[k];
                if (entity->kind == ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION)
                {
                    /* each entry needs index, data and string data for module name and help string */
                    total_len += sizeof(*index);
                    total_len += sizeof(*data);
                    /* help string is stored separately */
                    if (*entity->u.typelib.helpdir)
                        total_len += aligned_string_len((strlenW(entity->u.typelib.helpdir)+1)*sizeof(WCHAR));

                    /* module names are packed one after another */
                    names_len += (strlenW(dll->name)+1)*sizeof(WCHAR);

                    tlib_count++;
                }
            }
        }
    }

    total_len += aligned_string_len(names_len);
    total_len += sizeof(*header);

    header = RtlAllocateHeap(RtlGetProcessHeap(), 0, total_len);
    if (!header) return STATUS_NO_MEMORY;

    memset(header, 0, sizeof(*header));
    header->magic = GUIDSECTION_MAGIC;
    header->size  = sizeof(*header);
    header->count = tlib_count;
    header->index_offset = sizeof(*header) + aligned_string_len(names_len);
    index = (struct guid_index*)((BYTE*)header + header->index_offset);
    module_offset = sizeof(*header);
    data_offset = header->index_offset + tlib_count*sizeof(*index);

    for (i = 0; i < actctx->num_assemblies; i++)
    {
        struct assembly *assembly = &actctx->assemblies[i];
        for (j = 0; j < assembly->num_dlls; j++)
        {
            struct dll_redirect *dll = &assembly->dlls[j];
            for (k = 0; k < dll->entities.num; k++)
            {
                struct entity *entity = &dll->entities.base[k];
                if (entity->kind == ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION)
                {
                    ULONG module_len, help_len;
                    UNICODE_STRING str;
                    WCHAR *ptrW;

                    if (*entity->u.typelib.helpdir)
                        help_len = strlenW(entity->u.typelib.helpdir)*sizeof(WCHAR);
                    else
                        help_len = 0;

                    module_len = strlenW(dll->name)*sizeof(WCHAR);

                    /* setup new index entry */
                    RtlInitUnicodeString(&str, entity->u.typelib.tlbid);
                    RtlGUIDFromString(&str, &index->guid);
                    index->data_offset = data_offset;
                    index->data_len = sizeof(*data) + aligned_string_len(help_len);
                    index->rosterindex = i + 1;

                    /* setup data */
                    data = (struct tlibredirect_data*)((BYTE*)header + index->data_offset);
                    data->size = sizeof(*data);
                    data->res = 0;
                    data->name_len = module_len;
                    data->name_offset = module_offset;
                    /* FIXME: resourceid handling is really weird, and it doesn't seem to be useful */
                    data->langid = 0;
                    data->flags = entity->u.typelib.flags;
                    data->help_len = help_len;
                    data->help_offset = sizeof(*data);
                    data->major_version = entity->u.typelib.major;
                    data->minor_version = entity->u.typelib.minor;

                    /* module name */
                    ptrW = (WCHAR*)((BYTE*)header + data->name_offset);
                    memcpy(ptrW, dll->name, data->name_len);
                    ptrW[data->name_len/sizeof(WCHAR)] = 0;

                    /* help string */
                    if (data->help_len)
                    {
                        ptrW = (WCHAR*)((BYTE*)data + data->help_offset);
                        memcpy(ptrW, entity->u.typelib.helpdir, data->help_len);
                        ptrW[data->help_len/sizeof(WCHAR)] = 0;
                    }

                    data_offset += sizeof(*data);
                    if (help_len)
                        data_offset += aligned_string_len(help_len + sizeof(WCHAR));

                    module_offset += module_len + sizeof(WCHAR);

                    index++;
                }
            }
        }
    }

    *section = header;

    return STATUS_SUCCESS;
}