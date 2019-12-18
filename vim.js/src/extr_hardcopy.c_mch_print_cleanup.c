#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ ** ps_fontname; } ;

/* Variables and functions */
 void* FALSE ; 
 int PRT_PS_FONT_BOLDOBLIQUE ; 
 int PRT_PS_FONT_ROMAN ; 
 int /*<<< orphan*/  convert_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prt_conv ; 
 void* prt_do_conv ; 
 void* prt_file_error ; 
 scalar_t__ prt_out_mbyte ; 
 int /*<<< orphan*/ * prt_ps_fd ; 
 int /*<<< orphan*/ * prt_ps_file_name ; 
 TYPE_1__ prt_ps_mb_font ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

void
mch_print_cleanup()
{
#ifdef FEAT_MBYTE
    if (prt_out_mbyte)
    {
	int     i;

	/* Free off all CID font names created, but first clear duplicate
	 * pointers to the same string (when the same font is used for more than
	 * one style).
	 */
	for (i = PRT_PS_FONT_ROMAN; i <= PRT_PS_FONT_BOLDOBLIQUE; i++)
	{
	    if (prt_ps_mb_font.ps_fontname[i] != NULL)
		vim_free(prt_ps_mb_font.ps_fontname[i]);
	    prt_ps_mb_font.ps_fontname[i] = NULL;
	}
    }

    if (prt_do_conv)
    {
	convert_setup(&prt_conv, NULL, NULL);
	prt_do_conv = FALSE;
    }
#endif
    if (prt_ps_fd != NULL)
    {
	fclose(prt_ps_fd);
	prt_ps_fd = NULL;
	prt_file_error = FALSE;
    }
    if (prt_ps_file_name != NULL)
    {
	vim_free(prt_ps_file_name);
	prt_ps_file_name = NULL;
    }
}