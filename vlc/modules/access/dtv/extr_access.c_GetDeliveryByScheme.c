#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtv_delivery_t ;
struct TYPE_3__ {int /*<<< orphan*/  delivery; int /*<<< orphan*/  psz_scheme; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DTV_DELIVERY_NONE ; 
 TYPE_1__* delsys_mappings ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dtv_delivery_t GetDeliveryByScheme(const char *psz_scheme)
{
    for (size_t i=0; i<ARRAY_SIZE(delsys_mappings); i++)
    {
        if(!strcasecmp(psz_scheme, delsys_mappings[i].psz_scheme))
            return delsys_mappings[i].delivery;
    }
    return DTV_DELIVERY_NONE;
}