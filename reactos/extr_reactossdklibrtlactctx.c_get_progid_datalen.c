#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct string_index {int dummy; } ;
struct progidredirect_data {int dummy; } ;
struct entity_array {unsigned int num; struct entity* base; } ;
struct TYPE_4__ {unsigned int num; scalar_t__* progids; } ;
struct TYPE_5__ {TYPE_1__ progids; scalar_t__ progid; } ;
struct TYPE_6__ {TYPE_2__ comclass; } ;
struct entity {scalar_t__ kind; TYPE_3__ u; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 scalar_t__ ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION ; 
 scalar_t__ aligned_string_len (int) ; 
 int strlenW (scalar_t__) ; 

__attribute__((used)) static void get_progid_datalen(struct entity_array *entities, unsigned int *count, unsigned int *total_len)
{
    unsigned int i, j, single_len;

    single_len = sizeof(struct progidredirect_data) + sizeof(struct string_index) + sizeof(GUID);
    for (i = 0; i < entities->num; i++)
    {
        struct entity *entity = &entities->base[i];
        if (entity->kind == ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION)
        {
            if (entity->u.comclass.progid)
            {
                *total_len += single_len + aligned_string_len((strlenW(entity->u.comclass.progid)+1)*sizeof(WCHAR));
                *count += 1;
            }

            for (j = 0; j < entity->u.comclass.progids.num; j++)
                *total_len += aligned_string_len((strlenW(entity->u.comclass.progids.progids[j])+1)*sizeof(WCHAR));

            *total_len += single_len*entity->u.comclass.progids.num;
            *count += entity->u.comclass.progids.num;
        }
    }
}