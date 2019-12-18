#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct jpeg_error_mgr {scalar_t__ num_warnings; int /*<<< orphan*/  last_addon_message; int /*<<< orphan*/  first_addon_message; int /*<<< orphan*/  addon_message_table; } ;
struct jpeg_decompress_struct {scalar_t__ output_scanline; scalar_t__ output_height; int /*<<< orphan*/  err; } ;
struct TYPE_11__ {int /*<<< orphan*/  total_passes; int /*<<< orphan*/  completed_passes; } ;
struct cdjpeg_progress_mgr {TYPE_1__ pub; } ;
typedef  int /*<<< orphan*/  j_common_ptr ;
typedef  TYPE_2__* djpeg_dest_ptr ;
struct TYPE_12__ {int /*<<< orphan*/  (* finish_output ) (struct jpeg_decompress_struct*,TYPE_2__*) ;int /*<<< orphan*/  (* put_pixel_rows ) (struct jpeg_decompress_struct*,TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  buffer_height; int /*<<< orphan*/  buffer; int /*<<< orphan*/  (* start_output ) (struct jpeg_decompress_struct*,TYPE_2__*) ;int /*<<< orphan*/ * output_file; } ;
typedef  int /*<<< orphan*/  JDIMENSION ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ERREXIT (struct jpeg_decompress_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  EXIT_WARNING ; 
 int /*<<< orphan*/  FALSE ; 
#define  FMT_BMP 133 
#define  FMT_GIF 132 
#define  FMT_OS2 131 
#define  FMT_PPM 130 
#define  FMT_RLE 129 
#define  FMT_TARGA 128 
 size_t INPUT_BUF_SIZE ; 
 int /*<<< orphan*/  JERR_UNSUPPORTED_FORMAT ; 
 size_t JFREAD (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  JMSG_FIRSTADDONCODE ; 
 int /*<<< orphan*/  JMSG_LASTADDONCODE ; 
 scalar_t__ JPEG_APP0 ; 
 scalar_t__ JPEG_COM ; 
 int /*<<< orphan*/  READ_BINARY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WRITE_BINARY ; 
 int ccommand (char***) ; 
 int /*<<< orphan*/  cdjpeg_message_table ; 
 int /*<<< orphan*/  enable_signal_catcher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_progress_monitor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 TYPE_2__* jinit_write_bmp (struct jpeg_decompress_struct*,int /*<<< orphan*/ ) ; 
 TYPE_2__* jinit_write_gif (struct jpeg_decompress_struct*) ; 
 TYPE_2__* jinit_write_ppm (struct jpeg_decompress_struct*) ; 
 TYPE_2__* jinit_write_rle (struct jpeg_decompress_struct*) ; 
 TYPE_2__* jinit_write_targa (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_create_decompress (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_destroy_decompress (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_finish_decompress (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_mem_src (struct jpeg_decompress_struct*,unsigned char*,unsigned long) ; 
 int /*<<< orphan*/  jpeg_read_header (struct jpeg_decompress_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_read_scanlines (struct jpeg_decompress_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_set_marker_processor (struct jpeg_decompress_struct*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_start_decompress (struct jpeg_decompress_struct*) ; 
 int /*<<< orphan*/  jpeg_std_error (struct jpeg_error_mgr*) ; 
 int /*<<< orphan*/  jpeg_stdio_src (struct jpeg_decompress_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ memsrc ; 
 char* outfilename ; 
 int parse_switches (struct jpeg_decompress_struct*,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_text_marker ; 
 scalar_t__* progname ; 
 int /*<<< orphan*/ * read_stdin () ; 
 scalar_t__ realloc (unsigned char*,unsigned long) ; 
 int requested_fmt ; 
 int /*<<< orphan*/  start_progress_monitor (int /*<<< orphan*/ ,struct cdjpeg_progress_mgr*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  stub1 (struct jpeg_decompress_struct*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (struct jpeg_decompress_struct*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct jpeg_decompress_struct*,TYPE_2__*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/ * write_stdout () ; 

int
main (int argc, char **argv)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
#ifdef PROGRESS_REPORT
  struct cdjpeg_progress_mgr progress;
#endif
  int file_index;
  djpeg_dest_ptr dest_mgr = NULL;
  FILE * input_file;
  FILE * output_file;
  unsigned char *inbuffer = NULL;
  unsigned long insize = 0;
  JDIMENSION num_scanlines;

  /* On Mac, fetch a command line. */
#ifdef USE_CCOMMAND
  argc = ccommand(&argv);
#endif

  progname = argv[0];
  if (progname == NULL || progname[0] == 0)
    progname = "djpeg";		/* in case C library doesn't provide it */

  /* Initialize the JPEG decompression object with default error handling. */
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
  /* Add some application-specific error messages (from cderror.h) */
  jerr.addon_message_table = cdjpeg_message_table;
  jerr.first_addon_message = JMSG_FIRSTADDONCODE;
  jerr.last_addon_message = JMSG_LASTADDONCODE;

  /* Insert custom marker processor for COM and APP12.
   * APP12 is used by some digital camera makers for textual info,
   * so we provide the ability to display it as text.
   * If you like, additional APPn marker types can be selected for display,
   * but don't try to override APP0 or APP14 this way (see libjpeg.txt).
   */
  jpeg_set_marker_processor(&cinfo, JPEG_COM, print_text_marker);
  jpeg_set_marker_processor(&cinfo, JPEG_APP0+12, print_text_marker);

  /* Now safe to enable signal catcher. */
#ifdef NEED_SIGNAL_CATCHER
  enable_signal_catcher((j_common_ptr) &cinfo);
#endif

  /* Scan command line to find file names. */
  /* It is convenient to use just one switch-parsing routine, but the switch
   * values read here are ignored; we will rescan the switches after opening
   * the input file.
   * (Exception: tracing level set here controls verbosity for COM markers
   * found during jpeg_read_header...)
   */

  file_index = parse_switches(&cinfo, argc, argv, 0, FALSE);

#ifdef TWO_FILE_COMMANDLINE
  /* Must have either -outfile switch or explicit output file name */
  if (outfilename == NULL) {
    if (file_index != argc-2) {
      fprintf(stderr, "%s: must name one input and one output file\n",
	      progname);
      usage();
    }
    outfilename = argv[file_index+1];
  } else {
    if (file_index != argc-1) {
      fprintf(stderr, "%s: must name one input and one output file\n",
	      progname);
      usage();
    }
  }
#else
  /* Unix style: expect zero or one file name */
  if (file_index < argc-1) {
    fprintf(stderr, "%s: only one input file\n", progname);
    usage();
  }
#endif /* TWO_FILE_COMMANDLINE */

  /* Open the input file. */
  if (file_index < argc) {
    if ((input_file = fopen(argv[file_index], READ_BINARY)) == NULL) {
      fprintf(stderr, "%s: can't open %s\n", progname, argv[file_index]);
      exit(EXIT_FAILURE);
    }
  } else {
    /* default input file is stdin */
    input_file = read_stdin();
  }

  /* Open the output file. */
  if (outfilename != NULL) {
    if ((output_file = fopen(outfilename, WRITE_BINARY)) == NULL) {
      fprintf(stderr, "%s: can't open %s\n", progname, outfilename);
      exit(EXIT_FAILURE);
    }
  } else {
    /* default output file is stdout */
    output_file = write_stdout();
  }

#ifdef PROGRESS_REPORT
  start_progress_monitor((j_common_ptr) &cinfo, &progress);
#endif

  /* Specify data source for decompression */
#if JPEG_LIB_VERSION >= 80 || defined(MEM_SRCDST_SUPPORTED)
  if (memsrc) {
    size_t nbytes;
    do {
      inbuffer = (unsigned char *)realloc(inbuffer, insize + INPUT_BUF_SIZE);
      if (inbuffer == NULL) {
        fprintf(stderr, "%s: memory allocation failure\n", progname);
        exit(EXIT_FAILURE);
      }
      nbytes = JFREAD(input_file, &inbuffer[insize], INPUT_BUF_SIZE);
      if (nbytes < INPUT_BUF_SIZE && ferror(input_file)) {
        if (file_index < argc)
          fprintf(stderr, "%s: can't read from %s\n", progname,
                  argv[file_index]);
        else
          fprintf(stderr, "%s: can't read from stdin\n", progname);
      }
      insize += (unsigned long)nbytes;
    } while (nbytes == INPUT_BUF_SIZE);
    fprintf(stderr, "Compressed size:  %lu bytes\n", insize);
    jpeg_mem_src(&cinfo, inbuffer, insize);
  } else
#endif
    jpeg_stdio_src(&cinfo, input_file);

  /* Read file header, set default decompression parameters */
  (void) jpeg_read_header(&cinfo, TRUE);

  /* Adjust default decompression parameters by re-parsing the options */
  file_index = parse_switches(&cinfo, argc, argv, 0, TRUE);

  /* Initialize the output module now to let it override any crucial
   * option settings (for instance, GIF wants to force color quantization).
   */
  switch (requested_fmt) {
#ifdef BMP_SUPPORTED
  case FMT_BMP:
    dest_mgr = jinit_write_bmp(&cinfo, FALSE);
    break;
  case FMT_OS2:
    dest_mgr = jinit_write_bmp(&cinfo, TRUE);
    break;
#endif
#ifdef GIF_SUPPORTED
  case FMT_GIF:
    dest_mgr = jinit_write_gif(&cinfo);
    break;
#endif
#ifdef PPM_SUPPORTED
  case FMT_PPM:
    dest_mgr = jinit_write_ppm(&cinfo);
    break;
#endif
#ifdef RLE_SUPPORTED
  case FMT_RLE:
    dest_mgr = jinit_write_rle(&cinfo);
    break;
#endif
#ifdef TARGA_SUPPORTED
  case FMT_TARGA:
    dest_mgr = jinit_write_targa(&cinfo);
    break;
#endif
  default:
    ERREXIT(&cinfo, JERR_UNSUPPORTED_FORMAT);
    break;
  }
  dest_mgr->output_file = output_file;

  /* Start decompressor */
  (void) jpeg_start_decompress(&cinfo);

  /* Write output file header */
  (*dest_mgr->start_output) (&cinfo, dest_mgr);

  /* Process data */
  while (cinfo.output_scanline < cinfo.output_height) {
    num_scanlines = jpeg_read_scanlines(&cinfo, dest_mgr->buffer,
					dest_mgr->buffer_height);
    (*dest_mgr->put_pixel_rows) (&cinfo, dest_mgr, num_scanlines);
  }

#ifdef PROGRESS_REPORT
  /* Hack: count final pass as done in case finish_output does an extra pass.
   * The library won't have updated completed_passes.
   */
  progress.pub.completed_passes = progress.pub.total_passes;
#endif

  /* Finish decompression and release memory.
   * I must do it in this order because output module has allocated memory
   * of lifespan JPOOL_IMAGE; it needs to finish before releasing memory.
   */
  (*dest_mgr->finish_output) (&cinfo, dest_mgr);
  (void) jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);

  /* Close files, if we opened them */
  if (input_file != stdin)
    fclose(input_file);
  if (output_file != stdout)
    fclose(output_file);

#ifdef PROGRESS_REPORT
  end_progress_monitor((j_common_ptr) &cinfo);
#endif

  if (memsrc && inbuffer != NULL)
    free(inbuffer);

  /* All done. */
  exit(jerr.num_warnings ? EXIT_WARNING : EXIT_SUCCESS);
  return 0;			/* suppress no-return-value warnings */
}