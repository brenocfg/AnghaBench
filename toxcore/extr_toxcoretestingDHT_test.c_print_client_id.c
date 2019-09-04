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
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

void print_client_id(uint8_t *public_key)
{
    uint32_t j;

    for (j = 0; j < crypto_box_PUBLICKEYBYTES; j++) {
        printf("%02hhX", public_key[j]);
    }
}