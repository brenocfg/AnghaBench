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
 int /*<<< orphan*/  strlen (char const*) ; 
 char* vlc_b64_encode_binary (char const*,int /*<<< orphan*/ ) ; 

char *vlc_b64_encode(const char *src)
{
    if (src == NULL)
        src = "";
    return vlc_b64_encode_binary(src, strlen(src));
}