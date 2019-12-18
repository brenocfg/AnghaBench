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
typedef  int MMBMPStringError ;

/* Variables and functions */
#define  MMMBMPStringEncodeError 133 
#define  kMMBMPStringCompressError 132 
#define  kMMBMPStringDecodeError 131 
#define  kMMBMPStringDecompressError 130 
#define  kMMBMPStringInvalidHeaderError 129 
#define  kMMBMPStringSizeError 128 

const char *MMBitmapStringErrorString(MMBMPStringError err)
{
	switch (err) {
		case kMMBMPStringInvalidHeaderError:
			return "Invalid header for string";
		case kMMBMPStringDecodeError:
			return "Error decoding string";
		case kMMBMPStringDecompressError:
			return "Error decompressing string";
		case kMMBMPStringSizeError:
			return "String not of expected size";
		case MMMBMPStringEncodeError:
			return "Error encoding string";
		case kMMBMPStringCompressError:
			return "Error compressing string";
		default:
			return NULL;
	}
}