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
 int /*<<< orphan*/  g_assert (int) ; 
 char* g_strdup (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static inline char *
hb_test_normalize_path (const char *path)
{
  char *s, *p;

  g_assert (0 == strncmp (path, "test_", 5));
  path += 4;

  s = g_strdup (path);
  for (p = s; *p; p++)
    if (*p == '_')
      *p = '/';

  return s;
}