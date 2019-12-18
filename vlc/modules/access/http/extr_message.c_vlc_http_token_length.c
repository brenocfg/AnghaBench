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
 scalar_t__ vlc_http_istoken (char const) ; 

__attribute__((used)) static size_t vlc_http_token_length(const char *str)
{
    size_t i = 0;

    while (vlc_http_istoken(str[i]))
        i++;
    return i;
}