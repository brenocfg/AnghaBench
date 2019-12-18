#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {float width; float height; scalar_t__ use_argb; int argb_stride; scalar_t__ argb; } ;
typedef  TYPE_1__ WebPPicture ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertToGray (TYPE_1__*) ; 
 int DiffScaleChannel (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int,float,float,int) ; 
 int /*<<< orphan*/  FREE_WARGV_AND_RETURN (int) ; 
 scalar_t__ GET_WARGV (char const**,int) ; 
 int /*<<< orphan*/  Help () ; 
 int /*<<< orphan*/  INIT_WARGV (int,char const**) ; 
 scalar_t__ ImgIoUtilWriteFile (char const*,int /*<<< orphan*/ *,size_t) ; 
 size_t ReadPicture (char const*,TYPE_1__*,int) ; 
 int SSIMScaleChannel (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int,int,float,float,int) ; 
 int /*<<< orphan*/  WebPBlendAlpha (TYPE_1__*,int) ; 
 size_t WebPEncodeLosslessBGRA (int /*<<< orphan*/  const*,float,float,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  WebPFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPPictureDistortion (TYPE_1__*,TYPE_1__*,int,float*) ; 
 int /*<<< orphan*/  WebPPictureFree (TYPE_1__*) ; 
 int /*<<< orphan*/  WebPPictureInit (TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,float,float,float,float,float,float) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int main(int argc, const char* argv[]) {
  WebPPicture pic1, pic2;
  size_t size1 = 0, size2 = 0;
  int ret = 1;
  float disto[5];
  int type = 0;
  int c;
  int help = 0;
  int keep_alpha = 0;
  int scale = 0;
  int use_gray = 0;
  const char* name1 = NULL;
  const char* name2 = NULL;
  const char* output = NULL;

  INIT_WARGV(argc, argv);

  if (!WebPPictureInit(&pic1) || !WebPPictureInit(&pic2)) {
    fprintf(stderr, "Can't init pictures\n");
    FREE_WARGV_AND_RETURN(1);
  }

  for (c = 1; c < argc; ++c) {
    if (!strcmp(argv[c], "-ssim")) {
      type = 1;
    } else if (!strcmp(argv[c], "-psnr")) {
      type = 0;
    } else if (!strcmp(argv[c], "-alpha")) {
      keep_alpha = 1;
    } else if (!strcmp(argv[c], "-scale")) {
      scale = 1;
    } else if (!strcmp(argv[c], "-gray")) {
      use_gray = 1;
    } else if (!strcmp(argv[c], "-h")) {
      help = 1;
      ret = 0;
    } else if (!strcmp(argv[c], "-o")) {
      if (++c == argc) {
        fprintf(stderr, "missing file name after %s option.\n", argv[c - 1]);
        goto End;
      }
      output = (const char*)GET_WARGV(argv, c);
    } else if (name1 == NULL) {
      name1 = (const char*)GET_WARGV(argv, c);
    } else {
      name2 = (const char*)GET_WARGV(argv, c);
    }
  }
  if (help || name1 == NULL || name2 == NULL) {
    if (!help) {
      fprintf(stderr, "Error: missing arguments.\n");
    }
    Help();
    goto End;
  }
  size1 = ReadPicture(name1, &pic1, 1);
  size2 = ReadPicture(name2, &pic2, 1);
  if (size1 == 0 || size2 == 0) goto End;

  if (!keep_alpha) {
    WebPBlendAlpha(&pic1, 0x00000000);
    WebPBlendAlpha(&pic2, 0x00000000);
  }

  if (!WebPPictureDistortion(&pic1, &pic2, type, disto)) {
    fprintf(stderr, "Error while computing the distortion.\n");
    goto End;
  }
  printf("%u %.2f    %.2f %.2f %.2f %.2f [ %.2f bpp ]\n",
         (unsigned int)size1,
         disto[4], disto[0], disto[1], disto[2], disto[3],
         8.f * size1 / pic1.width / pic1.height);

  if (output != NULL) {
    uint8_t* data = NULL;
    size_t data_size = 0;
    if (pic1.use_argb != pic2.use_argb) {
      fprintf(stderr, "Pictures are not in the same argb format. "
                      "Can't save the difference map.\n");
      goto End;
    }
    if (pic1.use_argb) {
      int n;
      fprintf(stderr, "max differences per channel: ");
      for (n = 0; n < 3; ++n) {    // skip the alpha channel
        const int range = (type == 1) ?
          SSIMScaleChannel((uint8_t*)pic1.argb + n, pic1.argb_stride * 4,
                           (const uint8_t*)pic2.argb + n, pic2.argb_stride * 4,
                           4, pic1.width, pic1.height, scale) :
          DiffScaleChannel((uint8_t*)pic1.argb + n, pic1.argb_stride * 4,
                           (const uint8_t*)pic2.argb + n, pic2.argb_stride * 4,
                           4, pic1.width, pic1.height, scale);
        if (range < 0) fprintf(stderr, "\nError computing diff map\n");
        fprintf(stderr, "[%d]", range);
      }
      fprintf(stderr, "\n");
      if (use_gray) ConvertToGray(&pic1);
    } else {
      fprintf(stderr, "Can only compute the difference map in ARGB format.\n");
      goto End;
    }
#if !defined(WEBP_REDUCE_CSP)
    data_size = WebPEncodeLosslessBGRA((const uint8_t*)pic1.argb,
                                       pic1.width, pic1.height,
                                       pic1.argb_stride * 4,
                                       &data);
    if (data_size == 0) {
      fprintf(stderr, "Error during lossless encoding.\n");
      goto End;
    }
    ret = ImgIoUtilWriteFile(output, data, data_size) ? 0 : 1;
    WebPFree(data);
    if (ret) goto End;
#else
    (void)data;
    (void)data_size;
    fprintf(stderr, "Cannot save the difference map. Please recompile "
                    "without the WEBP_REDUCE_CSP flag.\n");
#endif  // WEBP_REDUCE_CSP
  }
  ret = 0;

 End:
  WebPPictureFree(&pic1);
  WebPPictureFree(&pic2);
  FREE_WARGV_AND_RETURN(ret);
}