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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  W_CHAR ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ImgIoUtilReadFromStdin (char const**,size_t*) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/ * WFOPEN (char const* const,char*) ; 
 int /*<<< orphan*/  WFPRINTF (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  WSTRCMP (char const* const,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fread (char*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  stderr ; 

int ImgIoUtilReadFile(const char* const file_name,
                      const uint8_t** data, size_t* data_size) {
  int ok;
  uint8_t* file_data;
  size_t file_size;
  FILE* in;
  const int from_stdin = (file_name == NULL) || !WSTRCMP(file_name, "-");

  if (from_stdin) return ImgIoUtilReadFromStdin(data, data_size);

  if (data == NULL || data_size == NULL) return 0;
  *data = NULL;
  *data_size = 0;

  in = WFOPEN(file_name, "rb");
  if (in == NULL) {
    WFPRINTF(stderr, "cannot open input file '%s'\n", (const W_CHAR*)file_name);
    return 0;
  }
  fseek(in, 0, SEEK_END);
  file_size = ftell(in);
  fseek(in, 0, SEEK_SET);
  // we allocate one extra byte for the \0 terminator
  file_data = (uint8_t*)malloc(file_size + 1);
  if (file_data == NULL) {
    fclose(in);
    WFPRINTF(stderr, "memory allocation failure when reading file %s\n",
             (const W_CHAR*)file_name);
    return 0;
  }
  ok = (fread(file_data, file_size, 1, in) == 1);
  fclose(in);

  if (!ok) {
    WFPRINTF(stderr, "Could not read %d bytes of data from file %s\n",
             (int)file_size, (const W_CHAR*)file_name);
    free(file_data);
    return 0;
  }
  file_data[file_size] = '\0';  // convenient 0-terminator
  *data = file_data;
  *data_size = file_size;
  return 1;
}