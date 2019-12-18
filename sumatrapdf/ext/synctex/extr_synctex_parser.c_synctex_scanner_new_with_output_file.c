#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* synctex_scanner_t ;
typedef  int /*<<< orphan*/  synctex_io_mode_t ;
typedef  int /*<<< orphan*/ * gzFile ;
typedef  int /*<<< orphan*/  _synctex_scanner_t ;
struct TYPE_5__ {char* output; char* synctex; } ;

/* Variables and functions */
 scalar_t__ SYNCTEX_BUFFER_MIN_SIZE ; 
 scalar_t__ SYNCTEX_BUFFER_SIZE ; 
 int /*<<< orphan*/ * SYNCTEX_FILE ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  _synctex_error (char*) ; 
 scalar_t__ _synctex_malloc (int) ; 
 scalar_t__ _synctex_open (char const*,char const*,char**,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gzclose (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (scalar_t__) ; 
 char* strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  synctex_ADD_QUOTES ; 
 int /*<<< orphan*/  synctex_DONT_ADD_QUOTES ; 
 TYPE_1__* synctex_scanner_parse (TYPE_1__*) ; 

synctex_scanner_t synctex_scanner_new_with_output_file(const char * output, const char * build_directory, int parse) {
	gzFile file = NULL;
	char * synctex = NULL;
	synctex_scanner_t scanner = NULL;
	synctex_io_mode_t io_mode = 0;
	/*  Here we assume that int are smaller than void * */
	if (sizeof(int)>sizeof(void*)) {
		_synctex_error("INTERNAL INCONSISTENCY: int's are unexpectedly bigger than pointers, bailing out.");
		return NULL;
	}
	/*  We ensure that SYNCTEX_BUFFER_SIZE < UINT_MAX, I don't know if it makes sense... */
	if (SYNCTEX_BUFFER_SIZE >= UINT_MAX) {
		_synctex_error("SyncTeX BUG: Internal inconsistency, bad SYNCTEX_BUFFER_SIZE (1)");
		return NULL;
	}
	/*  for integers: */
	if (SYNCTEX_BUFFER_SIZE < SYNCTEX_BUFFER_MIN_SIZE) {
		_synctex_error("SyncTeX BUG: Internal inconsistency, bad SYNCTEX_BUFFER_SIZE (2)");
		return NULL;
	}
	/*  now open the synctex file */
	if (_synctex_open(output,build_directory,&synctex,&file,synctex_ADD_QUOTES,&io_mode) || !file) {
		if (_synctex_open(output,build_directory,&synctex,&file,synctex_DONT_ADD_QUOTES,&io_mode) || !file) {
			return NULL;
		}
	}
	scanner = (synctex_scanner_t)_synctex_malloc(sizeof(_synctex_scanner_t));
	if (NULL == scanner) {
		_synctex_error("SyncTeX: malloc problem");
		free(synctex);
		gzclose(file);
		return NULL;
	}
	/*  make a private copy of output for the scanner */
	if (NULL == (scanner->output = (char *)malloc(strlen(output)+1))){
		_synctex_error("!  synctex_scanner_new_with_output_file: Memory problem (2), scanner's output is not reliable.");
	} else if (scanner->output != strcpy(scanner->output,output)) {
		_synctex_error("!  synctex_scanner_new_with_output_file: Copy problem, scanner's output is not reliable.");
	}
	scanner->synctex = synctex;/*  Now the scanner owns synctex */
	SYNCTEX_FILE = file;
	return parse? synctex_scanner_parse(scanner):scanner;
}