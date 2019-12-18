#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  out_file ;
typedef  int /*<<< orphan*/  image ;
typedef  int /*<<< orphan*/  WebPOutputFileFormat ;
struct TYPE_13__ {int stride; int size; int /*<<< orphan*/  rgba; } ;
struct TYPE_14__ {TYPE_2__ RGBA; } ;
struct TYPE_15__ {int is_external_memory; int width; int height; TYPE_3__ u; int /*<<< orphan*/  colorspace; } ;
typedef  TYPE_4__ WebPDecBuffer ;
typedef  int /*<<< orphan*/  const W_CHAR ;
struct TYPE_16__ {size_t num_frames; int canvas_width; int canvas_height; TYPE_1__* frames; } ;
struct TYPE_12__ {int /*<<< orphan*/  rgba; } ;
typedef  TYPE_5__ AnimatedImage ;

/* Variables and functions */
 int /*<<< orphan*/  ClearAnimatedImage (TYPE_5__*) ; 
 int /*<<< orphan*/  FREE_WARGV_AND_RETURN (int) ; 
 void* GET_WARGV (char const**,int) ; 
 int /*<<< orphan*/  GetAnimatedImageVersions (int*,int*) ; 
 int /*<<< orphan*/  Help () ; 
 int /*<<< orphan*/  INIT_WARGV (int,char const**) ; 
 int /*<<< orphan*/  MODE_RGBA ; 
 int /*<<< orphan*/  PAM ; 
 int /*<<< orphan*/  PNG ; 
 int /*<<< orphan*/  ReadAnimatedImage (char const*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIFF ; 
 int /*<<< orphan*/  const* TO_W_CHAR (char*) ; 
 int /*<<< orphan*/  WFPRINTF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WPRINTF (char*,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WSNPRINTF (int /*<<< orphan*/  const*,int,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WebPFreeDecBuffer (TYPE_4__*) ; 
 int /*<<< orphan*/  WebPInitDecBuffer (TYPE_4__*) ; 
 int /*<<< orphan*/  WebPSaveImage (TYPE_4__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int main(int argc, const char* argv[]) {
  int error = 0;
  const W_CHAR* dump_folder = TO_W_CHAR(".");
  const W_CHAR* prefix = TO_W_CHAR("dump_");
  const W_CHAR* suffix = TO_W_CHAR("png");
  WebPOutputFileFormat format = PNG;
  int c;

  INIT_WARGV(argc, argv);

  if (argc < 2) {
    Help();
    FREE_WARGV_AND_RETURN(-1);
  }

  for (c = 1; !error && c < argc; ++c) {
    if (!strcmp(argv[c], "-folder")) {
      if (c + 1 == argc) {
        fprintf(stderr, "missing argument after option '%s'\n", argv[c]);
        error = 1;
        break;
      }
      dump_folder = GET_WARGV(argv, ++c);
    } else if (!strcmp(argv[c], "-prefix")) {
      if (c + 1 == argc) {
        fprintf(stderr, "missing argument after option '%s'\n", argv[c]);
        error = 1;
        break;
      }
      prefix = GET_WARGV(argv, ++c);
    } else if (!strcmp(argv[c], "-tiff")) {
      format = TIFF;
      suffix = TO_W_CHAR("tiff");
    } else if (!strcmp(argv[c], "-pam")) {
      format = PAM;
      suffix = TO_W_CHAR("pam");
    } else if (!strcmp(argv[c], "-h") || !strcmp(argv[c], "-help")) {
      Help();
      FREE_WARGV_AND_RETURN(0);
    } else if (!strcmp(argv[c], "-version")) {
      int dec_version, demux_version;
      GetAnimatedImageVersions(&dec_version, &demux_version);
      printf("WebP Decoder version: %d.%d.%d\nWebP Demux version: %d.%d.%d\n",
             (dec_version >> 16) & 0xff, (dec_version >> 8) & 0xff,
             (dec_version >> 0) & 0xff,
             (demux_version >> 16) & 0xff, (demux_version >> 8) & 0xff,
             (demux_version >> 0) & 0xff);
      FREE_WARGV_AND_RETURN(0);
    } else {
      uint32_t i;
      AnimatedImage image;
      const W_CHAR* const file = GET_WARGV(argv, c);
      memset(&image, 0, sizeof(image));
      WPRINTF("Decoding file: %s as %s/%sxxxx.%s\n",
              file, dump_folder, prefix, suffix);
      if (!ReadAnimatedImage((const char*)file, &image, 0, NULL)) {
        WFPRINTF(stderr, "Error decoding file: %s\n Aborting.\n", file);
        error = 1;
        break;
      }
      for (i = 0; !error && i < image.num_frames; ++i) {
        W_CHAR out_file[1024];
        WebPDecBuffer buffer;
        WebPInitDecBuffer(&buffer);
        buffer.colorspace = MODE_RGBA;
        buffer.is_external_memory = 1;
        buffer.width = image.canvas_width;
        buffer.height = image.canvas_height;
        buffer.u.RGBA.rgba = image.frames[i].rgba;
        buffer.u.RGBA.stride = buffer.width * sizeof(uint32_t);
        buffer.u.RGBA.size = buffer.u.RGBA.stride * buffer.height;
        WSNPRINTF(out_file, sizeof(out_file), "%s/%s%.4d.%s",
                  dump_folder, prefix, i, suffix);
        if (!WebPSaveImage(&buffer, format, (const char*)out_file)) {
          WFPRINTF(stderr, "Error while saving image '%s'\n", out_file);
          error = 1;
        }
        WebPFreeDecBuffer(&buffer);
      }
      ClearAnimatedImage(&image);
    }
  }
  FREE_WARGV_AND_RETURN(error ? 1 : 0);
}