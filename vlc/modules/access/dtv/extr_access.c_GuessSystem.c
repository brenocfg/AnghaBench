#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  dvb_device_t ;
typedef  scalar_t__ dtv_delivery_t ;

/* Variables and functions */
 unsigned int DTV_DELGROUP_CABLE ; 
 unsigned int DTV_DELGROUP_G2 ; 
 unsigned int DTV_DELGROUP_SAT ; 
 unsigned int DTV_DELGROUP_TERRES ; 
 scalar_t__ DTV_DELIVERY_NONE ; 
 scalar_t__ GetDeliveryByScheme (char const*) ; 
 scalar_t__ GetSingleDelivery (unsigned int) ; 
 unsigned int dvb_enum_systems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static dtv_delivery_t GuessSystem (const char *scheme, dvb_device_t *dev)
{
    /* Specific delivery system is specified */
    dtv_delivery_t d = GetDeliveryByScheme(scheme);
    if(d != DTV_DELIVERY_NONE)
        return d;

    /* If the demodulator supports 2G, we cannot guess whether
     * 1G or 2G is intended. For backward compatibility, 1G is assumed
     * (this is not a limitation of Linux DVB). We will probably need something
     * smarter when 2G (semi automatic) scanning is implemented. */
    unsigned systems = dvb_enum_systems (dev);

    systems &= ~DTV_DELGROUP_G2;

    if( systems )
    {
        /* Only wave carrier is specified */
        if (!strcasecmp (scheme, "cable"))
        {
            return GetSingleDelivery(systems & DTV_DELGROUP_CABLE);
        }
        else if (!strcasecmp (scheme, "satellite"))
        {
            return GetSingleDelivery(systems & DTV_DELGROUP_SAT);
        }
        else if (!strcasecmp (scheme, "terrestrial"))
        {
            return GetSingleDelivery(systems & DTV_DELGROUP_TERRES);
        }
        else
        {
            /* Only standards family or nothing is specified */
            return GetSingleDelivery(systems);
        }
    }

    return DTV_DELIVERY_NONE;
}