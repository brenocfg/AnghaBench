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
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char const*,size_t const) ; 
 char* vlc_http_next_token (char const*) ; 
 size_t const vlc_http_token_length (char const*) ; 

__attribute__((used)) static const char *vlc_http_get_token(const char *value, const char *token)
{
    const size_t length = strlen(token);

    while (value != NULL)
    {
        if (vlc_http_token_length(value) == length
         && !strncasecmp(token, value, length))
            return value;

        value = vlc_http_next_token(value);
    }

    return NULL;
}