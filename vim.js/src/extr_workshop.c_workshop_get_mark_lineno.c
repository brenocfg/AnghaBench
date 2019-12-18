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
typedef  int /*<<< orphan*/  char_u ;
typedef  int /*<<< orphan*/  buf_T ;

/* Variables and functions */
 scalar_t__ WSDLEVEL (int) ; 
 int WS_TRACE ; 
 int WS_TRACE_VERBOSE ; 
 int buf_findsign (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * buflist_findname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wstrace (char*,char*,int) ; 

int
workshop_get_mark_lineno(
	char	*filename,
	int	 markId)
{
    buf_T	*buf;		/* buffer containing filename */
    int		lineno;		/* line number of filename in buf */

    /* Get mark line number */
#ifdef WSDEBUG_TRACE
    if (WSDLEVEL(WS_TRACE_VERBOSE | WS_TRACE))
	wstrace("workshop_get_mark_lineno(%s, %d)\n",
		filename, markId);
#endif

    lineno = 0;
    buf = buflist_findname((char_u *)filename);
    if (buf != NULL)
	lineno = buf_findsign(buf, markId);

    return lineno;
}