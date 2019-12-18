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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  disk_identify_get_string (int /*<<< orphan*/ *,unsigned int,char*,size_t) ; 

__attribute__((used)) static void disk_identify_fixup_string(
                uint8_t identify[512],
                unsigned offset_words,
                size_t len) {
        disk_identify_get_string(identify, offset_words,
                                 (char *) identify + offset_words * 2, len);
}