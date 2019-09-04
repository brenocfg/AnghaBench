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
typedef  int uint8_t ;

/* Variables and functions */
 int ADV_END ; 
 size_t ADV_LEN ; 
 int ADV_SIZE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  cleanup_adv (int*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 
 int /*<<< orphan*/  memmove (int*,int*,size_t) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 
 int* syslinux_adv ; 

int syslinux_setadv(int tag, size_t size, const void *data)
{
    uint8_t *p;
    size_t left;
    uint8_t advtmp[ADV_SIZE];

    if ((unsigned)tag - 1 > 254) {
	errno = EINVAL;
	return -1;		/* Impossible tag value */
    }

    if (size > 255) {
	errno = ENOSPC;		/* Max 255 bytes for a data item */
	return -1;
    }

    left = ADV_LEN;
    p = advtmp;
    memcpy(p, syslinux_adv + 2 * 4, left);	/* Make working copy */

    while (left >= 2) {
	uint8_t ptag = p[0];
	size_t plen = p[1] + 2;

	if (ptag == ADV_END)
	    break;

	if (ptag == tag) {
	    /* Found our tag.  Delete it. */

	    if (plen >= left) {
		/* Entire remainder is our tag */
		break;
	    }
	    memmove(p, p + plen, left - plen);
	} else {
	    /* Not our tag */
	    if (plen > left)
		break;		/* Corrupt tag (overrun) - overwrite it */

	    left -= plen;
	    p += plen;
	}
    }

    /* Now (p, left) reflects the position to write in and how much space
       we have for our data. */

    if (size) {
	if (left < size + 2) {
	    errno = ENOSPC;	/* Not enough space for data */
	    return -1;
	}

	*p++ = tag;
	*p++ = size;
	memcpy(p, data, size);
	p += size;
	left -= size + 2;
    }

    memset(p, 0, left);

    /* If we got here, everything went OK, commit the write */
    memcpy(syslinux_adv + 2 * 4, advtmp, ADV_LEN);
    cleanup_adv(syslinux_adv);

    return 0;
}