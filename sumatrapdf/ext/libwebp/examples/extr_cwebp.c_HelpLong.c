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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void HelpLong(void) {
  printf("Usage:\n");
  printf(" cwebp [-preset <...>] [options] in_file [-o out_file]\n\n");
  printf("If input size (-s) for an image is not specified, it is\n"
         "assumed to be a PNG, JPEG, TIFF or WebP file.\n");
#ifdef HAVE_WINCODEC_H
  printf("Windows builds can take as input any of the files handled by WIC.\n");
#endif
  printf("\nOptions:\n");
  printf("  -h / -help ............. short help\n");
  printf("  -H / -longhelp ......... long help\n");
  printf("  -q <float> ............. quality factor (0:small..100:big), "
         "default=75\n");
  printf("  -alpha_q <int> ......... transparency-compression quality (0..100),"
         "\n                           default=100\n");
  printf("  -preset <string> ....... preset setting, one of:\n");
  printf("                            default, photo, picture,\n");
  printf("                            drawing, icon, text\n");
  printf("     -preset must come first, as it overwrites other parameters\n");
  printf("  -z <int> ............... activates lossless preset with given\n"
         "                           level in [0:fast, ..., 9:slowest]\n");
  printf("\n");
  printf("  -m <int> ............... compression method (0=fast, 6=slowest), "
         "default=4\n");
  printf("  -segments <int> ........ number of segments to use (1..4), "
         "default=4\n");
  printf("  -size <int> ............ target size (in bytes)\n");
  printf("  -psnr <float> .......... target PSNR (in dB. typically: 42)\n");
  printf("\n");
  printf("  -s <int> <int> ......... input size (width x height) for YUV\n");
  printf("  -sns <int> ............. spatial noise shaping (0:off, 100:max), "
         "default=50\n");
  printf("  -f <int> ............... filter strength (0=off..100), "
         "default=60\n");
  printf("  -sharpness <int> ....... "
         "filter sharpness (0:most .. 7:least sharp), default=0\n");
  printf("  -strong ................ use strong filter instead "
                                     "of simple (default)\n");
  printf("  -nostrong .............. use simple filter instead of strong\n");
  printf("  -sharp_yuv ............. use sharper (and slower) RGB->YUV "
                                     "conversion\n");
  printf("  -partition_limit <int> . limit quality to fit the 512k limit on\n");
  printf("                           "
         "the first partition (0=no degradation ... 100=full)\n");
  printf("  -pass <int> ............ analysis pass number (1..10)\n");
  printf("  -crop <x> <y> <w> <h> .. crop picture with the given rectangle\n");
  printf("  -resize <w> <h> ........ resize picture (after any cropping)\n");
  printf("  -mt .................... use multi-threading if available\n");
  printf("  -low_memory ............ reduce memory usage (slower encoding)\n");
  printf("  -map <int> ............. print map of extra info\n");
  printf("  -print_psnr ............ prints averaged PSNR distortion\n");
  printf("  -print_ssim ............ prints averaged SSIM distortion\n");
  printf("  -print_lsim ............ prints local-similarity distortion\n");
  printf("  -d <file.pgm> .......... dump the compressed output (PGM file)\n");
  printf("  -alpha_method <int> .... transparency-compression method (0..1), "
         "default=1\n");
  printf("  -alpha_filter <string> . predictive filtering for alpha plane,\n");
  printf("                           one of: none, fast (default) or best\n");
  printf("  -exact ................. preserve RGB values in transparent area, "
         "default=off\n");
  printf("  -blend_alpha <hex> ..... blend colors against background color\n"
         "                           expressed as RGB values written in\n"
         "                           hexadecimal, e.g. 0xc0e0d0 for red=0xc0\n"
         "                           green=0xe0 and blue=0xd0\n");
  printf("  -noalpha ............... discard any transparency information\n");
  printf("  -lossless .............. encode image losslessly, default=off\n");
  printf("  -near_lossless <int> ... use near-lossless image\n"
         "                           preprocessing (0..100=off), "
         "default=100\n");
  printf("  -hint <string> ......... specify image characteristics hint,\n");
  printf("                           one of: photo, picture or graph\n");

  printf("\n");
  printf("  -metadata <string> ..... comma separated list of metadata to\n");
  printf("                           ");
  printf("copy from the input to the output if present.\n");
  printf("                           "
         "Valid values: all, none (default), exif, icc, xmp\n");

  printf("\n");
  printf("  -short ................. condense printed message\n");
  printf("  -quiet ................. don't print anything\n");
  printf("  -version ............... print version number and exit\n");
#ifndef WEBP_DLL
  printf("  -noasm ................. disable all assembly optimizations\n");
#endif
  printf("  -v ..................... verbose, e.g. print encoding/decoding "
         "times\n");
  printf("  -progress .............. report encoding progress\n");
  printf("\n");
  printf("Experimental Options:\n");
  printf("  -jpeg_like ............. roughly match expected JPEG size\n");
  printf("  -af .................... auto-adjust filter strength\n");
  printf("  -pre <int> ............. pre-processing filter\n");
  printf("\n");
}