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
 size_t vlc_http_token_length (char const*) ; 

__attribute__((used)) static bool vlc_http_is_token(const char *str)
{
    size_t len = vlc_http_token_length(str);
    return len > 0 && str[len] == '\0';
}