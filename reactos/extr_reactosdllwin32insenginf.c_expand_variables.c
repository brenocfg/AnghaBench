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
struct inf_file {int dummy; } ;

/* Variables and functions */
 int expand_variables_buffer (struct inf_file*,char const*,char*) ; 
 char* heap_alloc (int) ; 

__attribute__((used)) static char *expand_variables(struct inf_file *inf, const char *str)
{
    char *buffer;
    int len;

    len = expand_variables_buffer(inf, str, NULL);
    buffer = heap_alloc(len);
    if (!len) return NULL;

    expand_variables_buffer(inf, str, buffer);
    return buffer;
}