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
 char* get_token_data_buffer (char const*,unsigned int,char const*,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static __inline char* get_sanitized_token_data_buffer(const char* token, unsigned int n, const char* buffer, size_t buffer_size)
{
	size_t i;
	char* data = get_token_data_buffer(token, n, buffer, buffer_size);
	if (data != NULL) {
		for (i=0; i<strlen(data); i++) {
			if ((data[i] == '\\') && (data[i+1] == 'n')) {
				data[i] = '\r';
				data[i+1] = '\n';
			}
		}
	}
	return data;
}