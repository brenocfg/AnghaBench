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
struct buf {char* data; size_t size; } ;

/* Variables and functions */
 scalar_t__ _isspace (char) ; 
 size_t prefix_codefence (char*,size_t) ; 

__attribute__((used)) static size_t
is_codefence(uint8_t *data, size_t size, struct buf *syntax)
{
	size_t i = 0, syn_len = 0;
	uint8_t *syn_start;

	i = prefix_codefence(data, size);
	if (i == 0)
		return 0;

	while (i < size && data[i] == ' ')
		i++;

	syn_start = data + i;

	if (i < size && data[i] == '{') {
		i++; syn_start++;

		while (i < size && data[i] != '}' && data[i] != '\n') {
			syn_len++; i++;
		}

		if (i == size || data[i] != '}')
			return 0;

		/* strip all whitespace at the beginning and the end
		 * of the {} block */
		while (syn_len > 0 && _isspace(syn_start[0])) {
			syn_start++; syn_len--;
		}

		while (syn_len > 0 && _isspace(syn_start[syn_len - 1]))
			syn_len--;

		i++;
	} else {
		while (i < size && !_isspace(data[i])) {
			syn_len++; i++;
		}
	}

	if (syntax) {
		syntax->data = syn_start;
		syntax->size = syn_len;
	}

	while (i < size && data[i] != '\n') {
		if (!_isspace(data[i]))
			return 0;

		i++;
	}

	return i + 1;
}