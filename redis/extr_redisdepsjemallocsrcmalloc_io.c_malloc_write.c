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
 int /*<<< orphan*/  je_malloc_message (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  wrtmessage (int /*<<< orphan*/ *,char const*) ; 

void
malloc_write(const char *s) {
	if (je_malloc_message != NULL) {
		je_malloc_message(NULL, s);
	} else {
		wrtmessage(NULL, s);
	}
}