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
struct md5_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  md5_write (struct md5_s*,void const*,size_t) ; 

void AddMD5( struct md5_s *restrict h, const void *data, size_t len )
{
    md5_write( h, data, len );
}