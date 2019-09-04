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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
sec_hash_16(uint8 * out, uint8 * in, uint8 * salt1, uint8 * salt2)
{
	MD5_CTX md5;

	MD5_Init(&md5);
	MD5_Update(&md5, in, 16);
	MD5_Update(&md5, salt1, 32);
	MD5_Update(&md5, salt2, 32);
	MD5_Final(out, &md5);
}