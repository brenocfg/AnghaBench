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
 char* vlc_uri_resolve (char*,char const*) ; 

__attribute__((used)) static char *vlc_uri_resolve_rfc3986_test(const char *in)
{
    return vlc_uri_resolve("http://a/b/c/d;p?q", in);
}