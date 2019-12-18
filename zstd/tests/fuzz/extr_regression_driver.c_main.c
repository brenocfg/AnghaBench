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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,char const*) ; 
 int /*<<< orphan*/  FUZZ_ASSERT_MSG (int,char const*) ; 
 int /*<<< orphan*/  LLVMFuzzerTestOneInput (int /*<<< orphan*/ *,size_t const) ; 
 char** UTIL_createFileList (char const**,unsigned int,char**,unsigned int*,int const) ; 
 int /*<<< orphan*/  UTIL_freeFileList (char const**,char*) ; 
 size_t UTIL_getFileSize (char const*) ; 
 int /*<<< orphan*/  UTIL_isRegularFile (char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 size_t fread (int /*<<< orphan*/ *,int,size_t const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t const) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char const **argv) {
  size_t const kMaxFileSize = (size_t)1 << 27;
  int const kFollowLinks = 1;
  char *fileNamesBuf = NULL;
  char const **files = argv + 1;
  unsigned numFiles = argc - 1;
  uint8_t *buffer = NULL;
  size_t bufferSize = 0;
  unsigned i;
  int ret;

#ifdef UTIL_HAS_CREATEFILELIST
  files = UTIL_createFileList(files, numFiles, &fileNamesBuf, &numFiles,
                              kFollowLinks);
  if (!files)
    numFiles = 0;
#endif
  if (numFiles == 0)
    fprintf(stderr, "WARNING: No files passed to %s\n", argv[0]);
  for (i = 0; i < numFiles; ++i) {
    char const *fileName = files[i];
    DEBUGLOG(3, "Running %s", fileName);
    size_t const fileSize = UTIL_getFileSize(fileName);
    size_t readSize;
    FILE *file;

    /* Check that it is a regular file, and that the fileSize is valid.
     * If it is not a regular file, then it may have been deleted since we
     * constructed the list, so just skip it.
     */
    if (!UTIL_isRegularFile(fileName)) {
      continue;
    }
    FUZZ_ASSERT_MSG(fileSize <= kMaxFileSize, fileName);
    /* Ensure we have a large enough buffer allocated */
    if (fileSize > bufferSize) {
      free(buffer);
      buffer = (uint8_t *)malloc(fileSize);
      FUZZ_ASSERT_MSG(buffer, fileName);
      bufferSize = fileSize;
    }
    /* Open the file */
    file = fopen(fileName, "rb");
    FUZZ_ASSERT_MSG(file, fileName);
    /* Read the file */
    readSize = fread(buffer, 1, fileSize, file);
    FUZZ_ASSERT_MSG(readSize == fileSize, fileName);
    /* Close the file */
    fclose(file);
    /* Run the fuzz target */
    LLVMFuzzerTestOneInput(buffer, fileSize);
  }

  ret = 0;
  free(buffer);
#ifdef UTIL_HAS_CREATEFILELIST
  UTIL_freeFileList(files, fileNamesBuf);
#endif
  return ret;
}