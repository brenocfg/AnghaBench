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
struct guid_index {int dummy; } ;
struct entity_array {unsigned int num; struct entity* base; } ;
struct TYPE_3__ {scalar_t__ progid; scalar_t__ version; scalar_t__ name; } ;
struct TYPE_4__ {TYPE_1__ comclass; } ;
struct entity {scalar_t__ kind; TYPE_2__ u; } ;
struct dll_redirect {scalar_t__ name; } ;
struct comclassredirect_data {int dummy; } ;
struct clrclass_data {int dummy; } ;
typedef  int /*<<< orphan*/  mscoreeW ;
typedef  int /*<<< orphan*/  mscoree2W ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 scalar_t__ ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION ; 
 scalar_t__ aligned_string_len (int) ; 
 int strlenW (scalar_t__) ; 

__attribute__((used)) static void get_comserver_datalen(const struct entity_array *entities, const struct dll_redirect *dll,
    unsigned int *count, unsigned int *len, unsigned int *module_len)
{
    unsigned int i;

    for (i = 0; i < entities->num; i++)
    {
        struct entity *entity = &entities->base[i];
        if (entity->kind == ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION)
        {
            /* each entry needs two index entries, extra one goes for alias GUID */
            *len += 2*sizeof(struct guid_index);
            /* To save some memory we don't allocated two data structures,
               instead alias index and normal index point to the same data structure. */
            *len += sizeof(struct comclassredirect_data);

            /* for clrClass store some more */
            if (entity->u.comclass.name)
            {
                unsigned int str_len;

                /* all string data is stored together in aligned block */
                str_len = strlenW(entity->u.comclass.name)+1;
                if (entity->u.comclass.progid)
                    str_len += strlenW(entity->u.comclass.progid)+1;
                if (entity->u.comclass.version)
                    str_len += strlenW(entity->u.comclass.version)+1;

                *len += sizeof(struct clrclass_data);
                *len += aligned_string_len(str_len*sizeof(WCHAR));

                /* module name is forced to mscoree.dll, and stored two times with different case */
                *module_len += sizeof(mscoreeW) + sizeof(mscoree2W);
            }
            else
            {
                /* progid string is stored separately */
                if (entity->u.comclass.progid)
                    *len += aligned_string_len((strlenW(entity->u.comclass.progid)+1)*sizeof(WCHAR));

                *module_len += (strlenW(dll->name)+1)*sizeof(WCHAR);
            }

            *count += 1;
        }
    }
}