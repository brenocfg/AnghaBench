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
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static char *hpack_decode_str_raw(const uint8_t *data, size_t length)
{
    char *s = malloc(length + 1);
    if (s != NULL)
    {
        memcpy(s, data, length);
        s[length] = '\0';
    }
    return s;
}