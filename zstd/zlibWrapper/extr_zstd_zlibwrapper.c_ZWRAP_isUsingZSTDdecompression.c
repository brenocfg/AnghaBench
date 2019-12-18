#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* z_streamp ;
struct TYPE_3__ {scalar_t__ reserved; } ;

/* Variables and functions */
 scalar_t__ ZWRAP_ZSTD_STREAM ; 

int ZWRAP_isUsingZSTDdecompression(z_streamp strm)
{
    if (strm == NULL) return 0;
    return (strm->reserved == ZWRAP_ZSTD_STREAM);
}