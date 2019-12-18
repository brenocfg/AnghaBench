#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  assoc6; int /*<<< orphan*/  assoc4; } ;
struct TYPE_10__ {TYPE_2__ client; } ;
struct TYPE_7__ {scalar_t__ family; } ;
struct TYPE_9__ {TYPE_1__ ip; } ;
typedef  TYPE_3__ IP_Port ;
typedef  int /*<<< orphan*/  IPPTsPng ;
typedef  TYPE_4__ Client_entry ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 

__attribute__((used)) static IPPTsPng *entry_assoc(Client_entry *cl_entry, const IP_Port *ipp)
{
    if (!cl_entry)
        return NULL;

    if (ipp->ip.family == AF_INET)
        return &cl_entry->client.assoc4;

    if (ipp->ip.family == AF_INET6)
        return &cl_entry->client.assoc6;

    return NULL;
}