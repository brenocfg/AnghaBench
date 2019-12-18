#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct strsection_header {int dummy; } ;
struct string_index {int dummy; } ;
struct progids {unsigned int num; scalar_t__* progids; } ;
struct guid_index {int dummy; } ;
struct entity_array {unsigned int num; struct entity* base; } ;
struct TYPE_6__ {scalar_t__ progid; int /*<<< orphan*/  clsid; struct progids progids; } ;
struct TYPE_7__ {TYPE_1__ comclass; } ;
struct entity {scalar_t__ kind; TYPE_2__ u; } ;
struct comclassredirect_data {int /*<<< orphan*/  alias; } ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  comserver_section; } ;
typedef  int /*<<< orphan*/  GUID ;
typedef  TYPE_3__ ACTIVATION_CONTEXT ;

/* Variables and functions */
 scalar_t__ ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION ; 
 int /*<<< orphan*/  RtlGUIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct guid_index* find_guid_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct comclassredirect_data* get_comclass_data (TYPE_3__*,struct guid_index*) ; 
 int /*<<< orphan*/  write_progid_record (struct strsection_header*,scalar_t__,int /*<<< orphan*/ *,struct string_index**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_progid_record(ACTIVATION_CONTEXT* actctx, struct strsection_header *section, const struct entity_array *entities,
    struct string_index **index, ULONG *data_offset, ULONG *global_offset, ULONG rosterindex)
{
    unsigned int i, j;

    for (i = 0; i < entities->num; i++)
    {
        struct entity *entity = &entities->base[i];
        if (entity->kind == ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION)
        {
            const struct progids *progids = &entity->u.comclass.progids;
            struct comclassredirect_data *comclass;
            struct guid_index *guid_index;
            UNICODE_STRING str;
            GUID clsid;

            RtlInitUnicodeString(&str, entity->u.comclass.clsid);
            RtlGUIDFromString(&str, &clsid);

            guid_index = find_guid_index(actctx->comserver_section, &clsid);
            comclass = get_comclass_data(actctx, guid_index);

            if (entity->u.comclass.progid)
                write_progid_record(section, entity->u.comclass.progid, &comclass->alias,
                     index, data_offset, global_offset, rosterindex);

            for (j = 0; j < progids->num; j++)
                write_progid_record(section, progids->progids[j], &comclass->alias,
                     index, data_offset, global_offset, rosterindex);
        }
    }
}