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
typedef  int /*<<< orphan*/  DNS_Object ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void tox_dns3_kill(void *dns3_object)
{
    memset(dns3_object, 0, sizeof(DNS_Object));
    free(dns3_object);
}