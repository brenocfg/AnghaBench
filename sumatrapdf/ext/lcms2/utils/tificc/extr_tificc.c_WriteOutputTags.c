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
typedef  int /*<<< orphan*/  uint16 ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int ChanCountFromPixelType (int) ; 
 int /*<<< orphan*/  EXTRASAMPLE_UNASSALPHA ; 
 int /*<<< orphan*/  FatalError (char*) ; 
 int INKSET_CMYK ; 
 int PHOTOMETRIC_CIELAB ; 
 int PHOTOMETRIC_MINISBLACK ; 
 int PHOTOMETRIC_RGB ; 
 int PHOTOMETRIC_SEPARATED ; 
#define  PT_CMY 146 
#define  PT_CMYK 145 
#define  PT_GRAY 144 
#define  PT_Lab 143 
#define  PT_MCH10 142 
#define  PT_MCH11 141 
#define  PT_MCH12 140 
#define  PT_MCH13 139 
#define  PT_MCH14 138 
#define  PT_MCH15 137 
#define  PT_MCH2 136 
#define  PT_MCH3 135 
#define  PT_MCH4 134 
#define  PT_MCH5 133 
#define  PT_MCH6 132 
#define  PT_MCH7 131 
#define  PT_MCH8 130 
#define  PT_MCH9 129 
#define  PT_RGB 128 
 int SAMPLEFORMAT_IEEEFP ; 
 int /*<<< orphan*/  StoreAsAlpha ; 
 int /*<<< orphan*/  TIFFSetField (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  TIFFTAG_BITSPERSAMPLE ; 
 int /*<<< orphan*/  TIFFTAG_EXTRASAMPLES ; 
 int /*<<< orphan*/  TIFFTAG_INKSET ; 
 int /*<<< orphan*/  TIFFTAG_NUMBEROFINKS ; 
 int /*<<< orphan*/  TIFFTAG_PHOTOMETRIC ; 
 int /*<<< orphan*/  TIFFTAG_SAMPLEFORMAT ; 
 int /*<<< orphan*/  TIFFTAG_SAMPLESPERPIXEL ; 
 int Width ; 

__attribute__((used)) static
void WriteOutputTags(TIFF *out, int Colorspace, int BytesPerSample)
{
    int BitsPerSample = (8 * BytesPerSample);
    int nChannels     = ChanCountFromPixelType(Colorspace);

    uint16 Extra[] = { EXTRASAMPLE_UNASSALPHA,
                       EXTRASAMPLE_UNASSALPHA,
                       EXTRASAMPLE_UNASSALPHA,
                       EXTRASAMPLE_UNASSALPHA,
                       EXTRASAMPLE_UNASSALPHA,
                       EXTRASAMPLE_UNASSALPHA,
                       EXTRASAMPLE_UNASSALPHA,
                       EXTRASAMPLE_UNASSALPHA,
                       EXTRASAMPLE_UNASSALPHA,
                       EXTRASAMPLE_UNASSALPHA,
                       EXTRASAMPLE_UNASSALPHA
    };


  switch (Colorspace) {

  case PT_GRAY:
      TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
      TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, 1);
      TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, BitsPerSample);
      break;

  case PT_RGB:
      TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
      TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, 3);
      TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, BitsPerSample);
      break;

  case PT_CMY:
      TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_SEPARATED);
      TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, 3);
      TIFFSetField(out, TIFFTAG_INKSET, 2);
      TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, BitsPerSample);
      break;

  case PT_CMYK:
      TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_SEPARATED);
      TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, 4);
      TIFFSetField(out, TIFFTAG_INKSET, INKSET_CMYK);
      TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, BitsPerSample);
      break;

  case PT_Lab:
      if (BitsPerSample == 16)
          TIFFSetField(out, TIFFTAG_PHOTOMETRIC, 9);
      else
          TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_CIELAB);
      TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, 3);
      TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, BitsPerSample);    // Needed by TIFF Spec
      break;


      // Multi-ink separations
  case PT_MCH2:
  case PT_MCH3:
  case PT_MCH4:
  case PT_MCH5:
  case PT_MCH6:
  case PT_MCH7:
  case PT_MCH8:
  case PT_MCH9:
  case PT_MCH10:
  case PT_MCH11:
  case PT_MCH12:
  case PT_MCH13:
  case PT_MCH14:
  case PT_MCH15:

      TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_SEPARATED);
      TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, nChannels);

      if (StoreAsAlpha && nChannels >= 4) {
          // CMYK plus extra alpha
          TIFFSetField(out, TIFFTAG_EXTRASAMPLES, nChannels - 4, Extra);
          TIFFSetField(out, TIFFTAG_INKSET, 1);
          TIFFSetField(out, TIFFTAG_NUMBEROFINKS, 4);
      }
      else {
          TIFFSetField(out, TIFFTAG_INKSET, 2);
          TIFFSetField(out, TIFFTAG_NUMBEROFINKS, nChannels);
      }

      TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, BitsPerSample);
      break;


  default:
      FatalError("Unsupported output colorspace");
    }

  if (Width == 32)
      TIFFSetField(out, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_IEEEFP);
}