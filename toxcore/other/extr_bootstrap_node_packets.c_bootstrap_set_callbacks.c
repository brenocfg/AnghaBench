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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  Networking_Core ;

/* Variables and functions */
 int /*<<< orphan*/  BOOTSTRAP_INFO_PACKET_ID ; 
 scalar_t__ MAX_MOTD_LENGTH ; 
 int /*<<< orphan*/  bootstrap_motd ; 
 scalar_t__ bootstrap_motd_length ; 
 int /*<<< orphan*/  bootstrap_version ; 
 int /*<<< orphan*/  handle_info_request ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  networking_registerhandler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int bootstrap_set_callbacks(Networking_Core *net, uint32_t version, uint8_t *motd, uint16_t motd_length)
{
    if (motd_length > MAX_MOTD_LENGTH)
        return -1;

    bootstrap_version = htonl(version);
    memcpy(bootstrap_motd, motd, motd_length);
    bootstrap_motd_length = motd_length;

    networking_registerhandler(net, BOOTSTRAP_INFO_PACKET_ID, &handle_info_request, net);
    return 0;
}