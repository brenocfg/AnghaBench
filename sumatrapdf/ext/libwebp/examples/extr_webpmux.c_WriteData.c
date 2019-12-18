#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__ WebPData ;
typedef  int /*<<< orphan*/  W_CHAR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * ImgIoUtilSetBinaryMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WFOPEN (char const*,char*) ; 
 int /*<<< orphan*/  WFPRINTF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,...) ; 
 scalar_t__ WSTRCMP (char const*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fwrite (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static int WriteData(const char* filename, const WebPData* const webpdata) {
  int ok = 0;
  FILE* fout = WSTRCMP(filename, "-") ? WFOPEN(filename, "wb")
                                      : ImgIoUtilSetBinaryMode(stdout);
  if (fout == NULL) {
    WFPRINTF(stderr, "Error opening output WebP file %s!\n",
             (const W_CHAR*)filename);
    return 0;
  }
  if (fwrite(webpdata->bytes, webpdata->size, 1, fout) != 1) {
    WFPRINTF(stderr, "Error writing file %s!\n", (const W_CHAR*)filename);
  } else {
    WFPRINTF(stderr, "Saved file %s (%d bytes)\n",
             (const W_CHAR*)filename, (int)webpdata->size);
    ok = 1;
  }
  if (fout != stdout) fclose(fout);
  return ok;
}