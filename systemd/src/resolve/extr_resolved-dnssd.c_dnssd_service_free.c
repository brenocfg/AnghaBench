#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name_template; int /*<<< orphan*/  type; int /*<<< orphan*/  name; int /*<<< orphan*/  filename; int /*<<< orphan*/  txt_data_items; int /*<<< orphan*/  srv_rr; int /*<<< orphan*/  ptr_rr; TYPE_1__* manager; } ;
struct TYPE_7__ {int /*<<< orphan*/  dnssd_services; } ;
typedef  TYPE_2__ DnssdService ;

/* Variables and functions */
 int /*<<< orphan*/  dns_resource_record_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnssd_txtdata_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 

DnssdService *dnssd_service_free(DnssdService *service) {
        if (!service)
                return NULL;

        if (service->manager)
                hashmap_remove(service->manager->dnssd_services, service->name);

        dns_resource_record_unref(service->ptr_rr);
        dns_resource_record_unref(service->srv_rr);

        dnssd_txtdata_free_all(service->txt_data_items);

        free(service->filename);
        free(service->name);
        free(service->type);
        free(service->name_template);

        return mfree(service);
}