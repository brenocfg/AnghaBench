#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* items_next; } ;
typedef  TYPE_1__ DnssdTxtData ;

/* Variables and functions */
 int /*<<< orphan*/  dnssd_txtdata_free (TYPE_1__*) ; 

DnssdTxtData *dnssd_txtdata_free_all(DnssdTxtData *txt_data) {
        DnssdTxtData *next;

        if (!txt_data)
                return NULL;

        next = txt_data->items_next;

        dnssd_txtdata_free(txt_data);

        return dnssd_txtdata_free_all(next);
}