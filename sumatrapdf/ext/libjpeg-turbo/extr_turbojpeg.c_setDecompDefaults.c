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
struct jpeg_decompress_struct {int /*<<< orphan*/  dct_method; int /*<<< orphan*/  out_color_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  JCS_EXT_ABGR ; 
 int /*<<< orphan*/  JCS_EXT_ARGB ; 
 int /*<<< orphan*/  JCS_EXT_BGR ; 
 int /*<<< orphan*/  JCS_EXT_BGRA ; 
 int /*<<< orphan*/  JCS_EXT_BGRX ; 
 int /*<<< orphan*/  JCS_EXT_RGB ; 
 int /*<<< orphan*/  JCS_EXT_RGBA ; 
 int /*<<< orphan*/  JCS_EXT_RGBX ; 
 int /*<<< orphan*/  JCS_EXT_XBGR ; 
 int /*<<< orphan*/  JCS_EXT_XRGB ; 
 int /*<<< orphan*/  JCS_GRAYSCALE ; 
 int /*<<< orphan*/  JCS_RGB ; 
 int /*<<< orphan*/  JDCT_FASTEST ; 
 int TJFLAG_FASTDCT ; 
#define  TJPF_ABGR 138 
#define  TJPF_ARGB 137 
#define  TJPF_BGR 136 
#define  TJPF_BGRA 135 
#define  TJPF_BGRX 134 
#define  TJPF_GRAY 133 
#define  TJPF_RGB 132 
#define  TJPF_RGBA 131 
#define  TJPF_RGBX 130 
#define  TJPF_XBGR 129 
#define  TJPF_XRGB 128 
 int /*<<< orphan*/  _throw (char*) ; 

__attribute__((used)) static int setDecompDefaults(struct jpeg_decompress_struct *dinfo,
	int pixelFormat, int flags)
{
	int retval=0;

	switch(pixelFormat)
	{
		case TJPF_GRAY:
			dinfo->out_color_space=JCS_GRAYSCALE;  break;
		#if JCS_EXTENSIONS==1
		case TJPF_RGB:
			dinfo->out_color_space=JCS_EXT_RGB;  break;
		case TJPF_BGR:
			dinfo->out_color_space=JCS_EXT_BGR;  break;
		case TJPF_RGBX:
			dinfo->out_color_space=JCS_EXT_RGBX;  break;
		case TJPF_BGRX:
			dinfo->out_color_space=JCS_EXT_BGRX;  break;
		case TJPF_XRGB:
			dinfo->out_color_space=JCS_EXT_XRGB;  break;
		case TJPF_XBGR:
			dinfo->out_color_space=JCS_EXT_XBGR;  break;
		#if JCS_ALPHA_EXTENSIONS==1
		case TJPF_RGBA:
			dinfo->out_color_space=JCS_EXT_RGBA;  break;
		case TJPF_BGRA:
			dinfo->out_color_space=JCS_EXT_BGRA;  break;
		case TJPF_ARGB:
			dinfo->out_color_space=JCS_EXT_ARGB;  break;
		case TJPF_ABGR:
			dinfo->out_color_space=JCS_EXT_ABGR;  break;
		#endif
		#else
		case TJPF_RGB:
		case TJPF_BGR:
		case TJPF_RGBX:
		case TJPF_BGRX:
		case TJPF_XRGB:
		case TJPF_XBGR:
		case TJPF_RGBA:
		case TJPF_BGRA:
		case TJPF_ARGB:
		case TJPF_ABGR:
			dinfo->out_color_space=JCS_RGB;  break;
		#endif
		default:
			_throw("Unsupported pixel format");
	}

	if(flags&TJFLAG_FASTDCT) dinfo->dct_method=JDCT_FASTEST;

	bailout:
	return retval;
}