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
struct plain_hashmap_entry {int dummy; } ;
typedef  int /*<<< orphan*/  Hashmap ;

/* Variables and functions */
 int /*<<< orphan*/  HASHMAP_BASE (int /*<<< orphan*/ *) ; 
 scalar_t__ bucket_at (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static struct plain_hashmap_entry *plain_bucket_at(Hashmap *h, unsigned idx) {
        return (struct plain_hashmap_entry*) bucket_at(HASHMAP_BASE(h), idx);
}