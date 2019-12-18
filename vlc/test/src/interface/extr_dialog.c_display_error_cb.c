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
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 

__attribute__((used)) static void
display_error_cb(void *p_data, const char *psz_title, const char *psz_text)
{
    (void) p_data;
    printf("error message: title: '%s', text: '%s'\n", psz_title, psz_text);
}