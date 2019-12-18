#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int input_components; int num_components; int write_JFIF_header; TYPE_1__* comp_info; void* jpeg_color_space; void* in_color_space; } ;
struct TYPE_6__ {int h_samp_factor; int v_samp_factor; } ;
typedef  void* J_COLOR_SPACE ;

/* Variables and functions */
 TYPE_2__ Compressor ; 
 int /*<<< orphan*/  FatalError (char*) ; 
 void* JCS_CMYK ; 
 void* JCS_GRAYSCALE ; 
 void* JCS_RGB ; 
 void* JCS_YCCK ; 
 void* JCS_YCbCr ; 
#define  PT_CMYK 132 
#define  PT_GRAY 131 
#define  PT_Lab 130 
#define  PT_RGB 129 
#define  PT_YCbCr 128 
 int jpegQuality ; 
 int /*<<< orphan*/  jpeg_set_colorspace (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  jpeg_set_defaults (TYPE_2__*) ; 
 int /*<<< orphan*/  jpeg_set_quality (TYPE_2__*,int,int) ; 

__attribute__((used)) static
void WriteOutputFields(int OutputColorSpace)
{
    J_COLOR_SPACE in_space, jpeg_space;
    int components;

    switch (OutputColorSpace) {

    case PT_GRAY: in_space = jpeg_space = JCS_GRAYSCALE;
                  components = 1;
                  break;

    case PT_RGB:  in_space = JCS_RGB;
                  jpeg_space = JCS_YCbCr;
                  components = 3;
                  break;       // red/green/blue

    case PT_YCbCr: in_space = jpeg_space = JCS_YCbCr;
                   components = 3;
                   break;               // Y/Cb/Cr (also known as YUV)

    case PT_CMYK: in_space = JCS_CMYK;
                  jpeg_space = JCS_YCCK;
                  components = 4;
                  break;      // C/M/Y/components

    case PT_Lab:  in_space = jpeg_space = JCS_YCbCr;
                  components = 3;
                  break;                // Fake to don't touch
    default:
                 FatalError("Unsupported output color space");
                 return;
    }


    if (jpegQuality >= 100) {

     // avoid destructive conversion when asking for lossless compression
        jpeg_space = in_space;
    }

    Compressor.in_color_space =  in_space;
    Compressor.jpeg_color_space = jpeg_space;
    Compressor.input_components = Compressor.num_components = components;
    jpeg_set_defaults(&Compressor);
    jpeg_set_colorspace(&Compressor, jpeg_space);


    // Make sure to pass resolution through
    if (OutputColorSpace == PT_CMYK)
        Compressor.write_JFIF_header = 1;

    // Avoid subsampling on high quality factor
    jpeg_set_quality(&Compressor, jpegQuality, 1);
    if (jpegQuality >= 70) {

      int i;
      for(i=0; i < Compressor.num_components; i++) {

            Compressor.comp_info[i].h_samp_factor = 1;
            Compressor.comp_info[i].v_samp_factor = 1;
      }

    }

}