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
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

uint8_t *hex_string_to_bin(char *hex_string)
{
    if (strlen(hex_string) % 2 != 0) {
        return NULL;
    }

    size_t len = strlen(hex_string) / 2;
    uint8_t *ret = malloc(len);

    char *pos = hex_string;
    size_t i;

    for (i = 0; i < len; ++i, pos += 2) {
        sscanf(pos, "%2hhx", &ret[i]);
    }

    return ret;
}