#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WebPInfoStatus ;
struct TYPE_4__ {int quiet_; int show_diagnosis_; int show_summary_; int parse_bitstream_; } ;
typedef  TYPE_1__ WebPInfo ;
typedef  int /*<<< orphan*/  WebPData ;
typedef  int /*<<< orphan*/  W_CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  AnalyzeWebP (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FREE_WARGV_AND_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GET_WARGV (char const**,int) ; 
 int /*<<< orphan*/  HelpLong () ; 
 int /*<<< orphan*/  HelpShort () ; 
 int /*<<< orphan*/  INIT_WARGV (int,char const**) ; 
 int /*<<< orphan*/  ReadFileToWebPData (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WEBP_INFO_INVALID_COMMAND ; 
 int /*<<< orphan*/  WEBP_INFO_OK ; 
 int /*<<< orphan*/  WFPRINTF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WPRINTF (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WebPDataClear (int /*<<< orphan*/ *) ; 
 int WebPGetDecoderVersion () ; 
 int /*<<< orphan*/  WebPInfoInit (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,int const,int const,int const) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int main(int argc, const char* argv[]) {
  int c, quiet = 0, show_diag = 0, show_summary = 0;
  int parse_bitstream = 0;
  WebPInfoStatus webp_info_status = WEBP_INFO_OK;
  WebPInfo webp_info;

  INIT_WARGV(argc, argv);

  if (argc == 1) {
    HelpShort();
    FREE_WARGV_AND_RETURN(WEBP_INFO_OK);
  }

  // Parse command-line input.
  for (c = 1; c < argc; ++c) {
    if (!strcmp(argv[c], "-h") || !strcmp(argv[c], "-help")) {
      HelpShort();
      FREE_WARGV_AND_RETURN(WEBP_INFO_OK);
    } else if (!strcmp(argv[c], "-H") || !strcmp(argv[c], "-longhelp")) {
      HelpLong();
      FREE_WARGV_AND_RETURN(WEBP_INFO_OK);
    } else if (!strcmp(argv[c], "-quiet")) {
      quiet = 1;
    } else if (!strcmp(argv[c], "-diag")) {
      show_diag = 1;
    } else if (!strcmp(argv[c], "-summary")) {
      show_summary = 1;
    } else if (!strcmp(argv[c], "-bitstream_info")) {
      parse_bitstream = 1;
    } else if (!strcmp(argv[c], "-version")) {
      const int version = WebPGetDecoderVersion();
      printf("WebP Decoder version: %d.%d.%d\n",
             (version >> 16) & 0xff, (version >> 8) & 0xff, version & 0xff);
      FREE_WARGV_AND_RETURN(0);
    } else {  // Assume the remaining are all input files.
      break;
    }
  }

  if (c == argc) {
    HelpShort();
    FREE_WARGV_AND_RETURN(WEBP_INFO_INVALID_COMMAND);
  }

  // Process input files one by one.
  for (; c < argc; ++c) {
    WebPData webp_data;
    const W_CHAR* in_file = NULL;
    WebPInfoInit(&webp_info);
    webp_info.quiet_ = quiet;
    webp_info.show_diagnosis_ = show_diag;
    webp_info.show_summary_ = show_summary;
    webp_info.parse_bitstream_ = parse_bitstream;
    in_file = GET_WARGV(argv, c);
    if (in_file == NULL ||
        !ReadFileToWebPData((const char*)in_file, &webp_data)) {
      webp_info_status = WEBP_INFO_INVALID_COMMAND;
      WFPRINTF(stderr, "Failed to open input file %s.\n", in_file);
      continue;
    }
    if (!webp_info.quiet_) WPRINTF("File: %s\n", in_file);
    webp_info_status = AnalyzeWebP(&webp_info, &webp_data);
    WebPDataClear(&webp_data);
  }
  FREE_WARGV_AND_RETURN(webp_info_status);
}