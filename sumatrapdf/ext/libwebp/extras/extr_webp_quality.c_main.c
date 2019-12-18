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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  W_CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_WARGV_AND_RETURN (int) ; 
 scalar_t__ GET_WARGV (char const**,int) ; 
 int /*<<< orphan*/  INIT_WARGV (int,char const**) ; 
 int ImgIoUtilReadFile (char const* const,int /*<<< orphan*/  const**,size_t*) ; 
 int VP8EstimateQuality (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  WPRINTF (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int main(int argc, const char* argv[]) {
  int c;
  int quiet = 0;
  int ok = 1;

  INIT_WARGV(argc, argv);

  for (c = 1; ok && c < argc; ++c) {
    if (!strcmp(argv[c], "-quiet")) {
      quiet = 1;
    } else if (!strcmp(argv[c], "-help") || !strcmp(argv[c], "-h")) {
      printf("webp_quality [-h][-quiet] webp_files...\n");
      FREE_WARGV_AND_RETURN(0);
    } else {
      const char* const filename = (const char*)GET_WARGV(argv, c);
      const uint8_t* data = NULL;
      size_t data_size = 0;
      int q;
      ok = ImgIoUtilReadFile(filename, &data, &data_size);
      if (!ok) break;
      q = VP8EstimateQuality(data, data_size);
      if (!quiet) WPRINTF("[%s] ", (const W_CHAR*)filename);
      if (q < 0) {
        fprintf(stderr, "Not a WebP file, or not a lossy WebP file.\n");
        ok = 0;
      } else {
        if (!quiet) {
          printf("Estimated quality factor: %d\n", q);
        } else {
          printf("%d\n", q);   // just print the number
        }
      }
      free((void*)data);
    }
  }
  FREE_WARGV_AND_RETURN(ok ? 0 : 1);
}