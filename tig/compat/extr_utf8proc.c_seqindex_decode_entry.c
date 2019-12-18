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
typedef  int utf8proc_int32_t ;

/* Variables and functions */

__attribute__((used)) static utf8proc_int32_t seqindex_decode_entry(const utf8proc_uint16_t **entry)
{
  utf8proc_int32_t entry_cp = **entry;
  if ((entry_cp & 0xF800) == 0xD800) {
    *entry = *entry + 1;
    entry_cp = ((entry_cp & 0x03FF) << 10) | (**entry & 0x03FF);
    entry_cp += 0x10000;
  }
  return entry_cp;
}