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
typedef  scalar_t__ synctex_status_t ;
typedef  int /*<<< orphan*/ * synctex_scanner_t ;

/* Variables and functions */
 char* SYNCTEX_CUR ; 
 char* SYNCTEX_END ; 
 scalar_t__ SYNCTEX_STATUS_BAD_ARGUMENT ; 
 scalar_t__ SYNCTEX_STATUS_EOF ; 
 scalar_t__ SYNCTEX_STATUS_ERROR ; 
 scalar_t__ SYNCTEX_STATUS_OK ; 
 size_t UINT_MAX ; 
 scalar_t__ _synctex_buffer_get_available_size (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  _synctex_error (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ memcpy (char*,char*,size_t) ; 
 char* realloc (char*,size_t) ; 

synctex_status_t _synctex_decode_string(synctex_scanner_t scanner, char ** value_ref) {
	char * end = NULL;
	size_t current_size = 0;
	size_t new_size = 0;
	size_t len = 0;/*  The number of bytes to copy */
	size_t available = 0;
	synctex_status_t status = 0;
	if (NULL == scanner || NULL == value_ref) {
		return SYNCTEX_STATUS_BAD_ARGUMENT;
	}
	/*  The buffer must at least contain one character: the '\n' end of line marker */
	if (SYNCTEX_CUR>=SYNCTEX_END) {
		available = 1;
		status = _synctex_buffer_get_available_size(scanner,&available);
		if (status < 0) {
			return status;
		}
		if (0 == available) {
			return SYNCTEX_STATUS_EOF;
		}
	}
	/*  Now we are sure that there is at least one available character, either because
	 *  SYNCTEX_CUR was already < SYNCTEX_END, or because the buffer has been properly filled. */
	/*  end will point to the next unparsed '\n' character in the file, when mapped to the buffer. */
	end = SYNCTEX_CUR;
	* value_ref = NULL;/*  Initialize, it will be realloc'ed */
	/*  We scan all the characters up to the next '\n' */
next_character:
	if (end<SYNCTEX_END) {
		if (*end == '\n') {
			/*  OK, we found where to stop */
			len = end - SYNCTEX_CUR;
			if (current_size>UINT_MAX-len-1) {
				/*  But we have reached the limit: we do not have current_size+len+1>UINT_MAX.
				 *  We return the missing amount of memory.
				 *  This will never occur in practice. */
				return UINT_MAX-len-1 - current_size;
			}
			new_size = current_size+len;
			/*  We have current_size+len+1<=UINT_MAX
			 *  or equivalently new_size<UINT_MAX,
			 *  where we have assumed that len<UINT_MAX */
			if ((* value_ref = realloc(* value_ref,new_size+1)) != NULL) {
				if (memcpy((*value_ref)+current_size,SYNCTEX_CUR,len)) {
					/* SumatraPDF: fix reading files with DOS line endings*/
					if (new_size > 0 && (*value_ref)[new_size - 1] == '\r')
						new_size--;
					(* value_ref)[new_size]='\0'; /*  Terminate the string */
					SYNCTEX_CUR += len;/*  Advance to the terminating '\n' */
					return SYNCTEX_STATUS_OK;
				}
				free(* value_ref);
				* value_ref = NULL;
				_synctex_error("could not copy memory (1).");
				return SYNCTEX_STATUS_ERROR;
			}
			_synctex_error("could not allocate memory (1).");
			return SYNCTEX_STATUS_ERROR;
		} else {
			++end;
			goto next_character;
		}
	} else {
		/*  end == SYNCTEX_END */
		len = SYNCTEX_END - SYNCTEX_CUR;
		if (current_size>UINT_MAX-len-1) {
			/*  We have reached the limit. */
			_synctex_error("limit reached (missing %i).",current_size-(UINT_MAX-len-1));
			return SYNCTEX_STATUS_ERROR;
		}
		new_size = current_size+len;
		if ((* value_ref = realloc(* value_ref,new_size+1)) != NULL) {
			if (memcpy((*value_ref)+current_size,SYNCTEX_CUR,len)) {
				(* value_ref)[new_size]='\0'; /*  Terminate the string */
				SYNCTEX_CUR = SYNCTEX_END;/*  Advance the cursor to the end of the bufer */
				return SYNCTEX_STATUS_OK;
			}
			free(* value_ref);
			* value_ref = NULL;
			_synctex_error("could not copy memory (2).");
			return SYNCTEX_STATUS_ERROR;
		}
		/*  Huge memory problem */
		_synctex_error("could not allocate memory (2).");
		return SYNCTEX_STATUS_ERROR;
	}
}