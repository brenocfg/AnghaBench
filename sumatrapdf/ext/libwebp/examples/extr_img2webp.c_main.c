#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int use_argb; int width; int height; } ;
typedef  TYPE_1__ WebPPicture ;
struct TYPE_22__ {scalar_t__ size; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_2__ WebPData ;
struct TYPE_23__ {int lossless; void* method; int /*<<< orphan*/  quality; } ;
typedef  TYPE_3__ WebPConfig ;
struct TYPE_24__ {int minimize_size; int allow_mixed; void* kmax; void* kmin; } ;
typedef  TYPE_4__ WebPAnimEncoderOptions ;
typedef  int /*<<< orphan*/  WebPAnimEncoder ;
typedef  int /*<<< orphan*/  W_CHAR ;
struct TYPE_25__ {int argc_; char** argv_; } ;
typedef  TYPE_5__ CommandLineArguments ;

/* Variables and functions */
 int /*<<< orphan*/  ExUtilDeleteCommandLineArguments (TYPE_5__*) ; 
 int /*<<< orphan*/  ExUtilGetFloat (char const*,int*) ; 
 void* ExUtilGetInt (char const*,int /*<<< orphan*/ ,int*) ; 
 int ExUtilInitCommandLineArguments (int,char const**,TYPE_5__*) ; 
 int /*<<< orphan*/  FREE_WARGV_AND_RETURN (int) ; 
 scalar_t__ GET_WARGV_SHIFTED (char const**,int) ; 
 int /*<<< orphan*/  Help () ; 
 int /*<<< orphan*/  INIT_WARGV (int,char const**) ; 
 int ImgIoUtilWriteFile (char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int ReadImage (char const*,TYPE_1__*) ; 
 int SetLoopCount (int,TYPE_2__*) ; 
 int /*<<< orphan*/  WFPRINTF (int /*<<< orphan*/ ,char*,int,...) ; 
 int WebPAnimEncoderAdd (int /*<<< orphan*/ *,TYPE_1__*,int,TYPE_3__*) ; 
 scalar_t__ WebPAnimEncoderAssemble (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  WebPAnimEncoderDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WebPAnimEncoderNew (int,int,TYPE_4__*) ; 
 int /*<<< orphan*/  WebPAnimEncoderOptionsInit (TYPE_4__*) ; 
 int /*<<< orphan*/  WebPConfigInit (TYPE_3__*) ; 
 int /*<<< orphan*/  WebPDataClear (TYPE_2__*) ; 
 int /*<<< orphan*/  WebPDataInit (TYPE_2__*) ; 
 int WebPGetEncoderVersion () ; 
 int WebPGetMuxVersion () ; 
 int /*<<< orphan*/  WebPPictureFree (TYPE_1__*) ; 
 int /*<<< orphan*/  WebPPictureInit (TYPE_1__*) ; 
 int WebPValidateConfig (TYPE_3__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,int const,int const,int const,int const,int const,int const) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int main(int argc, const char* argv[]) {
  const char* output = NULL;
  WebPAnimEncoder* enc = NULL;
  int verbose = 0;
  int pic_num = 0;
  int duration = 100;
  int timestamp_ms = 0;
  int loop_count = 0;
  int width = 0, height = 0;
  WebPAnimEncoderOptions anim_config;
  WebPConfig config;
  WebPPicture pic;
  WebPData webp_data;
  int c;
  int have_input = 0;
  CommandLineArguments cmd_args;
  int ok;

  INIT_WARGV(argc, argv);

  ok = ExUtilInitCommandLineArguments(argc - 1, argv + 1, &cmd_args);
  if (!ok) FREE_WARGV_AND_RETURN(1);

  argc = cmd_args.argc_;
  argv = cmd_args.argv_;

  WebPDataInit(&webp_data);
  if (!WebPAnimEncoderOptionsInit(&anim_config) ||
      !WebPConfigInit(&config) ||
      !WebPPictureInit(&pic)) {
    fprintf(stderr, "Library version mismatch!\n");
    ok = 0;
    goto End;
  }

  // 1st pass of option parsing
  for (c = 0; ok && c < argc; ++c) {
    if (argv[c][0] == '-') {
      int parse_error = 0;
      if (!strcmp(argv[c], "-o") && c + 1 < argc) {
        argv[c] = NULL;
        output = (const char*)GET_WARGV_SHIFTED(argv, ++c);
      } else if (!strcmp(argv[c], "-kmin") && c + 1 < argc) {
        argv[c] = NULL;
        anim_config.kmin = ExUtilGetInt(argv[++c], 0, &parse_error);
      } else if (!strcmp(argv[c], "-kmax") && c + 1 < argc) {
        argv[c] = NULL;
        anim_config.kmax = ExUtilGetInt(argv[++c], 0, &parse_error);
      } else if (!strcmp(argv[c], "-loop") && c + 1 < argc) {
        argv[c] = NULL;
        loop_count = ExUtilGetInt(argv[++c], 0, &parse_error);
        if (loop_count < 0) {
          fprintf(stderr, "Invalid non-positive loop-count (%d)\n", loop_count);
          parse_error = 1;
        }
      } else if (!strcmp(argv[c], "-min_size")) {
        anim_config.minimize_size = 1;
      } else if (!strcmp(argv[c], "-mixed")) {
        anim_config.allow_mixed = 1;
        config.lossless = 0;
      } else if (!strcmp(argv[c], "-v")) {
        verbose = 1;
      } else if (!strcmp(argv[c], "-h") || !strcmp(argv[c], "-help")) {
        Help();
        goto End;
      } else if (!strcmp(argv[c], "-version")) {
        const int enc_version = WebPGetEncoderVersion();
        const int mux_version = WebPGetMuxVersion();
        printf("WebP Encoder version: %d.%d.%d\nWebP Mux version: %d.%d.%d\n",
               (enc_version >> 16) & 0xff, (enc_version >> 8) & 0xff,
               enc_version & 0xff, (mux_version >> 16) & 0xff,
               (mux_version >> 8) & 0xff, mux_version & 0xff);
        goto End;
      } else {
        continue;
      }
      ok = !parse_error;
      if (!ok) goto End;
      argv[c] = NULL;   // mark option as 'parsed' during 1st pass
    } else {
      have_input |= 1;
    }
  }
  if (!have_input) {
    fprintf(stderr, "No input file(s) for generating animation!\n");
    goto End;
  }

  // image-reading pass
  pic_num = 0;
  config.lossless = 1;
  for (c = 0; ok && c < argc; ++c) {
    if (argv[c] == NULL) continue;
    if (argv[c][0] == '-') {    // parse local options
      int parse_error = 0;
      if (!strcmp(argv[c], "-lossy")) {
        if (!anim_config.allow_mixed) config.lossless = 0;
      } else if (!strcmp(argv[c], "-lossless")) {
        if (!anim_config.allow_mixed) config.lossless = 1;
      } else if (!strcmp(argv[c], "-q") && c + 1 < argc) {
        config.quality = ExUtilGetFloat(argv[++c], &parse_error);
      } else if (!strcmp(argv[c], "-m") && c + 1 < argc) {
        config.method = ExUtilGetInt(argv[++c], 0, &parse_error);
      } else if (!strcmp(argv[c], "-d") && c + 1 < argc) {
        duration = ExUtilGetInt(argv[++c], 0, &parse_error);
        if (duration <= 0) {
          fprintf(stderr, "Invalid negative duration (%d)\n", duration);
          parse_error = 1;
        }
      } else {
        parse_error = 1;   // shouldn't be here.
        fprintf(stderr, "Unknown option [%s]\n", argv[c]);
      }
      ok = !parse_error;
      if (!ok) goto End;
      continue;
    }

    if (ok) {
      ok = WebPValidateConfig(&config);
      if (!ok) {
        fprintf(stderr, "Invalid configuration.\n");
        goto End;
      }
    }

    // read next input image
    pic.use_argb = 1;
    ok = ReadImage((const char*)GET_WARGV_SHIFTED(argv, c), &pic);
    if (!ok) goto End;

    if (enc == NULL) {
      width  = pic.width;
      height = pic.height;
      enc = WebPAnimEncoderNew(width, height, &anim_config);
      ok = (enc != NULL);
      if (!ok) {
        fprintf(stderr, "Could not create WebPAnimEncoder object.\n");
      }
    }

    if (ok) {
      ok = (width == pic.width && height == pic.height);
      if (!ok) {
        fprintf(stderr, "Frame #%d dimension mismatched! "
                        "Got %d x %d. Was expecting %d x %d.\n",
                pic_num, pic.width, pic.height, width, height);
      }
    }

    if (ok) {
      ok = WebPAnimEncoderAdd(enc, &pic, timestamp_ms, &config);
      if (!ok) {
        fprintf(stderr, "Error while adding frame #%d\n", pic_num);
      }
    }
    WebPPictureFree(&pic);
    if (!ok) goto End;

    if (verbose) {
      WFPRINTF(stderr, "Added frame #%3d at time %4d (file: %s)\n",
               pic_num, timestamp_ms, GET_WARGV_SHIFTED(argv, c));
    }
    timestamp_ms += duration;
    ++pic_num;
  }

  // add a last fake frame to signal the last duration
  ok = ok && WebPAnimEncoderAdd(enc, NULL, timestamp_ms, NULL);
  ok = ok && WebPAnimEncoderAssemble(enc, &webp_data);
  if (!ok) {
    fprintf(stderr, "Error during final animation assembly.\n");
  }

 End:
  // free resources
  WebPAnimEncoderDelete(enc);

  if (ok && loop_count > 0) {  // Re-mux to add loop count.
    ok = SetLoopCount(loop_count, &webp_data);
  }

  if (ok) {
    if (output != NULL) {
      ok = ImgIoUtilWriteFile(output, webp_data.bytes, webp_data.size);
      if (ok) WFPRINTF(stderr, "output file: %s     ", (const W_CHAR*)output);
    } else {
      fprintf(stderr, "[no output file specified]   ");
    }
  }

  if (ok) {
    fprintf(stderr, "[%d frames, %u bytes].\n",
            pic_num, (unsigned int)webp_data.size);
  }
  WebPDataClear(&webp_data);
  ExUtilDeleteCommandLineArguments(&cmd_args);
  FREE_WARGV_AND_RETURN(ok ? 0 : 1);
}