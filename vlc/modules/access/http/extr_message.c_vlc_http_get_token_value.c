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
 int /*<<< orphan*/  assert (int) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strspn (char const*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 char* vlc_http_get_token (char const*,char const*) ; 
 size_t vlc_http_quoted_length (char const*) ; 
 int /*<<< orphan*/  vlc_http_token_length (char const*) ; 

__attribute__((used)) static char *vlc_http_get_token_value(const char *value, const char *token)
{
    value = vlc_http_get_token(value, token);
    if (value == NULL)
        return NULL;

    value += vlc_http_token_length(value);
    value += strspn(value, " \t"); /* BWS */

    if (*value != '=')
        return NULL;

    value++;
    value += strspn(value, " \t"); /* BWS */

    size_t len = vlc_http_quoted_length(value);
    if (len == 0)
        return NULL;

    assert(len >= 2);
    value++;
    len -= 2;

    char *out = malloc(len + 1), *p;
    if (unlikely(out == NULL))
        return NULL;

    for (p = out; len > 0; len--)
    {
        char c = *(value++);
        if (c == '\\') /* Quoted pair */
        {
            c = *(value++);
            len--;
        }
        *(p++) = c;
    }
    *p = '\0';
    return out;
}