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

/* Variables and functions */
 int /*<<< orphan*/  LOG_LEVEL_INFO ; 
 int crypto_box_PUBLICKEYBYTES ; 
 scalar_t__ sprintf (char*,char*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  write_log (int /*<<< orphan*/ ,char*,char*) ; 

void print_public_key(const uint8_t *public_key)
{
    char buffer[2 * crypto_box_PUBLICKEYBYTES + 1];
    int index = 0;

    size_t i;

    for (i = 0; i < crypto_box_PUBLICKEYBYTES; i++) {
        index += sprintf(buffer + index, "%02hhX", public_key[i]);
    }

    write_log(LOG_LEVEL_INFO, "Public Key: %s\n", buffer);

    return;
}