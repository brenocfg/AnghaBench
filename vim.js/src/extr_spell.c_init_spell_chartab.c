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
struct TYPE_3__ {int* st_isw; int* st_fold; int* st_upper; void** st_isu; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int MB_BYTE2LEN (int) ; 
 scalar_t__ MB_ISLOWER (int) ; 
 scalar_t__ MB_ISUPPER (int) ; 
 int MB_TOLOWER (int) ; 
 int MB_TOUPPER (int) ; 
 void* TRUE ; 
 int /*<<< orphan*/  clear_spell_chartab (TYPE_1__*) ; 
 int /*<<< orphan*/  did_set_spelltab ; 
 scalar_t__ enc_dbcs ; 
 scalar_t__ enc_utf8 ; 
 TYPE_1__ spelltab ; 
 int utf_fold (int) ; 
 scalar_t__ utf_islower (int) ; 
 void* utf_isupper (int) ; 
 int utf_toupper (int) ; 

void
init_spell_chartab()
{
    int	    i;

    did_set_spelltab = FALSE;
    clear_spell_chartab(&spelltab);
#ifdef FEAT_MBYTE
    if (enc_dbcs)
    {
	/* DBCS: assume double-wide characters are word characters. */
	for (i = 128; i <= 255; ++i)
	    if (MB_BYTE2LEN(i) == 2)
		spelltab.st_isw[i] = TRUE;
    }
    else if (enc_utf8)
    {
	for (i = 128; i < 256; ++i)
	{
	    int f = utf_fold(i);
	    int u = utf_toupper(i);

	    spelltab.st_isu[i] = utf_isupper(i);
	    spelltab.st_isw[i] = spelltab.st_isu[i] || utf_islower(i);
	    /* The folded/upper-cased value is different between latin1 and
	     * utf8 for 0xb5, causing E763 for no good reason.  Use the latin1
	     * value for utf-8 to avoid this. */
	    spelltab.st_fold[i] = (f < 256) ? f : i;
	    spelltab.st_upper[i] = (u < 256) ? u : i;
	}
    }
    else
#endif
    {
	/* Rough guess: use locale-dependent library functions. */
	for (i = 128; i < 256; ++i)
	{
	    if (MB_ISUPPER(i))
	    {
		spelltab.st_isw[i] = TRUE;
		spelltab.st_isu[i] = TRUE;
		spelltab.st_fold[i] = MB_TOLOWER(i);
	    }
	    else if (MB_ISLOWER(i))
	    {
		spelltab.st_isw[i] = TRUE;
		spelltab.st_upper[i] = MB_TOUPPER(i);
	    }
	}
    }
}