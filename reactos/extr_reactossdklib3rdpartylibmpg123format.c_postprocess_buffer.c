#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dec_enc; int /*<<< orphan*/  encoding; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer; TYPE_1__ af; } ;
typedef  TYPE_2__ mpg123_handle ;

/* Variables and functions */
#define  MPG123_ENC_FLOAT_32 134 
#define  MPG123_ENC_SIGNED_16 133 
#define  MPG123_ENC_SIGNED_24 132 
#define  MPG123_ENC_SIGNED_32 131 
#define  MPG123_ENC_UNSIGNED_16 130 
#define  MPG123_ENC_UNSIGNED_24 129 
#define  MPG123_ENC_UNSIGNED_32 128 
 int /*<<< orphan*/  chop_fourth_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conv_s16_to_f32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conv_s16_to_s32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conv_s16_to_u16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conv_s32_to_u32 (int /*<<< orphan*/ *) ; 

void postprocess_buffer(mpg123_handle *fr)
{
	/*
		This caters for the final output formats that are never produced by
		decoder synth directly (wide unsigned and 24 bit formats) or that are
		missing because of limited decoder precision (16 bit synth but 32 or
		24 bit output).
	*/
	switch(fr->af.dec_enc)
	{
#ifndef NO_32BIT
	case MPG123_ENC_SIGNED_32:
		switch(fr->af.encoding)
		{
		case MPG123_ENC_UNSIGNED_32:
			conv_s32_to_u32(&fr->buffer);
		break;
		case MPG123_ENC_UNSIGNED_24:
			conv_s32_to_u32(&fr->buffer);
			chop_fourth_byte(&fr->buffer);
		break;
		case MPG123_ENC_SIGNED_24:
			chop_fourth_byte(&fr->buffer);
		break;
		}
	break;
#endif
#ifndef NO_16BIT
	case MPG123_ENC_SIGNED_16:
		switch(fr->af.encoding)
		{
		case MPG123_ENC_UNSIGNED_16:
			conv_s16_to_u16(&fr->buffer);
		break;
#ifndef NO_REAL
		case MPG123_ENC_FLOAT_32:
			conv_s16_to_f32(&fr->buffer);
		break;
#endif
#ifndef NO_32BIT
		case MPG123_ENC_SIGNED_32:
			conv_s16_to_s32(&fr->buffer);
		break;
		case MPG123_ENC_UNSIGNED_32:
			conv_s16_to_s32(&fr->buffer);
			conv_s32_to_u32(&fr->buffer);
		break;
		case MPG123_ENC_UNSIGNED_24:
			conv_s16_to_s32(&fr->buffer);
			conv_s32_to_u32(&fr->buffer);
			chop_fourth_byte(&fr->buffer);
		break;
		case MPG123_ENC_SIGNED_24:
			conv_s16_to_s32(&fr->buffer);
			chop_fourth_byte(&fr->buffer);
		break;
#endif
		}
	break;
#endif
	}
}