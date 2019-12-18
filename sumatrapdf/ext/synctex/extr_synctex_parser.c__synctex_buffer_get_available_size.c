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
typedef  int /*<<< orphan*/  synctex_status_t ;
typedef  int /*<<< orphan*/ * synctex_scanner_t ;

/* Variables and functions */
 size_t SYNCTEX_BUFFER_SIZE ; 
 char* SYNCTEX_CUR ; 
 char* SYNCTEX_END ; 
 int /*<<< orphan*/ * SYNCTEX_FILE ; 
 char* SYNCTEX_START ; 
 int /*<<< orphan*/  SYNCTEX_STATUS_BAD_ARGUMENT ; 
 int /*<<< orphan*/  SYNCTEX_STATUS_EOF ; 
 int /*<<< orphan*/  SYNCTEX_STATUS_ERROR ; 
 int /*<<< orphan*/  SYNCTEX_STATUS_OK ; 
 int Z_ERRNO ; 
 int /*<<< orphan*/  _synctex_error (char*,int,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  gzclose (int /*<<< orphan*/ *) ; 
 char* gzerror (int /*<<< orphan*/ *,int*) ; 
 int gzread (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 size_t size ; 

synctex_status_t _synctex_buffer_get_available_size(synctex_scanner_t scanner, size_t * size_ptr) {
  	size_t available = 0;
	if (NULL == scanner || NULL == size_ptr) {
		return SYNCTEX_STATUS_BAD_ARGUMENT;
	}
#   define size (* size_ptr)
	if (size>SYNCTEX_BUFFER_SIZE){
		size = SYNCTEX_BUFFER_SIZE;
	}
	available = SYNCTEX_END - SYNCTEX_CUR; /*  available is the number of unparsed chars in the buffer */
	if (size<=available) {
		/*  There are already sufficiently many characters in the buffer */
		size = available;
		return SYNCTEX_STATUS_OK;
	}
	if (SYNCTEX_FILE) {
		/*  Copy the remaining part of the buffer to the beginning,
		 *  then read the next part of the file */
		int already_read = 0;
		if (available) {
			memmove(SYNCTEX_START, SYNCTEX_CUR, available);
		}
		SYNCTEX_CUR = SYNCTEX_START + available; /*  the next character after the move, will change. */
		/*  Fill the buffer up to its end */
		already_read = gzread(SYNCTEX_FILE,(void *)SYNCTEX_CUR,SYNCTEX_BUFFER_SIZE - available);
		if (already_read>0) {
			/*  We assume that 0<already_read<=SYNCTEX_BUFFER_SIZE - available, such that
			 *  SYNCTEX_CUR + already_read = SYNCTEX_START + available  + already_read <= SYNCTEX_START + SYNCTEX_BUFFER_SIZE */
			SYNCTEX_END = SYNCTEX_CUR + already_read;
			/*  If the end of the file was reached, all the required SYNCTEX_BUFFER_SIZE - available
			 *  may not be filled with values from the file.
			 *  In that case, the buffer should stop properly after already_read characters. */
			* SYNCTEX_END = '\0';
			SYNCTEX_CUR = SYNCTEX_START;
			size = SYNCTEX_END - SYNCTEX_CUR; /* == old available + already_read*/
			return SYNCTEX_STATUS_OK; /*  May be available is less than size, the caller will have to test. */
		} else if (0>already_read) {
			/*  There is a possible error in reading the file */
			int errnum = 0;
			const char * error_string = gzerror(SYNCTEX_FILE, &errnum);
			if (Z_ERRNO == errnum) {
				/*  There is an error in zlib caused by the file system */
				_synctex_error("gzread error from the file system (%i)",errno);
                return SYNCTEX_STATUS_ERROR;
			} else if (errnum) {
				_synctex_error("gzread error (%i:%i,%s)",already_read,errnum,error_string);
                return SYNCTEX_STATUS_ERROR;
			}
		}
        /*  Nothing was read, we are at the end of the file. */
        gzclose(SYNCTEX_FILE);
        SYNCTEX_FILE = NULL;
        SYNCTEX_END = SYNCTEX_CUR;
        SYNCTEX_CUR = SYNCTEX_START;
        * SYNCTEX_END = '\0';/*  Terminate the string properly.*/
        size = SYNCTEX_END - SYNCTEX_CUR;
        return SYNCTEX_STATUS_EOF; /*  there might be a bit of text left */
    }
	/*  We cannot enlarge the buffer because the end of the file was reached. */
	size = available;
 	return SYNCTEX_STATUS_EOF;
#   undef size
}