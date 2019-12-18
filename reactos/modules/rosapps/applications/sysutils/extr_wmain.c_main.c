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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 scalar_t__ GlobalAlloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  a2w (char*,int /*<<< orphan*/ *) ; 
 int lstrlenA (char*) ; 
 int wmain (int,int /*<<< orphan*/ **) ; 

int main(int argc, char *argv[])
{
	wchar_t	** wargv;
	int	i;
	int	ec;

	wargv = (wchar_t **) GlobalAlloc(
				sizeof(void*) * argc,
				0
				);
	for(i=0;i<argc;++i)
	{
		wargv[i] = (wchar_t*) GlobalAlloc(
				sizeof(wchar_t) * (1+lstrlenA(argv[i])),
				0
				);
		a2w(argv[i],wargv[i]);
	}
	wargv[i] = NULL;
	ec = wmain(argc,wargv);
	for (i=0;wargv[i];++i) GlobalFree(wargv[i]);
	return ec;
}