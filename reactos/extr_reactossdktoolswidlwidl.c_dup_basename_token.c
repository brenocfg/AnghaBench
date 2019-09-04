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
 char* dup_basename (char const*,char const*) ; 
 int /*<<< orphan*/  isalnum (char) ; 

__attribute__((used)) static char *dup_basename_token(const char *name, const char *ext)
{
    char *p, *ret = dup_basename( name, ext );
    /* map invalid characters to '_' */
    for (p = ret; *p; p++) if (!isalnum(*p)) *p = '_';
    return ret;
}