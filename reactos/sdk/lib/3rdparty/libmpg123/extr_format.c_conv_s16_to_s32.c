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
struct outbuffer {int fill; size_t size; scalar_t__ data; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  S32_RESCALE ; 
 int /*<<< orphan*/  bufsizeerr ; 
 int /*<<< orphan*/  error1 (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void conv_s16_to_s32(struct outbuffer *buf)
{
	ssize_t i;
	int16_t  *in = (int16_t*) buf->data;
	int32_t *out = (int32_t*) buf->data;
	size_t count = buf->fill/sizeof(int16_t);

	if(buf->size < count*sizeof(int32_t))
	{
		error1("%s", bufsizeerr);
		return;
	}

	/* Work from the back since output is bigger. */
	for(i=count-1; i>=0; --i)
	{
		out[i] = in[i];
		/* Could just shift bytes, but would have to mess with sign bit. */
		out[i] *= S32_RESCALE;
	}

	buf->fill = count*sizeof(int32_t);
}