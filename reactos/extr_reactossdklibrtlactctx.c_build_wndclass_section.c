#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct wndclass_redirect_data {int size; int name_len; int name_offset; int module_len; int module_offset; scalar_t__ res; } ;
struct strsection_header {int size; unsigned int count; int index_offset; int /*<<< orphan*/  magic; } ;
struct string_index {int name_offset; int name_len; int data_offset; int data_len; unsigned int rosterindex; int /*<<< orphan*/  hash; } ;
struct TYPE_8__ {char const* name; scalar_t__ versioned; } ;
struct TYPE_9__ {TYPE_1__ class; } ;
struct entity {scalar_t__ kind; TYPE_2__ u; } ;
struct TYPE_10__ {unsigned int num; struct entity* base; } ;
struct dll_redirect {char const* name; TYPE_3__ entities; } ;
struct assembly {unsigned int num_dlls; struct dll_redirect* dlls; } ;
typedef  char WCHAR ;
typedef  int USHORT ;
struct TYPE_11__ {char const* Buffer; int Length; int MaximumLength; } ;
typedef  TYPE_4__ UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_12__ {unsigned int num_assemblies; struct assembly* assemblies; } ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_5__ ACTIVATION_CONTEXT ;

/* Variables and functions */
 scalar_t__ ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION ; 
 int /*<<< orphan*/  HASH_STRING_ALGORITHM_X65599 ; 
 struct strsection_header* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  RtlHashUnicodeString (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATUS_NO_MEMORY ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STRSECTION_MAGIC ; 
 int /*<<< orphan*/  TRUE ; 
 int aligned_string_len (int) ; 
 int get_assembly_version (struct assembly*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (struct strsection_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcatW (char*,char const*) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static NTSTATUS build_wndclass_section(ACTIVATION_CONTEXT* actctx, struct strsection_header **section)
{
    unsigned int i, j, k, total_len = 0, class_count = 0;
    struct wndclass_redirect_data *data;
    struct strsection_header *header;
    struct string_index *index;
    ULONG name_offset;

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
                if (entity->kind == ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION)
                {
                    int class_len = strlenW(entity->u.class.name) + 1;
                    int len;

                    /* each class entry needs index, data and string data */
                    total_len += sizeof(*index);
                    total_len += sizeof(*data);
                    /* original name is stored separately */
                    total_len += aligned_string_len(class_len*sizeof(WCHAR));
                    /* versioned name and module name are stored one after another */
                    if (entity->u.class.versioned)
                        len = get_assembly_version(assembly, NULL) + class_len + 1 /* '!' separator */;
                    else
                        len = class_len;
                    len += strlenW(dll->name) + 1;
                    total_len += aligned_string_len(len*sizeof(WCHAR));

                    class_count++;
                }
            }
        }
    }

    total_len += sizeof(*header);

    header = RtlAllocateHeap(RtlGetProcessHeap(), 0, total_len);
    if (!header) return STATUS_NO_MEMORY;

    memset(header, 0, sizeof(*header));
    header->magic = STRSECTION_MAGIC;
    header->size  = sizeof(*header);
    header->count = class_count;
    header->index_offset = sizeof(*header);
    index = (struct string_index*)((BYTE*)header + header->index_offset);
    name_offset = header->index_offset + header->count*sizeof(*index);

    for (i = 0; i < actctx->num_assemblies; i++)
    {
        struct assembly *assembly = &actctx->assemblies[i];
        for (j = 0; j < assembly->num_dlls; j++)
        {
            struct dll_redirect *dll = &assembly->dlls[j];
            for (k = 0; k < dll->entities.num; k++)
            {
                struct entity *entity = &dll->entities.base[k];
                if (entity->kind == ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION)
                {
                    static const WCHAR exclW[] = {'!',0};
                    ULONG versioned_len, module_len;
                    UNICODE_STRING str;
                    WCHAR *ptrW;

                    /* setup new index entry */
                    str.Buffer = entity->u.class.name;
                    str.Length = (USHORT)strlenW(entity->u.class.name)*sizeof(WCHAR);
                    str.MaximumLength = str.Length + sizeof(WCHAR);
                    /* hash original class name */
                    RtlHashUnicodeString(&str, TRUE, HASH_STRING_ALGORITHM_X65599, &index->hash);

                    /* include '!' separator too */
                    if (entity->u.class.versioned)
                        versioned_len = (get_assembly_version(assembly, NULL) + 1)*sizeof(WCHAR) + str.Length;
                    else
                        versioned_len = str.Length;
                    module_len = strlenW(dll->name)*sizeof(WCHAR);

                    index->name_offset = name_offset;
                    index->name_len = str.Length;
                    index->data_offset = index->name_offset + aligned_string_len(str.MaximumLength);
                    index->data_len = sizeof(*data) + versioned_len + module_len + 2*sizeof(WCHAR) /* two nulls */;
                    index->rosterindex = i + 1;

                    /* setup data */
                    data = (struct wndclass_redirect_data*)((BYTE*)header + index->data_offset);
                    data->size = sizeof(*data);
                    data->res = 0;
                    data->name_len = versioned_len;
                    data->name_offset = sizeof(*data);
                    data->module_len = module_len;
                    data->module_offset = index->data_offset + data->name_offset + data->name_len + sizeof(WCHAR);

                    /* original class name */
                    ptrW = (WCHAR*)((BYTE*)header + index->name_offset);
                    memcpy(ptrW, entity->u.class.name, index->name_len);
                    ptrW[index->name_len/sizeof(WCHAR)] = 0;

                    /* module name */
                    ptrW = (WCHAR*)((BYTE*)header + data->module_offset);
                    memcpy(ptrW, dll->name, data->module_len);
                    ptrW[data->module_len/sizeof(WCHAR)] = 0;

                    /* versioned name */
                    ptrW = (WCHAR*)((BYTE*)data + data->name_offset);
                    if (entity->u.class.versioned)
                    {
                        get_assembly_version(assembly, ptrW);
                        strcatW(ptrW, exclW);
                        strcatW(ptrW, entity->u.class.name);
                    }
                    else
                    {
                        memcpy(ptrW, entity->u.class.name, index->name_len);
                        ptrW[index->name_len/sizeof(WCHAR)] = 0;
                    }

                    name_offset += sizeof(*data);
                    name_offset += aligned_string_len(str.MaximumLength) + aligned_string_len(versioned_len + module_len + 2*sizeof(WCHAR));

                    index++;
                }
            }
        }
    }

    *section = header;

    return STATUS_SUCCESS;
}