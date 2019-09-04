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

/* Variables and functions */
 int xmlCompressMode ; 

void
xmlSetCompressMode(int mode) {
    if (mode < 0) xmlCompressMode = 0;
    else if (mode > 9) xmlCompressMode = 9;
    else xmlCompressMode = mode;
}