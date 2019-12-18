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
 int /*<<< orphan*/  CHECK_EXTENSION_WRAPPER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASTER_EXTENSIONS ; 
 int /*<<< orphan*/  SLAVE_AUDIO_EXTENSIONS ; 
 int /*<<< orphan*/  SLAVE_SPU_EXTENSIONS ; 

int main(void)
{
    CHECK_EXTENSION_WRAPPER( MASTER_EXTENSIONS );
    CHECK_EXTENSION_WRAPPER( SLAVE_SPU_EXTENSIONS );
    CHECK_EXTENSION_WRAPPER( SLAVE_AUDIO_EXTENSIONS );
    return 0;
}