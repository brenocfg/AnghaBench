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

/* Variables and functions */
 int /*<<< orphan*/  _synctex_error (char*) ; 
 char* _synctex_last_path_component (char const*) ; 
 char* dest ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 scalar_t__ strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 char* strncpy (char*,char const*,size_t) ; 

int _synctex_copy_with_quoting_last_path_component(const char * src, char ** dest_ref, size_t size) {
  const char * lpc;
  if(src && dest_ref) {
#		define dest (*dest_ref)
		dest = NULL;	/*	Default behavior: no change and sucess. */
		lpc = _synctex_last_path_component(src);
		if(strlen(lpc)) {
			if(strchr(lpc,' ') && lpc[0]!='"' && lpc[strlen(lpc)-1]!='"') {
				/*	We are in the situation where adding the quotes is allowed.	*/
				/*	Time to add the quotes.	*/
				/*  Consistency test: we must have dest+size>dest+strlen(dest)+2
				 *	or equivalently: strlen(dest)+2<size (see below) */
				if(strlen(src)<size) {
					if((dest = (char *)malloc(size+2))) {
						char * dpc = dest + (lpc-src);	/*	dpc is the last path component of dest.	*/
						if(dest != strncpy(dest,src,size)) {
							_synctex_error("!  _synctex_copy_with_quoting_last_path_component: Copy problem");
							free(dest);
							dest = NULL;/*  Don't forget to reinitialize. */
							return -2;
						}
						memmove(dpc+1,dpc,strlen(dpc)+1);	/*	Also move the null terminating character. */
						dpc[0]='"';
						dpc[strlen(dpc)+1]='\0';/*	Consistency test */
						dpc[strlen(dpc)]='"';
						return 0;	/*	Success. */
					}
					return -1;	/*	Memory allocation error.	*/
				}
				_synctex_error("!  _synctex_copy_with_quoting_last_path_component: Internal inconsistency");
				return -3;
			}
			return 0;	/*	Success. */
		}
		return 0;	/*	No last path component. */
#		undef dest
	}
	return 1; /*  Bad parameter, this value is subject to changes. */
}