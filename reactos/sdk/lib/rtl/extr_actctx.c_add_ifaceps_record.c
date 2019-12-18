#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ifacepsredirect_data {int size; int name_len; int name_offset; int /*<<< orphan*/  base; int /*<<< orphan*/  tlbid; int /*<<< orphan*/  nummethods; int /*<<< orphan*/  iid; int /*<<< orphan*/  mask; } ;
struct guidsection_header {int dummy; } ;
struct guid_index {int data_offset; int data_len; int rosterindex; int /*<<< orphan*/  guid; } ;
struct entity_array {unsigned int num; struct entity* base; } ;
struct TYPE_3__ {scalar_t__ name; int /*<<< orphan*/  base; int /*<<< orphan*/  tlib; int /*<<< orphan*/  nummethods; int /*<<< orphan*/  ps32; int /*<<< orphan*/  mask; int /*<<< orphan*/  iid; } ;
struct TYPE_4__ {TYPE_1__ ifaceps; } ;
struct entity {scalar_t__ kind; TYPE_2__ u; } ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ ACTIVATION_CONTEXT_SECTION_COM_INTERFACE_REDIRECTION ; 
 int /*<<< orphan*/  RtlGUIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int aligned_string_len (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int strlenW (scalar_t__) ; 

__attribute__((used)) static void add_ifaceps_record(struct guidsection_header *section, struct entity_array *entities,
    struct guid_index **index, ULONG *data_offset, ULONG rosterindex)
{
    unsigned int i;

    for (i = 0; i < entities->num; i++)
    {
        struct entity *entity = &entities->base[i];
        if (entity->kind == ACTIVATION_CONTEXT_SECTION_COM_INTERFACE_REDIRECTION)
        {
            struct ifacepsredirect_data *data = (struct ifacepsredirect_data*)((BYTE*)section + *data_offset);
            UNICODE_STRING str;
            ULONG name_len;

            if (entity->u.ifaceps.name)
                name_len = strlenW(entity->u.ifaceps.name)*sizeof(WCHAR);
            else
                name_len = 0;

            /* setup index */
            RtlInitUnicodeString(&str, entity->u.ifaceps.iid);
            RtlGUIDFromString(&str, &(*index)->guid);
            (*index)->data_offset = *data_offset;
            (*index)->data_len = sizeof(*data) + name_len ? aligned_string_len(name_len + sizeof(WCHAR)) : 0;
            (*index)->rosterindex = rosterindex;

            /* setup data record */
            data->size = sizeof(*data);
            data->mask = entity->u.ifaceps.mask;

            /* proxyStubClsid32 value is only stored for external PS,
               if set it's used as iid, otherwise 'iid' attribute value is used */
            if (entity->u.ifaceps.ps32)
            {
                RtlInitUnicodeString(&str, entity->u.ifaceps.ps32);
                RtlGUIDFromString(&str, &data->iid);
            }
            else
                data->iid = (*index)->guid;

            data->nummethods = entity->u.ifaceps.nummethods;

            if (entity->u.ifaceps.tlib)
            {
                RtlInitUnicodeString(&str, entity->u.ifaceps.tlib);
                RtlGUIDFromString(&str, &data->tlbid);
            }
            else
                memset(&data->tlbid, 0, sizeof(data->tlbid));

            if (entity->u.ifaceps.base)
            {
                RtlInitUnicodeString(&str, entity->u.ifaceps.base);
                RtlGUIDFromString(&str, &data->base);
            }
            else
                memset(&data->base, 0, sizeof(data->base));

            data->name_len = name_len;
            data->name_offset = data->name_len ? sizeof(*data) : 0;

            /* name string */
            if (data->name_len)
            {
                WCHAR *ptrW = (WCHAR*)((BYTE*)data + data->name_offset);
                memcpy(ptrW, entity->u.ifaceps.name, data->name_len);
                ptrW[data->name_len/sizeof(WCHAR)] = 0;
            }

            /* move to next record */
            (*index) += 1;
            *data_offset += sizeof(*data);
            if (data->name_len)
                *data_offset += aligned_string_len(data->name_len + sizeof(WCHAR));
        }
    }
}