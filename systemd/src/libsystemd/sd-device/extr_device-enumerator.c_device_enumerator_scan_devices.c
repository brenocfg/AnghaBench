#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int scan_uptodate; scalar_t__ type; size_t n_devices; int /*<<< orphan*/ * devices; scalar_t__ match_parent; int /*<<< orphan*/  match_tag; } ;
typedef  TYPE_1__ sd_device_enumerator ;

/* Variables and functions */
 scalar_t__ DEVICE_ENUMERATION_TYPE_DEVICES ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  device_compare ; 
 int /*<<< orphan*/  device_enumerator_dedup_devices (TYPE_1__*) ; 
 int enumerator_scan_devices_all (TYPE_1__*) ; 
 int enumerator_scan_devices_children (TYPE_1__*) ; 
 int enumerator_scan_devices_tags (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_device_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_isempty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typesafe_qsort (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

int device_enumerator_scan_devices(sd_device_enumerator *enumerator) {
        int r = 0, k;
        size_t i;

        assert(enumerator);

        if (enumerator->scan_uptodate &&
            enumerator->type == DEVICE_ENUMERATION_TYPE_DEVICES)
                return 0;

        for (i = 0; i < enumerator->n_devices; i++)
                sd_device_unref(enumerator->devices[i]);

        enumerator->n_devices = 0;

        if (!set_isempty(enumerator->match_tag)) {
                k = enumerator_scan_devices_tags(enumerator);
                if (k < 0)
                        r = k;
        } else if (enumerator->match_parent) {
                k = enumerator_scan_devices_children(enumerator);
                if (k < 0)
                        r = k;
        } else {
                k = enumerator_scan_devices_all(enumerator);
                if (k < 0)
                        r = k;
        }

        typesafe_qsort(enumerator->devices, enumerator->n_devices, device_compare);
        device_enumerator_dedup_devices(enumerator);

        enumerator->scan_uptodate = true;
        enumerator->type = DEVICE_ENUMERATION_TYPE_DEVICES;

        return r;
}