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
 scalar_t__ STBDS_REALLOC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *stbds_strdup(char *str)
{
  // to keep replaceable allocator simple, we don't want to use strdup.
  // rolling our own also avoids problem of strdup vs _strdup
  size_t len = strlen(str)+1;
  char *p = (char*) STBDS_REALLOC(NULL, 0, len);
  memmove(p, str, len);
  return p;
}