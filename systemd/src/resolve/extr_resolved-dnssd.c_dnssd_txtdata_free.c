#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  txt; int /*<<< orphan*/  rr; } ;
typedef  TYPE_1__ DnssdTxtData ;

/* Variables and functions */
 int /*<<< orphan*/  dns_resource_record_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_txt_item_free_all (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 

DnssdTxtData *dnssd_txtdata_free(DnssdTxtData *txt_data) {
        if (!txt_data)
                return NULL;

        dns_resource_record_unref(txt_data->rr);
        dns_txt_item_free_all(txt_data->txt);

        return mfree(txt_data);
}