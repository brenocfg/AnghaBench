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
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int SHORT_SCALE ; 
 int /*<<< orphan*/  bufsizeerr ; 
 int /*<<< orphan*/  error1 (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void conv_s16_to_f32(struct outbuffer *buf)
{
	ssize_t i;
	int16_t *in = (int16_t*) buf->data;
	float  *out = (float*)   buf->data;
	size_t count = buf->fill/sizeof(int16_t);
	/* Does that make any sense? In x86, there is an actual instruction to divide
	   float by integer ... but then, if we have that FPU, we don't really need
	   fixed point decoder hacks ...? */
	float scale = 1./SHORT_SCALE;

	if(buf->size < count*sizeof(float))
	{
		error1("%s", bufsizeerr);
		return;
	}

	/* Work from the back since output is bigger. */
	for(i=count-1; i>=0; --i)
	out[i] = (float)in[i] * scale;

	buf->fill = count*sizeof(float);
}