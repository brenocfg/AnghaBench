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
typedef  int mode_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  S_IFBLK 136 
#define  S_IFCHR 135 
#define  S_IFDIR 134 
#define  S_IFDOOR 133 
#define  S_IFIFO 132 
#define  S_IFLNK 131 
 int S_IFMT ; 
#define  S_IFPORT 130 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char) ; 

__attribute__((used)) static void
print_what(FILE *fp, mode_t what)
{
	char symbol;

	switch (what & S_IFMT) {
	case S_IFBLK:
		symbol = 'B';
		break;
	case S_IFCHR:
		symbol = 'C';
		break;
	case S_IFDIR:
		symbol = '/';
		break;
#ifdef S_IFDOOR
	case S_IFDOOR:
		symbol = '>';
		break;
#endif
	case S_IFIFO:
		symbol = '|';
		break;
	case S_IFLNK:
		symbol = '@';
		break;
#ifdef S_IFPORT
	case S_IFPORT:
		symbol = 'P';
		break;
#endif
	case S_IFSOCK:
		symbol = '=';
		break;
	case S_IFREG:
		symbol = 'F';
		break;
	default:
		symbol = '?';
		break;
	}
	(void) fprintf(fp, "%c", symbol);
}