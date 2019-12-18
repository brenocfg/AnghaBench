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
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  var_DecInteger (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  var_IncInteger (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vlc_object_parent (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aout_PolicyNotify (audio_output_t *aout, bool cork)
{
    (cork ? var_IncInteger : var_DecInteger)(vlc_object_parent(aout), "corks");
}