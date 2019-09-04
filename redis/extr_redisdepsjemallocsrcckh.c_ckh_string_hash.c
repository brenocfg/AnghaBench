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
 int /*<<< orphan*/  hash (void const*,int /*<<< orphan*/ ,int,size_t*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void
ckh_string_hash(const void *key, size_t r_hash[2]) {
	hash(key, strlen((const char *)key), 0x94122f33U, r_hash);
}