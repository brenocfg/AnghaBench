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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _O_BINARY ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ *) ; 
 int _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

FILE* ImgIoUtilSetBinaryMode(FILE* file) {
#if defined(_WIN32)
  if (_setmode(_fileno(file), _O_BINARY) == -1) {
    fprintf(stderr, "Failed to reopen file in O_BINARY mode.\n");
    return NULL;
  }
#endif
  return file;
}