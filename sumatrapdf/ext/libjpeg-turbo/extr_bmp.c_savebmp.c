#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  output_message; int /*<<< orphan*/  error_exit; } ;
struct my_error_mgr {int /*<<< orphan*/  setjmp_buffer; TYPE_6__ pub; } ;
struct jpeg_decompress_struct {int out_color_components; int output_components; int image_width; int image_height; int scale_num; int scale_denom; scalar_t__ output_scanline; scalar_t__ output_height; TYPE_1__* mem; int /*<<< orphan*/  global_state; int /*<<< orphan*/  out_color_space; int /*<<< orphan*/  err; } ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  TYPE_2__* djpeg_dest_ptr ;
struct TYPE_10__ {int buffer_height; int /*<<< orphan*/  (* finish_output ) (struct jpeg_decompress_struct*,TYPE_2__*) ;int /*<<< orphan*/  (* put_pixel_rows ) (struct jpeg_decompress_struct*,TYPE_2__*,int) ;int /*<<< orphan*/ * buffer; int /*<<< orphan*/  (* start_output ) (struct jpeg_decompress_struct*,TYPE_2__*) ;int /*<<< orphan*/ * output_file; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* realize_virt_arrays ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DSTATE_READY ; 
 int /*<<< orphan*/  JCS_GRAYSCALE ; 
 int /*<<< orphan*/  JCS_RGB ; 
 int TJPF_GRAY ; 
 int TJPF_RGB ; 
 int TJ_NUMPF ; 
 int /*<<< orphan*/  _throw (char*) ; 
 int /*<<< orphan*/  _throwunix (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 TYPE_2__* jinit_write_bmp (struct jpeg_decompress_struct*,int /*<<< orphan*/ ) ; 
 TYPE_2__* jinit_write_ppm (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_create_decompress (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_destroy_decompress (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_std_error (TYPE_6__*) ; 
 int /*<<< orphan*/  memset (struct jpeg_decompress_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  my_error_exit ; 
 int /*<<< orphan*/  my_output_message ; 
 int /*<<< orphan*/  pixelconvert (unsigned char*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  stub1 (struct jpeg_decompress_struct*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct jpeg_decompress_struct*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub4 (struct jpeg_decompress_struct*,TYPE_2__*) ; 
 int* tjPixelSize ; 

int savebmp(char *filename, unsigned char *buf, int w, int h, int srcpf,
	int bottomup)
{
	int retval=0, srcps, dstpf;
	struct jpeg_decompress_struct dinfo;
	struct my_error_mgr jerr;
	djpeg_dest_ptr dst;
	FILE *file=NULL;
	char *ptr=NULL;

	memset(&dinfo, 0, sizeof(struct jpeg_decompress_struct));

	if(!filename || !buf || w<1 || h<1 || srcpf<0 || srcpf>=TJ_NUMPF)
		_throw("savebmp(): Invalid argument");

	if((file=fopen(filename, "wb"))==NULL)
		_throwunix("savebmp(): Cannot open output file");

	dinfo.err=jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit=my_error_exit;
	jerr.pub.output_message=my_output_message;

	if(setjmp(jerr.setjmp_buffer))
	{
		/* If we get here, the JPEG code has signaled an error. */
		retval=-1;  goto bailout;
	}

	jpeg_create_decompress(&dinfo);
	if(srcpf==TJPF_GRAY)
	{
		dinfo.out_color_components=dinfo.output_components=1;
		dinfo.out_color_space=JCS_GRAYSCALE;
	}
	else
	{
		dinfo.out_color_components=dinfo.output_components=3;
		dinfo.out_color_space=JCS_RGB;
	}
	dinfo.image_width=w;  dinfo.image_height=h;
	dinfo.global_state=DSTATE_READY;
	dinfo.scale_num=dinfo.scale_denom=1;

	ptr=strrchr(filename, '.');
	if(ptr && !strcasecmp(ptr, ".bmp"))
	{
		if((dst=jinit_write_bmp(&dinfo, 0))==NULL)
			_throw("savebmp(): Could not initialize bitmap writer");
	}
	else
	{
		if((dst=jinit_write_ppm(&dinfo))==NULL)
			_throw("savebmp(): Could not initialize PPM writer");
	}

	dst->output_file=file;
	(*dst->start_output)(&dinfo, dst);
	(*dinfo.mem->realize_virt_arrays)((j_common_ptr)&dinfo);

	if(srcpf==TJPF_GRAY) dstpf=srcpf;
	else dstpf=TJPF_RGB;
	srcps=tjPixelSize[srcpf];

	while(dinfo.output_scanline<dinfo.output_height)
	{
		int i, nlines=dst->buffer_height;
		for(i=0; i<nlines; i++)
		{
			unsigned char *inbuf;  int row;
			row=dinfo.output_scanline+i;
			if(bottomup) inbuf=&buf[(h-row-1)*w*srcps];
			else inbuf=&buf[row*w*srcps];
			pixelconvert(inbuf, srcpf, bottomup, dst->buffer[i], dstpf, 0, w,
				nlines);
		}
		(*dst->put_pixel_rows)(&dinfo, dst, nlines);
		dinfo.output_scanline+=nlines;
	}

	(*dst->finish_output)(&dinfo, dst);

	bailout:
	jpeg_destroy_decompress(&dinfo);
	if(file) fclose(file);
	return retval;
}