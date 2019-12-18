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
struct sym_key {char* ptr; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  strm_int ;
typedef  int khint_t ;

/* Variables and functions */

__attribute__((used)) static khint_t
sym_hash(struct sym_key key)
{
  const char *s = key.ptr;
  khint_t h;
  strm_int len = key.len;

  h = *s++;
  while (len--) {
    h = (h << 5) - h + (khint_t)*s++;
  }
  return h;
}