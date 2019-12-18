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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  void* uint32_t ;
struct TYPE_3__ {void* time_interleaving; void* segment_count; int /*<<< orphan*/  code_rate; int /*<<< orphan*/  modulation; } ;
typedef  TYPE_1__ isdbt_layer_t ;
typedef  int /*<<< orphan*/  dvb_device_t ;

/* Variables and functions */
 int dvb_set_isdbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int,void*,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  var_InheritCodeRate (int /*<<< orphan*/ *,char*) ; 
 void* var_InheritGuardInterval (int /*<<< orphan*/ *) ; 
 void* var_InheritInteger (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_InheritModulation (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int isdbt_setup (vlc_object_t *obj, dvb_device_t *dev, uint64_t freq)
{
    isdbt_layer_t layers[3];
    uint32_t guard = var_InheritGuardInterval (obj);
    uint32_t bw = var_InheritInteger (obj, "dvb-bandwidth");
    int tx = var_InheritInteger (obj, "dvb-transmission");

    for (unsigned i = 0; i < 3; i++)
    {
        char varname[sizeof ("dvb-X-interleaving")];
        memcpy (varname, "dvb-X-", 6);
        varname[4] = 'a' + i;

        strcpy (varname + 6, "modulation");
        layers[i].modulation = var_InheritModulation (obj, varname);
        strcpy (varname + 6, "fec");
        layers[i].code_rate = var_InheritCodeRate (obj, varname);
        strcpy (varname + 6, "count");
        layers[i].segment_count = var_InheritInteger (obj, varname);
        strcpy (varname + 6, "interleaving");
        layers[i].time_interleaving = var_InheritInteger (obj, varname);
    }

    return dvb_set_isdbt (dev, freq, bw, tx, guard, layers);
}