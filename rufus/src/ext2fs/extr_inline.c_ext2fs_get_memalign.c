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
typedef  scalar_t__ errcode_t ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ EXT2_ET_NO_MEMORY ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (unsigned long) ; 
 void* memalign (unsigned long,unsigned long) ; 
 scalar_t__ posix_memalign (void**,unsigned long,unsigned long) ; 
 void* valloc (unsigned long) ; 

errcode_t ext2fs_get_memalign(unsigned long size,
			      unsigned long align, void *ptr)
{
	errcode_t retval = 0;
	void **p = ptr;

	if (align < 8)
		align = 8;
#ifdef HAVE_POSIX_MEMALIGN
	retval = posix_memalign(p, align, size);
	if (retval == ENOMEM)
		return EXT2_ET_NO_MEMORY;
#else  /* !HAVE_POSIX_MEMALIGN */
#ifdef HAVE_MEMALIGN
	*p = memalign(align, size);
	if (*p == NULL) {
		if (errno)
			return errno;
		else
			return EXT2_ET_NO_MEMORY;
	}
#else  /* !HAVE_MEMALIGN */
#ifdef HAVE_VALLOC
	if (align > sizeof(long long))
		*p = valloc(size);
	else
#endif
		*p = malloc(size);
	if ((uintptr_t) *p & (align - 1)) {
		free(*p);
		*p = 0;
	}
	if (*p == 0)
		return EXT2_ET_NO_MEMORY;
#endif	/* HAVE_MEMALIGN */
#endif	/* HAVE_POSIX_MEMALIGN */
	return retval;
}