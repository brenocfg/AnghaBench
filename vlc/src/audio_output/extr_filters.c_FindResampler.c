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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  filter_t ;
typedef  int /*<<< orphan*/  audio_sample_format_t ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static filter_t *FindResampler (vlc_object_t *obj,
                                const audio_sample_format_t *infmt,
                                const audio_sample_format_t *outfmt)
{
    char *modlist = var_InheritString(obj, "audio-resampler");
    filter_t *filter = CreateFilter(obj, NULL, "audio resampler", modlist,
                                    infmt, outfmt, NULL, true);
    free(modlist);
    return filter;
}