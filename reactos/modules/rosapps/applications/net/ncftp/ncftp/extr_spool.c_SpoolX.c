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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  spathname2 ;
typedef  int /*<<< orphan*/  spathname ;
typedef  int /*<<< orphan*/  sdir ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  ldir2 ;
struct TYPE_2__ {char* defaultAnonPassword; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FOPEN_WRITE_TEXT ; 
 int /*<<< orphan*/  FTPGetLocalCWD (char*,int) ; 
 scalar_t__ MkSpoolDir (char*,int) ; 
 int /*<<< orphan*/  SpoolName (char*,char*,int,char const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ToBase64 (char*,char const* const,int /*<<< orphan*/ ,int) ; 
 char* YESNO (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__ gLib ; 
 int /*<<< orphan*/  gSpoolSerial ; 
 int /*<<< orphan*/  gUnprocessedJobs ; 
 scalar_t__ kDefaultFTPPort ; 
 int /*<<< orphan*/  kPasswordMagic ; 
 int kPasswordMagicLen ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ rename (char*,char*) ; 
 scalar_t__ strcmp (char const* const,char*) ; 
 int /*<<< orphan*/  strlen (char const* const) ; 
 int umask (int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int
SpoolX(
	const char *const op,
	const char *const rfile,
	const char *const rdir,
	const char *const lfile,
	const char *const ldir,
	const char *const host,
	const char *const ip,
	const unsigned int port,
	const char *const user,
	const char *const passclear,
	int xtype,
	int recursive,
	int delete,
	int passive,
	const char *const precmd,
	const char *const perfilecmd,
	const char *const postcmd,
	time_t when)
{
	char sdir[256];
	char pass[160];
	char spathname[256];
	char spathname2[256];
	char ldir2[256];
	FILE *fp;
#if defined(WIN32) || defined(_WINDOWS)
#else
	mode_t um;
#endif

	if (MkSpoolDir(sdir, sizeof(sdir)) < 0)
		return (-1);

	gSpoolSerial++;
	SpoolName(sdir, spathname2, sizeof(spathname2), op[0], gSpoolSerial, when);
	SpoolName(sdir, spathname, sizeof(spathname), 'z', gSpoolSerial, when);
#if defined(WIN32) || defined(_WINDOWS)
	fp = fopen(spathname, FOPEN_WRITE_TEXT);
#else
	um = umask(077);
	fp = fopen(spathname, FOPEN_WRITE_TEXT);
	(void) umask(um);
#endif
	if (fp == NULL)
		return (-1);

	if (fprintf(fp, "# This is a NcFTP spool file entry.\n# Run the \"ncftpbatch\" program to process the spool directory.\n#\n") < 0)
		goto err;
	if (fprintf(fp, "op=%s\n", op) < 0)
		goto err;
	if (fprintf(fp, "hostname=%s\n", host) < 0)
		goto err;
	if ((ip != NULL) && (ip[0] != '\0') && (fprintf(fp, "host-ip=%s\n", ip) < 0))
		goto err;
	if ((port > 0) && (port != (unsigned int) kDefaultFTPPort) && (fprintf(fp, "port=%u\n", port) < 0))
		goto err;
	if ((user != NULL) && (user[0] != '\0') && (strcmp(user, "anonymous") != 0) && (fprintf(fp, "user=%s\n", user) < 0))
		goto err;
	if ((strcmp(user, "anonymous") != 0) && (passclear != NULL) && (passclear[0] != '\0')) {
		(void) memcpy(pass, kPasswordMagic, kPasswordMagicLen);
		ToBase64(pass + kPasswordMagicLen, passclear, strlen(passclear), 1);
		if (fprintf(fp, "pass=%s\n", pass) < 0)
			goto err;
	} else if ((strcmp(user, "anonymous") == 0) && (gLib.defaultAnonPassword[0] != '\0')) {
		if (fprintf(fp, "anon-pass=%s\n", gLib.defaultAnonPassword) < 0)
			goto err;
	}
	if (fprintf(fp, "xtype=%c\n", xtype) < 0)
		goto err;
	if ((recursive != 0) && (fprintf(fp, "recursive=%s\n", YESNO(recursive)) < 0))
		goto err;
	if ((delete != 0) && (fprintf(fp, "delete=%s\n", YESNO(delete)) < 0))
		goto err;
	if (fprintf(fp, "passive=%d\n", passive) < 0)
		goto err;
	if (fprintf(fp, "remote-dir=%s\n", rdir) < 0)
		goto err;
	if ((ldir == NULL) || (ldir[0] == '\0') || (strcmp(ldir, ".") == 0)) {
		/* Use current process' working directory. */
		FTPGetLocalCWD(ldir2, sizeof(ldir2));
		if (fprintf(fp, "local-dir=%s\n", ldir2) < 0)
			goto err;
	} else {
		if (fprintf(fp, "local-dir=%s\n", ldir) < 0)
			goto err;
	}
	if (fprintf(fp, "remote-file=%s\n", rfile) < 0)
		goto err;
	if (fprintf(fp, "local-file=%s\n", lfile) < 0)
		goto err;
	if ((precmd != NULL) && (precmd[0] != '\0') && (fprintf(fp, "pre-command=%s\n", precmd) < 0))
		goto err;
	if ((perfilecmd != NULL) && (perfilecmd[0] != '\0') && (fprintf(fp, "per-file-command=%s\n", perfilecmd) < 0))
		goto err;
	if ((postcmd != NULL) && (postcmd[0] != '\0') && (fprintf(fp, "post-command=%s\n", postcmd) < 0))
		goto err;

	if (fclose(fp) < 0)
		goto err2;

	/* Move the spool file into its "live" name. */
	if (rename(spathname, spathname2) < 0) {
		perror("rename spoolfile failed");
		goto err3;
	}
	gUnprocessedJobs++;
	return (0);

err:
	(void) fclose(fp);
err2:
	perror("write to spool file failed");
err3:
	(void) unlink(spathname);
	return (-1);
}