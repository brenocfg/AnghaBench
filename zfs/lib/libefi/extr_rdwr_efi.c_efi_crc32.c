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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 unsigned char const* Z_NULL ; 
 scalar_t__ crc32 (scalar_t__,unsigned char const*,unsigned int) ; 

__attribute__((used)) static uint32_t
efi_crc32(const unsigned char *buf, unsigned int size)
{
	uint32_t crc = crc32(0, Z_NULL, 0);

	crc = crc32(crc, buf, size);

	return (crc);
}