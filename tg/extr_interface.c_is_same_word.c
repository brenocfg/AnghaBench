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
 int /*<<< orphan*/  memcmp (char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

int is_same_word (const char *s, size_t l, const char *word) {
  return s && word && strlen (word) == l && !memcmp (s, word, l);
}