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
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void aout_DeviceNotify (audio_output_t *aout, const char *id)
{
    var_SetString (aout, "device", (id != NULL) ? id : "");
}