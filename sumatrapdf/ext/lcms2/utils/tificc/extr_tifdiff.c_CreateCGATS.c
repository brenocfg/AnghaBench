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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  cmsHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  AddOneCGATSRow (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CGATSout ; 
 int Channels ; 
 int /*<<< orphan*/ * ColorantStat ; 
 int /*<<< orphan*/  ColorimetricStat ; 
 int /*<<< orphan*/  EuclideanStat ; 
 int /*<<< orphan*/  FatalError (char*) ; 
 int /*<<< orphan*/  cmsIT8Alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsIT8Free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsIT8SaveToFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsIT8SetComment (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cmsIT8SetDataFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  cmsIT8SetPropertyDbl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cmsIT8SetPropertyStr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cmsIT8SetSheetType (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void CreateCGATS(const char* TiffName1, const char* TiffName2)
{
    cmsHANDLE hIT8 = cmsIT8Alloc(0);
    time_t ltime;
    char Buffer[256];

    cmsIT8SetSheetType(NULL, hIT8, "TIFFDIFF");


    sprintf(Buffer, "Differences between %s and %s", TiffName1, TiffName2);

    cmsIT8SetComment(NULL, hIT8, Buffer);

    cmsIT8SetPropertyStr(NULL, hIT8, "ORIGINATOR", "TIFFDIFF");
    time( &ltime );
    strcpy(Buffer, ctime(&ltime));
    Buffer[strlen(Buffer)-1] = 0;     // Remove the nasty "\n"

    cmsIT8SetPropertyStr(NULL, hIT8, "CREATED", Buffer);

    cmsIT8SetComment(NULL, hIT8, " ");

    cmsIT8SetPropertyDbl(NULL, hIT8, "NUMBER_OF_FIELDS", 6);


    cmsIT8SetDataFormat(NULL, hIT8, 0, "SAMPLE_ID");
    cmsIT8SetDataFormat(NULL, hIT8, 1, "PER100_EQUAL");
    cmsIT8SetDataFormat(NULL, hIT8, 2, "MEAN_DE");
    cmsIT8SetDataFormat(NULL, hIT8, 3, "STDEV_DE");
    cmsIT8SetDataFormat(NULL, hIT8, 4, "MIN_DE");
    cmsIT8SetDataFormat(NULL, hIT8, 5, "MAX_DE");


    switch (Channels) {

    case 1:
            cmsIT8SetPropertyDbl(NULL, hIT8, "NUMBER_OF_SETS", 3);
            AddOneCGATSRow(hIT8, "GRAY_PLANE", &ColorantStat[0]);
            break;

    case 3:
            cmsIT8SetPropertyDbl(NULL, hIT8, "NUMBER_OF_SETS", 5);
            AddOneCGATSRow(hIT8, "R_PLANE", &ColorantStat[0]);
            AddOneCGATSRow(hIT8, "G_PLANE", &ColorantStat[1]);
            AddOneCGATSRow(hIT8, "B_PLANE", &ColorantStat[2]);
            break;


    case 4:
            cmsIT8SetPropertyDbl(NULL, hIT8, "NUMBER_OF_SETS", 6);
            AddOneCGATSRow(hIT8, "C_PLANE", &ColorantStat[0]);
            AddOneCGATSRow(hIT8, "M_PLANE", &ColorantStat[1]);
            AddOneCGATSRow(hIT8, "Y_PLANE", &ColorantStat[2]);
            AddOneCGATSRow(hIT8, "K_PLANE", &ColorantStat[3]);
            break;

    default: FatalError("Internal error: Bad ColorSpace");

    }

    AddOneCGATSRow(hIT8, "EUCLIDEAN",    &EuclideanStat);
    AddOneCGATSRow(hIT8, "COLORIMETRIC", &ColorimetricStat);

    cmsIT8SaveToFile(NULL, hIT8, CGATSout);
    cmsIT8Free(NULL, hIT8);
}