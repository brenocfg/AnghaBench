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
struct optioninfo {scalar_t__ lopt; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static int oc_long(const char **optp, const struct optioninfo *entry) {
  return entry->lopt && !strcmp(*optp,entry->lopt);
}