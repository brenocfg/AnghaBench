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
typedef  size_t utf8proc_uint32_t ;
typedef  int /*<<< orphan*/  utf8proc_uint16_t ;
typedef  int /*<<< orphan*/  utf8proc_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  seqindex_decode_entry (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * utf8proc_sequences ; 

__attribute__((used)) static utf8proc_int32_t seqindex_decode_index(const utf8proc_uint32_t seqindex)
{
  const utf8proc_uint16_t *entry = &utf8proc_sequences[seqindex];
  return seqindex_decode_entry(&entry);
}