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
typedef  scalar_t__ z_off_t ;
typedef  scalar_t__ synctex_status_t ;
typedef  int /*<<< orphan*/ * synctex_scanner_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 size_t SYNCTEX_CUR ; 
 size_t SYNCTEX_END ; 
 scalar_t__ SYNCTEX_FILE ; 
 size_t SYNCTEX_START ; 
 scalar_t__ SYNCTEX_STATUS_BAD_ARGUMENT ; 
 scalar_t__ SYNCTEX_STATUS_EOF ; 
 scalar_t__ SYNCTEX_STATUS_ERROR ; 
 scalar_t__ SYNCTEX_STATUS_NOT_OK ; 
 scalar_t__ SYNCTEX_STATUS_OK ; 
 scalar_t__ _synctex_buffer_get_available_size (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  _synctex_error (char*) ; 
 scalar_t__ gzseek (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gztell (scalar_t__) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 

synctex_status_t _synctex_match_string(synctex_scanner_t scanner, const char * the_string) {
	size_t tested_len = 0; /*  the number of characters at the beginning of the_string that match */
	size_t remaining_len = 0; /*  the number of remaining characters of the_string that should match */
	size_t available = 0;
	synctex_status_t status = 0;
	if (NULL == scanner || NULL == the_string) {
		return SYNCTEX_STATUS_BAD_ARGUMENT;
	}
	remaining_len = strlen(the_string); /*  All the_string should match */
	if (0 == remaining_len) {
		return SYNCTEX_STATUS_BAD_ARGUMENT;
	}
	/*  How many characters available in the buffer? */
	available = remaining_len;
	status = _synctex_buffer_get_available_size(scanner,&available);
	if (status<SYNCTEX_STATUS_EOF) {
		return status;
	}
	/*  Maybe we have less characters than expected because the buffer is too small. */
	if (available>=remaining_len) {
		/*  The buffer is sufficiently big to hold the expected number of characters. */
		if (strncmp((char *)SYNCTEX_CUR,the_string,remaining_len)) {
			return SYNCTEX_STATUS_NOT_OK;
		}
return_OK:
		/*  Advance SYNCTEX_CUR to the next character after the_string. */
		SYNCTEX_CUR += remaining_len;
		return SYNCTEX_STATUS_OK;
	} else if (strncmp((char *)SYNCTEX_CUR,the_string,available)) {
			/*  No need to goo further, this is not the expected string in the buffer. */
			return SYNCTEX_STATUS_NOT_OK;
	} else if (SYNCTEX_FILE) {
		/*  The buffer was too small to contain remaining_len characters.
		 *  We have to cut the string into pieces. */
		z_off_t offset = 0L;
		/*  the first part of the string is found, advance the_string to the next untested character. */
		the_string += available;
		/*  update the remaining length and the parsed length. */
		remaining_len -= available;
		tested_len += available;
		SYNCTEX_CUR += available; /*  We validate the tested characters. */
		if (0 == remaining_len) {
			/*  Nothing left to test, we have found the given string, we return the length. */
			return tested_len;
		}
		/*  We also have to record the current state of the file cursor because
		 *  if the_string does not match, all this should be a totally blank operation,
		 *  for which the file and buffer states should not be modified at all.
		 *  In fact, the states of the buffer before and after this function are in general different
		 *  but they are totally equivalent as long as the values of the buffer before SYNCTEX_CUR
		 *  can be safely discarded.  */
		offset = gztell(SYNCTEX_FILE);
		/*  offset now corresponds to the first character of the file that was not buffered. */
		available = SYNCTEX_CUR - SYNCTEX_START; /*  available can be used as temporary placeholder. */
		/*  available now corresponds to the number of chars that where already buffered and
		 *  that match the head of the_string. If in fine the_string does not match, all these chars must be recovered
		 *  because the buffer contents is completely replaced by _synctex_buffer_get_available_size.
		 *  They were buffered from offset-len location in the file. */
		offset -= available;
more_characters:
		/*  There is still some work to be done, so read another bunch of file.
		 *  This is the second call to _synctex_buffer_get_available_size,
		 *  which means that the actual contents of the buffer will be discarded.
		 *  We will definitely have to recover the previous state in case we do not find the expected string. */
		available = remaining_len;
		status = _synctex_buffer_get_available_size(scanner,&available);
		if (status<SYNCTEX_STATUS_EOF) {
			return status; /*  This is an error, no need to go further. */
		}
		if (available==0) {
			/*  Missing characters: recover the initial state of the file and return. */
return_NOT_OK:
			if (offset != gzseek(SYNCTEX_FILE,offset,SEEK_SET)) {
				/*  This is a critical error, we could not recover the previous state. */
				_synctex_error("can't seek file");
				return SYNCTEX_STATUS_ERROR;
			}
			/*  Next time we are asked to fill the buffer,
			 *  we will read a complete bunch of text from the file. */
			SYNCTEX_CUR = SYNCTEX_END;
			return SYNCTEX_STATUS_NOT_OK;
		}
		if (available<remaining_len) {
			/*  We'll have to loop one more time. */
			if (strncmp((char *)SYNCTEX_CUR,the_string,available)) {
				/*  This is not the expected string, recover the previous state and return. */
				goto return_NOT_OK;
			}
			/*  Advance the_string to the first untested character. */
			the_string += available;
			/*  update the remaining length and the parsed length. */
			remaining_len -= available;
			tested_len += available;
			SYNCTEX_CUR += available; /*  We validate the tested characters. */
			if (0 == remaining_len) {
				/*  Nothing left to test, we have found the given string. */
				return SYNCTEX_STATUS_OK;
			}
			goto more_characters;
		}
		/*  This is the last step. */
		if (strncmp((char *)SYNCTEX_CUR,the_string,remaining_len)) {
			/*  This is not the expected string, recover the previous state and return. */
			goto return_NOT_OK;
		}
		goto return_OK;
	} else {
		/*  The buffer can't contain the given string argument, and the EOF was reached */
		return SYNCTEX_STATUS_EOF;
	}
}