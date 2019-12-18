#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct jpeg_compress_struct {TYPE_1__* comp_info; int /*<<< orphan*/  dct_method; int /*<<< orphan*/  input_components; int /*<<< orphan*/  in_color_space; } ;
struct TYPE_2__ {int h_samp_factor; int v_samp_factor; } ;

/* Variables and functions */
 int /*<<< orphan*/  JCS_EXT_BGR ; 
 int /*<<< orphan*/  JCS_EXT_BGRX ; 
 int /*<<< orphan*/  JCS_EXT_RGB ; 
 int /*<<< orphan*/  JCS_EXT_RGBX ; 
 int /*<<< orphan*/  JCS_EXT_XBGR ; 
 int /*<<< orphan*/  JCS_EXT_XRGB ; 
 int /*<<< orphan*/  JCS_GRAYSCALE ; 
 int /*<<< orphan*/  JCS_RGB ; 
 int /*<<< orphan*/  JCS_YCbCr ; 
 int /*<<< orphan*/  JDCT_FASTEST ; 
 int /*<<< orphan*/  JDCT_ISLOW ; 
 int TJFLAG_ACCURATEDCT ; 
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
 int TJSAMP_GRAY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  jpeg_set_colorspace (struct jpeg_compress_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_set_defaults (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_set_quality (struct jpeg_compress_struct*,int,int /*<<< orphan*/ ) ; 
 int* tjMCUHeight ; 
 int* tjMCUWidth ; 
 int /*<<< orphan*/ * tjPixelSize ; 

__attribute__((used)) static int setCompDefaults(struct jpeg_compress_struct *cinfo,
	int pixelFormat, int subsamp, int jpegQual, int flags)
{
	int retval=0;

	switch(pixelFormat)
	{
		case TJPF_GRAY:
			cinfo->in_color_space=JCS_GRAYSCALE;  break;
		#if JCS_EXTENSIONS==1
		case TJPF_RGB:
			cinfo->in_color_space=JCS_EXT_RGB;  break;
		case TJPF_BGR:
			cinfo->in_color_space=JCS_EXT_BGR;  break;
		case TJPF_RGBX:
		case TJPF_RGBA:
			cinfo->in_color_space=JCS_EXT_RGBX;  break;
		case TJPF_BGRX:
		case TJPF_BGRA:
			cinfo->in_color_space=JCS_EXT_BGRX;  break;
		case TJPF_XRGB:
		case TJPF_ARGB:
			cinfo->in_color_space=JCS_EXT_XRGB;  break;
		case TJPF_XBGR:
		case TJPF_ABGR:
			cinfo->in_color_space=JCS_EXT_XBGR;  break;
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
			cinfo->in_color_space=JCS_RGB;  pixelFormat=TJPF_RGB;
			break;
		#endif
	}

	cinfo->input_components=tjPixelSize[pixelFormat];
	jpeg_set_defaults(cinfo);
	if(jpegQual>=0)
	{
		jpeg_set_quality(cinfo, jpegQual, TRUE);
		if(jpegQual>=96 || flags&TJFLAG_ACCURATEDCT) cinfo->dct_method=JDCT_ISLOW;
		else cinfo->dct_method=JDCT_FASTEST;
	}
	if(subsamp==TJSAMP_GRAY)
		jpeg_set_colorspace(cinfo, JCS_GRAYSCALE);
	else
		jpeg_set_colorspace(cinfo, JCS_YCbCr);

	cinfo->comp_info[0].h_samp_factor=tjMCUWidth[subsamp]/8;
	cinfo->comp_info[1].h_samp_factor=1;
	cinfo->comp_info[2].h_samp_factor=1;
	cinfo->comp_info[0].v_samp_factor=tjMCUHeight[subsamp]/8;
	cinfo->comp_info[1].v_samp_factor=1;
	cinfo->comp_info[2].v_samp_factor=1;

	return retval;
}