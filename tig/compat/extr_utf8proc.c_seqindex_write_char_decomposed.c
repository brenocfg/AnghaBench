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
typedef  int utf8proc_uint16_t ;
typedef  int utf8proc_ssize_t ;
typedef  int /*<<< orphan*/  utf8proc_option_t ;
typedef  int /*<<< orphan*/  utf8proc_int32_t ;

/* Variables and functions */
 int UTF8PROC_ERROR_OVERFLOW ; 
 int /*<<< orphan*/  seqindex_decode_entry (int const**) ; 
 int utf8proc_decompose_char (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 
 int* utf8proc_sequences ; 

__attribute__((used)) static utf8proc_ssize_t seqindex_write_char_decomposed(utf8proc_uint16_t seqindex, utf8proc_int32_t *dst, utf8proc_ssize_t bufsize, utf8proc_option_t options, int *last_boundclass) {
  utf8proc_ssize_t written = 0;
  const utf8proc_uint16_t *entry = &utf8proc_sequences[seqindex & 0x1FFF];
  int len = seqindex >> 13;
  if (len >= 7) {
    len = *entry;
    entry++;
  }
  for (; len >= 0; entry++, len--) {
    utf8proc_int32_t entry_cp = seqindex_decode_entry(&entry);

    written += utf8proc_decompose_char(entry_cp, dst+written,
      (bufsize > written) ? (bufsize - written) : 0, options,
    last_boundclass);
    if (written < 0) return UTF8PROC_ERROR_OVERFLOW;
  }
  return written;
}