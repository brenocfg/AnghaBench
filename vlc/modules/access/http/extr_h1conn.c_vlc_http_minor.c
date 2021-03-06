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
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static int vlc_http_minor(const char *msg)
{
    int minor;

    if (sscanf(msg, "HTTP/1.%1d", &minor) == 1)
        return minor;
    return -1;
}