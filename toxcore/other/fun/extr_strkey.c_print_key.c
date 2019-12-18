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

/* Variables and functions */
 size_t crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stdout ; 

void print_key(unsigned char *key)
{
    size_t i;
    for (i = 0; i < crypto_box_PUBLICKEYBYTES; i++) {
        if (key[i] < 16) {
            fprintf(stdout, "0");
        }

        fprintf(stdout, "%hhX", key[i]);
    }
}