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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void printpacket(uint8_t *data, uint32_t length, IP_Port ip_port)
{
    uint32_t i;
    printf("UNHANDLED PACKET RECEIVED\nLENGTH:%u\nCONTENTS:\n", length);
    printf("--------------------BEGIN-----------------------------\n");

    for (i = 0; i < length; i++) {
        if (data[i] < 16)
            printf("0");

        printf("%hhX", data[i]);
    }

    printf("\n--------------------END-----------------------------\n\n\n");
}