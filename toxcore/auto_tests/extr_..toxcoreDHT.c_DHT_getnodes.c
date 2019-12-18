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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  IP_Port ;
typedef  int /*<<< orphan*/  DHT ;

/* Variables and functions */
 int /*<<< orphan*/  getnodes (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

void DHT_getnodes(DHT *dht, const IP_Port *from_ipp, const uint8_t *from_id, const uint8_t *which_id)
{
    getnodes(dht, *from_ipp, from_id, which_id, NULL);
}