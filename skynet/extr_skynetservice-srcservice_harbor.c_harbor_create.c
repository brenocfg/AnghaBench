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
struct harbor {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_new () ; 
 int /*<<< orphan*/  memset (struct harbor*,int /*<<< orphan*/ ,int) ; 
 struct harbor* skynet_malloc (int) ; 

struct harbor *
harbor_create(void) {
	struct harbor * h = skynet_malloc(sizeof(*h));
	memset(h,0,sizeof(*h));
	h->map = hash_new();
	return h;
}