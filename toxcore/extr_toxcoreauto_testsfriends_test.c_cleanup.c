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
 int /*<<< orphan*/  child_id ; 
 int /*<<< orphan*/  crypto_box_PUBLICKEYBYTES ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent_id ; 
 int /*<<< orphan*/  puts (char*) ; 

void cleanup(void)
{
    munmap(parent_id, crypto_box_PUBLICKEYBYTES);
    munmap(child_id, crypto_box_PUBLICKEYBYTES);
    puts("============= END TEST =============");
}