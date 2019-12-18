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
typedef  int uint32_t ;

/* Variables and functions */
 int* foldkeys ; 
 int lj_rol (int,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int nkeys ; 

__attribute__((used)) static int tryhash(uint32_t *htab, uint32_t sz, uint32_t r, int dorol)
{
  uint32_t i;
  if (dorol && ((r & 31) == 0 || (r>>5) == 0))
    return 0;  /* Avoid zero rotates. */
  memset(htab, 0xff, (sz+1)*sizeof(uint32_t));
  for (i = 0; i < nkeys; i++) {
    uint32_t key = foldkeys[i];
    uint32_t k = key & 0xffffff;
    uint32_t h = (dorol ? lj_rol(lj_rol(k, r>>5) - k, r&31) :
			  (((k << (r>>5)) - k) << (r&31))) % sz;
    if (htab[h] != 0xffffffff) {  /* Collision on primary slot. */
      if (htab[h+1] != 0xffffffff) {  /* Collision on secondary slot. */
	/* Try to move the colliding key, if possible. */
	if (h < sz-1 && htab[h+2] == 0xffffffff) {
	  uint32_t k2 = htab[h+1] & 0xffffff;
	  uint32_t h2 = (dorol ? lj_rol(lj_rol(k2, r>>5) - k2, r&31) :
				 (((k2 << (r>>5)) - k2) << (r&31))) % sz;
	  if (h2 != h+1) return 0;  /* Cannot resolve collision. */
	  htab[h+2] = htab[h+1];  /* Move colliding key to secondary slot. */
	} else {
	  return 0;  /* Collision. */
	}
      }
      htab[h+1] = key;
    } else {
      htab[h] = key;
    }
  }
  return 1;  /* Success, all keys could be stored. */
}