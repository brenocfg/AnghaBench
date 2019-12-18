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
typedef  int /*<<< orphan*/  cmsToneCurve ;
typedef  int /*<<< orphan*/  cmsPipeline ;
typedef  int /*<<< orphan*/  cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateLinear () ; 
 int /*<<< orphan*/ * CreateStep () ; 
 int /*<<< orphan*/  SetTextTags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsAT_BEGIN ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsFreeToneCurve (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsOpenProfileFromFile (char*,char*) ; 
 int /*<<< orphan*/ * cmsPipelineAlloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cmsPipelineFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsPipelineInsertStage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetColorSpace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetDeviceClass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetPCS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetProfileVersion (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  cmsSigAToB0Tag ; 
 int /*<<< orphan*/  cmsSigLabData ; 
 int /*<<< orphan*/  cmsSigLinkClass ; 
 int /*<<< orphan*/  cmsStageAllocToneCurves (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cmsWriteTag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *argv[])
{
	cmsHPROFILE hProfile;
	cmsPipeline *AToB0;
	cmsToneCurve* PreLinear[3];
	cmsToneCurve *Lin, *Step;

	fprintf(stderr, "Creating lcmstiff8.icm...");
    
    remove("lcmstiff8.icm");
	hProfile = cmsOpenProfileFromFile("lcmstiff8.icm", "w");

	// Create linearization
	Lin  = CreateLinear();
	Step = CreateStep();

	PreLinear[0] = Lin;
	PreLinear[1] = Step;
	PreLinear[2] = Step;

    AToB0 = cmsPipelineAlloc(0, 3, 3);

	cmsPipelineInsertStage(AToB0, 
		cmsAT_BEGIN, cmsStageAllocToneCurves(0, 3, PreLinear));

	cmsSetColorSpace(hProfile, cmsSigLabData);
	cmsSetPCS(hProfile, cmsSigLabData);
	cmsSetDeviceClass(hProfile, cmsSigLinkClass);
	cmsSetProfileVersion(hProfile, 4.2);

    cmsWriteTag(hProfile, cmsSigAToB0Tag, AToB0);
	
    SetTextTags(hProfile);

	cmsCloseProfile(hProfile);

	cmsFreeToneCurve(Lin);
	cmsFreeToneCurve(Step);
	cmsPipelineFree(AToB0);
		
	fprintf(stderr, "Done.\n");

	return 0;
}