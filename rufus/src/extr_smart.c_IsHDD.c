#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {char const* name; scalar_t__ vid; scalar_t__ pid; scalar_t__ score; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARRAYSIZE (TYPE_1__*) ; 
 scalar_t__ DRIVE_FIXED ; 
 int GB ; 
 int GetDriveSize (int /*<<< orphan*/ ) ; 
 scalar_t__ GetDriveTypeFromIndex (int /*<<< orphan*/ ) ; 
 scalar_t__ _strnicmp (char const*,char*,size_t) ; 
 int /*<<< orphan*/  duprintf (char*,int) ; 
 TYPE_1__* str_adjust ; 
 TYPE_1__* str_score ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 
 TYPE_1__* vid_score ; 
 TYPE_1__* vidpid_score ; 

int IsHDD(DWORD DriveIndex, uint16_t vid, uint16_t pid, const char* strid)
{
	int score = 0;
	size_t i, mlen, ilen;
	BOOL wc;
	uint64_t drive_size;

	// Boost the score if fixed, as these are *generally* HDDs
	// NB: Due to a Windows API limitation, drives with no mounted partition will never have DRIVE_FIXED
	if (GetDriveTypeFromIndex(DriveIndex) == DRIVE_FIXED)
		score += 3;

	// Adjust the score depending on the size
	drive_size = GetDriveSize(DriveIndex);
	if (drive_size > 512*GB)
		score += 10;
	else if (drive_size < 8*GB)
		score -= 10;

	// Check the string against well known HDD identifiers
	if (strid != NULL) {
		ilen = strlen(strid);
		for (i=0; i<ARRAYSIZE(str_score); i++) {
			mlen = strlen(str_score[i].name);
			if (mlen > ilen)
				break;
			wc = (str_score[i].name[mlen-1] == '#');
			if ( (_strnicmp(strid, str_score[i].name, mlen-((wc)?1:0)) == 0)
			  && ((!wc) || ((strid[mlen] >= '0') && (strid[mlen] <= '9'))) ) {
				score += str_score[i].score;
				break;
			}
		}
	}

	// Adjust for oddball devices
	if (strid != NULL) {
		for (i=0; i<ARRAYSIZE(str_adjust); i++)
			if (strstr(strid, str_adjust[i].name) != NULL)
				score += str_adjust[i].score;
	}

	// Check against known VIDs
	for (i=0; i<ARRAYSIZE(vid_score); i++) {
		if (vid == vid_score[i].vid) {
			score += vid_score[i].score;
			break;
		}
	}

	// Check against known VID:PIDs
	for (i=0; i<ARRAYSIZE(vidpid_score); i++) {
		if ((vid == vidpid_score[i].vid) && (pid == vidpid_score[i].pid)) {
			score += vidpid_score[i].score;
			break;
		}
	}

	duprintf("  Score: %d\n", score);
	return score;
}