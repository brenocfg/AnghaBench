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
typedef  scalar_t__ gunichar ;
typedef  int glong ;
struct TYPE_2__ {int /*<<< orphan*/  case_sensitive; } ;

/* Variables and functions */
 int const G_MAXLONG ; 
 unsigned int MIN3 (unsigned int,unsigned int,int) ; 
 unsigned int UINT_MAX ; 
 TYPE_1__ config ; 
 scalar_t__ g_unichar_tolower (scalar_t__) ; 
 scalar_t__ g_utf8_get_char (char const*) ; 
 char* g_utf8_next_char (char const*) ; 

unsigned int levenshtein ( const char *needle, const glong needlelen, const char *haystack, const glong haystacklen )
{
    if ( needlelen == G_MAXLONG ) {
        // String to long, we cannot handle this.
        return UINT_MAX;
    }
    unsigned int column[needlelen + 1];
    for ( glong y = 0; y < needlelen; y++ ) {
        column[y] = y;
    }
    // Removed out of the loop, otherwise static code analyzers think it is unset.. silly but true.
    // old loop: for ( glong y = 0; y <= needlelen; y++)
    column[needlelen] = needlelen;
    for ( glong x = 1; x <= haystacklen; x++ ) {
        const char *needles = needle;
        column[0] = x;
        gunichar   haystackc = g_utf8_get_char ( haystack );
        if ( !config.case_sensitive ) {
            haystackc = g_unichar_tolower ( haystackc );
        }
        for ( glong y = 1, lastdiag = x - 1; y <= needlelen; y++ ) {
            gunichar needlec = g_utf8_get_char ( needles );
            if ( !config.case_sensitive ) {
                needlec = g_unichar_tolower ( needlec );
            }
            unsigned int olddiag = column[y];
            column[y] = MIN3 ( column[y] + 1, column[y - 1] + 1, lastdiag + ( needlec == haystackc ? 0 : 1 ) );
            lastdiag  = olddiag;
            needles   = g_utf8_next_char ( needles );
        }
        haystack = g_utf8_next_char ( haystack );
    }
    return column[needlelen];
}