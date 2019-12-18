#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  token ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {int xferType; unsigned int port; char xferMode; scalar_t__ pass; scalar_t__ ldir; void* hasUTIME; scalar_t__ comment; scalar_t__ lastIP; void* isUnix; void* hasPASV; void* hasMDTM; void* hasSIZE; int /*<<< orphan*/  lastCall; scalar_t__ dir; scalar_t__ acct; scalar_t__ user; scalar_t__ name; scalar_t__ bookmarkName; } ;
typedef  TYPE_1__* BookmarkPtr ;

/* Variables and functions */
 int /*<<< orphan*/  FromBase64 (char*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int HexCharToNibble (char) ; 
 int /*<<< orphan*/  STRNCPY (scalar_t__,char*) ; 
 int /*<<< orphan*/  SetBookmarkDefaults (TYPE_1__*) ; 
 void* atoi (char*) ; 
 scalar_t__ kDefaultFTPPort ; 
 int /*<<< orphan*/  kPasswordMagic ; 
 scalar_t__ kPasswordMagicLen ; 
 int /*<<< orphan*/  sscanf (char*,char*,long*) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 scalar_t__ strncmp (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

int
ParseHostLine(char *line, BookmarkPtr bmp)
{
	char token[128];
	char pass[128];
	char *s, *d;
	char *tokenend;
	long L;
	int i;
	int result;
	int n, n1, n2;

	SetBookmarkDefaults(bmp);
	s = line;
	tokenend = token + sizeof(token) - 1;
	result = -1;
	for (i=1; ; i++) {
		if (*s == '\0')
			break;
		/* Some tokens may need to have a comma in them.  Since this is a
		 * field delimiter, these fields use \, to represent a comma, and
		 * \\ for a backslash.  This chunk gets the next token, paying
		 * attention to the escaped stuff.
		 */
		for (d = token; *s != '\0'; ) {
			if ((*s == '\\') && (s[1] != '\0')) {
				if (d < tokenend)
					*d++ = s[1];
				s += 2;
			} else if (*s == ',') {
				++s;
				break;
			} else if ((*s == '$') && (s[1] != '\0') && (s[2] != '\0')) {
				n1 = HexCharToNibble(s[1]);
				n2 = HexCharToNibble(s[2]);
				if ((n1 >= 0) && (n2 >= 0)) {
					n = (n1 << 4) | n2;
					if (d < tokenend)
						*(unsigned char *)d++ = (unsigned int) n;
				}
				s += 3;
			} else {
				if (d < tokenend)
					*d++ = *s;
				++s;
			}
		}
		*d = '\0';
		switch(i) {
			case 1: (void) STRNCPY(bmp->bookmarkName, token); break;
			case 2: (void) STRNCPY(bmp->name, token); break;
			case 3: (void) STRNCPY(bmp->user, token); break;
			case 4: (void) STRNCPY(bmp->pass, token); break;
			case 5: (void) STRNCPY(bmp->acct, token); break;
			case 6: (void) STRNCPY(bmp->dir, token);
					result = 0;		/* Good enough to have these fields. */
					break;
			case 7:
				if (token[0] != '\0')
					bmp->xferType = (int) token[0];
				break;
			case 8:
				/* Most of the time, we won't have a port. */
				if (token[0] == '\0')
					bmp->port = (unsigned int) kDefaultFTPPort;
				else
					bmp->port = (unsigned int) atoi(token);
				break;
			case 9:
				(void) sscanf(token, "%lx", &L);
				bmp->lastCall = (time_t) L;
				break;
			case 10: bmp->hasSIZE = atoi(token); break;
			case 11: bmp->hasMDTM = atoi(token); break;
			case 12: bmp->hasPASV = atoi(token); break;
			case 13: bmp->isUnix = atoi(token);
					result = 3;		/* Version 3 had all fields to here. */
					break;
			case 14: (void) STRNCPY(bmp->lastIP, token); break;
			case 15: (void) STRNCPY(bmp->comment, token); break;
			case 16:
			case 17:
			case 18:
			case 19:
				break;
			case 20: bmp->xferMode = token[0];
					result = 7;		/* Version 7 has all fields to here. */
					break;
			case 21: bmp->hasUTIME = atoi(token);
					break;
			case 22: (void) STRNCPY(bmp->ldir, token);
					result = 8;		/* Version 8 has all fields to here. */
					break;
			default:
					result = 99;	/* Version >8 ? */
					goto done;
		}
	}
done:

	/* Decode password, if it was base-64 encoded. */
	if (strncmp(bmp->pass, kPasswordMagic, kPasswordMagicLen) == 0) {
		FromBase64(pass, bmp->pass + kPasswordMagicLen, strlen(bmp->pass + kPasswordMagicLen), 1);
		(void) STRNCPY(bmp->pass, pass);
	}
	return (result);
}