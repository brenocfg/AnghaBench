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
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,unsigned int) ; 
 int /*<<< orphan*/  g_test_bug (char*) ; 
 int /*<<< orphan*/  g_test_bug_base (char const*) ; 

__attribute__((used)) static inline void
hb_test_bug (const char *uri_base, unsigned int number)
{
  char *s = g_strdup_printf ("%u", number);

  g_test_bug_base (uri_base);
  g_test_bug (s);

  g_free (s);
}