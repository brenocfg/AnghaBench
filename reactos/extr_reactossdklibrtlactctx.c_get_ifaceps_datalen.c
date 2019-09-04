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
struct ifacepsredirect_data {int dummy; } ;
struct guid_index {int dummy; } ;
struct entity_array {unsigned int num; struct entity* base; } ;
struct TYPE_3__ {scalar_t__ name; } ;
struct TYPE_4__ {TYPE_1__ ifaceps; } ;
struct entity {scalar_t__ kind; TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 scalar_t__ ACTIVATION_CONTEXT_SECTION_COM_INTERFACE_REDIRECTION ; 
 scalar_t__ aligned_string_len (int) ; 
 int strlenW (scalar_t__) ; 

__attribute__((used)) static void get_ifaceps_datalen(const struct entity_array *entities, unsigned int *count, unsigned int *len)
{
    unsigned int i;

    for (i = 0; i < entities->num; i++)
    {
        struct entity *entity = &entities->base[i];
        if (entity->kind == ACTIVATION_CONTEXT_SECTION_COM_INTERFACE_REDIRECTION)
        {
            *len += sizeof(struct guid_index) + sizeof(struct ifacepsredirect_data);
            if (entity->u.ifaceps.name)
                *len += aligned_string_len((strlenW(entity->u.ifaceps.name)+1)*sizeof(WCHAR));
            *count += 1;
        }
    }
}