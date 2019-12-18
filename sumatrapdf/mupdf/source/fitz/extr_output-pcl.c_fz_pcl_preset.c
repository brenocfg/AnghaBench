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
typedef  int /*<<< orphan*/  fz_pcl_options ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  copy_opts (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_pcl_options_dj500 ; 
 int /*<<< orphan*/  fz_pcl_options_fs600 ; 
 int /*<<< orphan*/  fz_pcl_options_generic ; 
 int /*<<< orphan*/  fz_pcl_options_lj ; 
 int /*<<< orphan*/  fz_pcl_options_lj2 ; 
 int /*<<< orphan*/  fz_pcl_options_lj3 ; 
 int /*<<< orphan*/  fz_pcl_options_lj3d ; 
 int /*<<< orphan*/  fz_pcl_options_lj4 ; 
 int /*<<< orphan*/  fz_pcl_options_lj4d ; 
 int /*<<< orphan*/  fz_pcl_options_lj4pl ; 
 int /*<<< orphan*/  fz_pcl_options_ljet4 ; 
 int /*<<< orphan*/  fz_pcl_options_lp2563b ; 
 int /*<<< orphan*/  fz_pcl_options_oce9050 ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

void fz_pcl_preset(fz_context *ctx, fz_pcl_options *opts, const char *preset)
{
	if (preset == NULL || *preset == 0 || !strcmp(preset, "generic"))
		copy_opts(opts, &fz_pcl_options_generic);
	else if (!strcmp(preset, "ljet4"))
		copy_opts(opts, &fz_pcl_options_ljet4);
	else if (!strcmp(preset, "dj500"))
		copy_opts(opts, &fz_pcl_options_dj500);
	else if (!strcmp(preset, "fs600"))
		copy_opts(opts, &fz_pcl_options_fs600);
	else if (!strcmp(preset, "lj"))
		copy_opts(opts, &fz_pcl_options_lj);
	else if (!strcmp(preset, "lj2"))
		copy_opts(opts, &fz_pcl_options_lj2);
	else if (!strcmp(preset, "lj3"))
		copy_opts(opts, &fz_pcl_options_lj3);
	else if (!strcmp(preset, "lj3d"))
		copy_opts(opts, &fz_pcl_options_lj3d);
	else if (!strcmp(preset, "lj4"))
		copy_opts(opts, &fz_pcl_options_lj4);
	else if (!strcmp(preset, "lj4pl"))
		copy_opts(opts, &fz_pcl_options_lj4pl);
	else if (!strcmp(preset, "lj4d"))
		copy_opts(opts, &fz_pcl_options_lj4d);
	else if (!strcmp(preset, "lp2563b"))
		copy_opts(opts, &fz_pcl_options_lp2563b);
	else if (!strcmp(preset, "oce9050"))
		copy_opts(opts, &fz_pcl_options_oce9050);
	else
		fz_throw(ctx, FZ_ERROR_GENERIC, "Unknown preset '%s'", preset);
}