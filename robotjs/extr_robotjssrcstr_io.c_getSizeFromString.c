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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 size_t parseDimension (int /*<<< orphan*/  const*,size_t,size_t*) ; 

__attribute__((used)) static bool getSizeFromString(const uint8_t *buf, size_t buflen,
                              size_t *width, size_t *height,
                              size_t *len)
{
	size_t numlen;
	assert(buf != NULL);
	assert(width != NULL);
	assert(height != NULL);

	if ((*width = parseDimension(buf, buflen, &numlen)) == 0) {
		return false;
	}
	*len = numlen + 1;

	if ((*height = parseDimension(buf + *len, buflen, &numlen)) == 0) {
		return false;
	}
	*len += numlen + 1;

	return true;
}