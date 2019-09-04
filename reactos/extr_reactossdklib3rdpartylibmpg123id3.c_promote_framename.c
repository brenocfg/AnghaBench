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
typedef  int /*<<< orphan*/  old ;
typedef  int /*<<< orphan*/  mpg123_handle ;

/* Variables and functions */
 scalar_t__ VERBOSE3 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int promote_framename(mpg123_handle *fr, char *id) /* fr because of VERBOSE macros */
{
	size_t i;
	char *old[] =
	{
		"COM",  "TAL",  "TBP",  "TCM",  "TCO",  "TCR",  "TDA",  "TDY",  "TEN",  "TFT",
		"TIM",  "TKE",  "TLA",  "TLE",  "TMT",  "TOA",  "TOF",  "TOL",  "TOR",  "TOT",
		"TP1",  "TP2",  "TP3",  "TP4",  "TPA",  "TPB",  "TRC",  "TDA",  "TRK",  "TSI",
		"TSS",  "TT1",  "TT2",  "TT3",  "TXT",  "TXX",  "TYE"
	};
	char *new[] =
	{
		"COMM", "TALB", "TBPM", "TCOM", "TCON", "TCOP", "TDAT", "TDLY", "TENC", "TFLT",
		"TIME", "TKEY", "TLAN", "TLEN", "TMED", "TOPE", "TOFN", "TOLY", "TORY", "TOAL",
		"TPE1", "TPE2", "TPE3", "TPE4", "TPOS", "TPUB", "TSRC", "TRDA", "TRCK", "TSIZ",
		"TSSE", "TIT1", "TIT2", "TIT3", "TEXT", "TXXX", "TYER"
	};
	for(i=0; i<sizeof(old)/sizeof(char*); ++i)
	{
		if(!strncmp(id, old[i], 3))
		{
			memcpy(id, new[i], 4);
			if(VERBOSE3) fprintf(stderr, "Translated ID3v2.2 frame %s to %s\n", old[i], new[i]);
			return 0;
		}
	}
	if(VERBOSE3) fprintf(stderr, "Ignoring untranslated ID3v2.2 frame %c%c%c\n", id[0], id[1], id[2]);
	return -1;
}