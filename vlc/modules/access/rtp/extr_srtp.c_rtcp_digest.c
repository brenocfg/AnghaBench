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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  gcry_md_hd_t ;

/* Variables and functions */
 int /*<<< orphan*/  const* gcry_md_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcry_md_write (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static const uint8_t *
rtcp_digest (gcry_md_hd_t md, const void *data, size_t len)
{
    gcry_md_reset (md);
    gcry_md_write (md, data, len);
    return gcry_md_read (md, 0);
}