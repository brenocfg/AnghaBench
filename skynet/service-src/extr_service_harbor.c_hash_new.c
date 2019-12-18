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
struct hashmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct hashmap*,int /*<<< orphan*/ ,int) ; 
 struct hashmap* skynet_malloc (int) ; 

__attribute__((used)) static struct hashmap * 
hash_new() {
	struct hashmap * h = skynet_malloc(sizeof(struct hashmap));
	memset(h,0,sizeof(*h));
	return h;
}