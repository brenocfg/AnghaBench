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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEG_NUMBER_PLACEHOLDER ; 
 int asprintf (char**,char*,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int strcspn (char*,int /*<<< orphan*/ ) ; 
 int strspn (char*,int /*<<< orphan*/ ) ; 
 char* vlc_strftime (char*) ; 

__attribute__((used)) static char *formatSegmentPath( char *psz_path, uint32_t i_seg )
{
    char *psz_result;
    char *psz_firstNumSign;

    if ( ! ( psz_result  = vlc_strftime( psz_path ) ) )
        return NULL;

    psz_firstNumSign = psz_result + strcspn( psz_result, SEG_NUMBER_PLACEHOLDER );
    if ( *psz_firstNumSign )
    {
        char *psz_newResult;
        int i_cnt = strspn( psz_firstNumSign, SEG_NUMBER_PLACEHOLDER );
        int ret;

        *psz_firstNumSign = '\0';
        ret = asprintf( &psz_newResult, "%s%0*d%s", psz_result, i_cnt, i_seg, psz_firstNumSign + i_cnt );
        free ( psz_result );
        if ( ret < 0 )
            return NULL;
        psz_result = psz_newResult;
    }

    return psz_result;
}