#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_md5 ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ fz_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_md5_final (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  fz_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_md5_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
fz_md5_buffer(fz_context *ctx, fz_buffer *buffer, unsigned char digest[16])
{
	fz_md5 state;
	fz_md5_init(&state);
	if (buffer)
		fz_md5_update(&state, buffer->data, buffer->len);
	fz_md5_final(&state, digest);
}