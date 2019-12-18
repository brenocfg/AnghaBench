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
typedef  int /*<<< orphan*/  subdir ;
typedef  int /*<<< orphan*/  portstr ;
struct TYPE_3__ {char* user; char* pass; char* host; int port; } ;
typedef  int /*<<< orphan*/  LineListPtr ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  AddLine (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  InitLineList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  URLCopyToken (char* const,size_t const,char*,size_t) ; 
 int atoi (char*) ; 
 int kMalformedURL ; 
 int kNoErr ; 
 int kTypeAscii ; 
 int kTypeBinary ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char* const) ; 
 scalar_t__ strncasecmp (char* const,char*,int) ; 
 scalar_t__ strncmp (char* const,char*,int) ; 
 char* strrchr (char*,char) ; 
 char* strtok (char*,char*) ; 

int
FTPDecodeURL(
	const FTPCIPtr cip,	/* area pointed to may be modified */
	char *const url,	/* always modified */
	LineListPtr cdlist,	/* always modified */
	char *const fn,		/* always modified */
	const size_t fnsize,
	int *const xtype,	/* optional; may be modified */
	int *const wantnlst	/* optional; always modified */
)
{
	char *cp;
	char *hstart, *hend;
	char *h2start;
	char *at1;
	char portstr[32];
	int port;
	int sc;
	char *lastslash;
	char *parsestr;
	char *tok;
	char subdir[128];
	char *semi;

	InitLineList(cdlist);
	*fn = '\0';
	if (wantnlst != NULL)
		*wantnlst = 0;
	if (xtype != NULL)
		*xtype = kTypeBinary;

	cp = NULL;	/* shut up warnings */
#ifdef HAVE_STRCASECMP
	if (strncasecmp(url, "<URL:ftp://", 11) == 0) {
		cp = url + strlen(url) - 1;
		if (*cp != '>')
			return (kMalformedURL);	/* missing closing > */
		*cp = '\0';
		cp = url + 11;
	} else if (strncasecmp(url, "ftp://", 6) == 0) {
		cp = url + 6;
	} else {
		return (-1);		/* not a RFC 1738 URL */
	}
#else	/* HAVE_STRCASECMP */
	if (strncmp(url, "<URL:ftp://", 11) == 0) {
		cp = url + strlen(url) - 1;
		if (*cp != '>')
			return (kMalformedURL);	/* missing closing > */
		*cp = '\0';
		cp = url + 11;
	} else if (strncmp(url, "ftp://", 6) == 0) {
		cp = url + 6;
	} else {
		return (-1);		/* not a RFC 1738 URL */
	}
#endif	/* HAVE_STRCASECMP */

	/* //<user>:<password>@<host>:<port>/<url-path> */

	at1 = NULL;
	for (hstart = cp; ; cp++) {
		if (*cp == '@') {
			if (at1 == NULL)
				at1 = cp;
			else
				return (kMalformedURL);
		} else if ((*cp == '\0') || (*cp == '/')) {
			hend = cp;
			break;
		}
	}

	sc = *hend;
	*hend = '\0';
	if (at1 == NULL) {
		/* no user or password */
		h2start = hstart;
	} else {
		*at1 = '\0';
		cp = strchr(hstart, ':');
		if (cp == NULL) {
			/* whole thing is the user name then */
			URLCopyToken(cip->user, sizeof(cip->user), hstart, (size_t) (at1 - hstart));
		} else if (strchr(cp + 1, ':') != NULL) {
			/* Too many colons */
			return (kMalformedURL);
		} else {
			URLCopyToken(cip->user, sizeof(cip->user), hstart, (size_t) (cp - hstart));
			URLCopyToken(cip->pass, sizeof(cip->pass), cp + 1, (size_t) (at1 - (cp + 1)));
		}
		*at1 = '@';
		h2start = at1 + 1;
	}

	cp = strchr(h2start, ':');
	if (cp == NULL) {
		/* whole thing is the host then */
		URLCopyToken(cip->host, sizeof(cip->host), h2start, (size_t) (hend - h2start));
	} else if (strchr(cp + 1, ':') != NULL) {
		/* Too many colons */
		return (kMalformedURL);
	} else {
		URLCopyToken(cip->host, sizeof(cip->host), h2start, (size_t) (cp - h2start));
		URLCopyToken(portstr, sizeof(portstr), cp + 1, (size_t) (hend - (cp + 1)));
		port = atoi(portstr);
		if (port > 0)
			cip->port = port;
	}

	*hend = (char) sc;
	if ((*hend == '\0') || ((*hend == '/') && (hend[1] == '\0'))) {
		/* no path, okay */
		return (0);
	}

	lastslash = strrchr(hend, '/');
	if (lastslash == NULL) {
		/* no path, okay */
		return (0);
	}
	*lastslash = '\0';

	if ((semi = strchr(lastslash + 1, ';')) != NULL) {
		*semi++ = '\0';
#ifdef HAVE_STRCASECMP
		if (strcasecmp(semi, "type=i") == 0) {
			if (xtype != NULL)
				*xtype = kTypeBinary;
		} else if (strcasecmp(semi, "type=a") == 0) {
			if (xtype != NULL)
				*xtype = kTypeAscii;
		} else if (strcasecmp(semi, "type=b") == 0) {
			if (xtype != NULL)
				*xtype = kTypeBinary;
		} else if (strcasecmp(semi, "type=d") == 0) {
			if (wantnlst != NULL) {
				*wantnlst = 1;
				if (xtype != NULL)
					*xtype = kTypeAscii;
			} else {
				/* You didn't want these. */
				return (kMalformedURL);
			}
		}
#else	/* HAVE_STRCASECMP */
		if (strcmp(semi, "type=i") == 0) {
			if (xtype != NULL)
				*xtype = kTypeBinary;
		} else if (strcmp(semi, "type=a") == 0) {
			if (xtype != NULL)
				*xtype = kTypeAscii;
		} else if (strcmp(semi, "type=b") == 0) {
			if (xtype != NULL)
				*xtype = kTypeBinary;
		} else if (strcmp(semi, "type=d") == 0) {
			if (wantnlst != NULL) {
				*wantnlst = 1;
				if (xtype != NULL)
					*xtype = kTypeAscii;
			} else {
				/* You didn't want these. */
				return (kMalformedURL);
			}
		}
#endif	/* HAVE_STRCASECMP */
	}
	URLCopyToken(fn, fnsize, lastslash + 1, strlen(lastslash + 1));
	for (parsestr = hend; (tok = strtok(parsestr, "/")) != NULL; parsestr = NULL) {
		URLCopyToken(subdir, sizeof(subdir), tok, strlen(tok));
		(void) AddLine(cdlist, subdir);
	}
	*lastslash = '/';
	return (kNoErr);
}