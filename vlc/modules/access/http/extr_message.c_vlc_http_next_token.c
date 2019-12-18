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
 int /*<<< orphan*/  strcspn (char const*,char*) ; 
 int strspn (char const*,char*) ; 
 int /*<<< orphan*/  vlc_http_quoted_length (char const*) ; 

const char *vlc_http_next_token(const char *value)
{   /* We handle either token or token = token / quoted-string */
    value += strcspn(value, ",\"");
    if (!*value)
        return NULL;

    value += vlc_http_quoted_length(value);
    return value + strspn(value, "\t ,");
}