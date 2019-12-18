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
struct pattern {scalar_t__ regex; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pattern*) ; 
 int /*<<< orphan*/  pcre_free (scalar_t__) ; 

__attribute__((used)) static void pattern_destroy(struct pattern *pattern) {
	if (pattern) {
		if (pattern->regex) {
			pcre_free(pattern->regex);
		}
		free(pattern);
	}
}