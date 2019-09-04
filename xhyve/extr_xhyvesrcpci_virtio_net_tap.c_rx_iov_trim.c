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
struct iovec {size_t iov_len; void* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static __inline struct iovec *
rx_iov_trim(struct iovec *iov, int *niov, int tlen)
{
	struct iovec *riov;

	/* XXX short-cut: assume first segment is >= tlen */
	assert(iov[0].iov_len >= ((size_t) tlen));

	iov[0].iov_len -= ((size_t) tlen);
	if (iov[0].iov_len == 0) {
		assert(*niov > 1);
		*niov -= 1;
		riov = &iov[1];
	} else {
		iov[0].iov_base = (void *)((uintptr_t)iov[0].iov_base +
			((size_t) tlen));
		riov = &iov[0];
	}

	return (riov);
}