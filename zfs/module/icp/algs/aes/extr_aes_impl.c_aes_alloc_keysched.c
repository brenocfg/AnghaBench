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
typedef  void aes_key_t ;

/* Variables and functions */
 scalar_t__ kmem_alloc (int,int) ; 

void *
aes_alloc_keysched(size_t *size, int kmflag)
{
	aes_key_t *keysched;

	keysched = (aes_key_t *)kmem_alloc(sizeof (aes_key_t), kmflag);
	if (keysched != NULL) {
		*size = sizeof (aes_key_t);
		return (keysched);
	}
	return (NULL);
}