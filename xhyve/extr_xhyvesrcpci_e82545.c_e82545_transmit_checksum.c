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
typedef  int /*<<< orphan*/  uint16_t ;
struct iovec {scalar_t__ iov_base; } ;
struct ck_info {int ck_start; int ck_off; int ck_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,int,int,int) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  e82545_iov_checksum (struct iovec*,int,int,int) ; 
 int /*<<< orphan*/  write_uint16_unaligned (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
e82545_transmit_checksum(struct iovec *iov, int iovcnt, struct ck_info *ck)
{
	uint16_t cksum;
	int cklen;

	DPRINTF("tx cksum: iovcnt/s/off/len %d/%d/%d/%d\r\n",
	    iovcnt, ck->ck_start, ck->ck_off, ck->ck_len);
	cklen = ck->ck_len ? ck->ck_len - ck->ck_start + 1 : INT_MAX;
	cksum = e82545_iov_checksum(iov, iovcnt, ck->ck_start, cklen);
    write_uint16_unaligned((uint8_t *)iov[0].iov_base + ck->ck_off, ~cksum);
}