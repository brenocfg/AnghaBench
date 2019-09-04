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
typedef  int /*<<< orphan*/  tok ;
struct TYPE_3__ {char* bookmarkName; char* pass; int xferType; int hasSIZE; int hasMDTM; int hasPASV; int isUnix; char* lastIP; int xferMode; int hasUTIME; int /*<<< orphan*/  ldir; int /*<<< orphan*/  comment; scalar_t__ lastCall; scalar_t__ port; int /*<<< orphan*/  dir; int /*<<< orphan*/  acct; int /*<<< orphan*/  user; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Bookmark ;

/* Variables and functions */
 char* BmEscapeTok (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ToBase64 (char*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  kPasswordMagic ; 
 int kPasswordMagicLen ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int
WriteBmLine(Bookmark *bmp, FILE *outfp, int savePassword)
{
	char tok[256];
	char pass[160];

	if (fprintf(outfp, "%s", bmp->bookmarkName) < 0) return (-1) ;/*1*/
	if (fprintf(outfp, ",%s", BmEscapeTok(tok, sizeof(tok), bmp->name)) < 0) return (-1) ;/*2*/
	if (fprintf(outfp, ",%s", BmEscapeTok(tok, sizeof(tok), bmp->user)) < 0) return (-1) ;/*3*/
	if ((bmp->pass[0] != '\0') && (savePassword == 1)) {
		(void) memcpy(pass, kPasswordMagic, kPasswordMagicLen);
		ToBase64(pass + kPasswordMagicLen, bmp->pass, strlen(bmp->pass), 1);
		if (fprintf(outfp, ",%s", pass) < 0) return (-1) ;/*4*/
	} else {
		if (fprintf(outfp, ",%s", "") < 0) return (-1) ;/*4*/
	}
	if (fprintf(outfp, ",%s", BmEscapeTok(tok, sizeof(tok), bmp->acct)) < 0) return (-1) ;/*5*/
	if (fprintf(outfp, ",%s", BmEscapeTok(tok, sizeof(tok), bmp->dir)) < 0) return (-1) ;/*6*/
	if (fprintf(outfp, ",%c", bmp->xferType) < 0) return (-1) ;/*7*/
	if (fprintf(outfp, ",%u", (unsigned int) bmp->port) < 0) return (-1) ;/*8*/
	if (fprintf(outfp, ",%lu", (unsigned long) bmp->lastCall) < 0) return (-1) ;/*9*/
	if (fprintf(outfp, ",%d", bmp->hasSIZE) < 0) return (-1) ;/*10*/
	if (fprintf(outfp, ",%d", bmp->hasMDTM) < 0) return (-1) ;/*11*/
	if (fprintf(outfp, ",%d", bmp->hasPASV) < 0) return (-1) ;/*12*/
	if (fprintf(outfp, ",%d", bmp->isUnix) < 0) return (-1) ;/*13*/
	if (fprintf(outfp, ",%s", bmp->lastIP) < 0) return (-1) ;/*14*/
	if (fprintf(outfp, ",%s", BmEscapeTok(tok, sizeof(tok), bmp->comment)) < 0) return (-1) ;/*15*/
	if (fprintf(outfp, ",%s", "") < 0) return (-1) ;/*16*/
	if (fprintf(outfp, ",%s", "") < 0) return (-1) ;/*17*/
	if (fprintf(outfp, ",%s", "") < 0) return (-1) ;/*18*/
	if (fprintf(outfp, ",%s", "") < 0) return (-1) ;/*19*/
	if (fprintf(outfp, ",%c", bmp->xferMode) < 0) return (-1) ;/*20*/
	if (fprintf(outfp, ",%d", bmp->hasUTIME) < 0) return (-1) ;/*21*/
	if (fprintf(outfp, ",%s", BmEscapeTok(tok, sizeof(tok), bmp->ldir)) < 0) return (-1) ;/*22*/
	if (fprintf(outfp, "\n") < 0) return (-1) ;
	if (fflush(outfp) < 0) return (-1);
	return (0);
}