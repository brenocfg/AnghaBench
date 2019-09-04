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
typedef  int /*<<< orphan*/  langs ;
typedef  int /*<<< orphan*/  lang_spec_t ;

/* Variables and functions */

size_t get_lang_count() {
    return sizeof(langs) / sizeof(lang_spec_t);
}