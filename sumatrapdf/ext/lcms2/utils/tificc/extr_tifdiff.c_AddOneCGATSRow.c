#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsHANDLE ;
struct TYPE_5__ {double Min; double Peak; } ;
typedef  TYPE_1__* LPSTAT ;

/* Variables and functions */
 double Mean (TYPE_1__*) ; 
 double Std (TYPE_1__*) ; 
 int /*<<< orphan*/  cmsIT8SetData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  cmsIT8SetDataDbl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,double) ; 

__attribute__((used)) static
void AddOneCGATSRow(cmsHANDLE hIT8, char *Name, LPSTAT st)
{

    double Per100 = 100.0 * ((255.0 - Mean(st)) / 255.0);

    cmsIT8SetData(NULL, hIT8,    Name, "SAMPLE_ID", Name);
    cmsIT8SetDataDbl(NULL, hIT8, Name, "PER100_EQUAL", Per100);
    cmsIT8SetDataDbl(NULL, hIT8, Name, "MEAN_DE", Mean(st));
    cmsIT8SetDataDbl(NULL, hIT8, Name, "STDEV_DE", Std(st));
    cmsIT8SetDataDbl(NULL, hIT8, Name, "MIN_DE", st ->Min);
    cmsIT8SetDataDbl(NULL, hIT8, Name, "MAX_DE", st ->Peak);

}