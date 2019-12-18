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
typedef  int /*<<< orphan*/  ar_stream ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * ar_open_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_close ; 
 int /*<<< orphan*/  file_read ; 
 int /*<<< orphan*/  file_seek ; 
 int /*<<< orphan*/  file_tell ; 

ar_stream *ar_open(FILE *f)
{
    if (!f)
        return NULL;
    return ar_open_stream(f, file_close, file_read, file_seek, file_tell);
}