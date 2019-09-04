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
typedef  size_t uint32_t ;

/* Variables and functions */
 int SIZEOF_FIELD ; 
 int SIZEOF_HEADER ; 
 size_t SIZEOF_LENGTH ; 
 size_t todword (int /*<<< orphan*/  const*) ; 
 int toword (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
struct_field(const uint8_t * stream, size_t sz) {
	const uint8_t * field;
	int fn, header, i;
	if (sz < SIZEOF_LENGTH)
		return -1;
	fn = toword(stream);
	header = SIZEOF_HEADER + SIZEOF_FIELD * fn;
	if (sz < header)
		return -1;
	field = stream + SIZEOF_HEADER;
	sz -= header;
	stream += header;
	for (i=0;i<fn;i++) {
		int value= toword(field + i * SIZEOF_FIELD);
		uint32_t dsz;
		if (value != 0)
			continue;
		if (sz < SIZEOF_LENGTH)
			return -1;
		dsz = todword(stream);
		if (sz < SIZEOF_LENGTH + dsz)
			return -1;
		stream += SIZEOF_LENGTH + dsz;
		sz -= SIZEOF_LENGTH + dsz;
	}

	return fn;
}