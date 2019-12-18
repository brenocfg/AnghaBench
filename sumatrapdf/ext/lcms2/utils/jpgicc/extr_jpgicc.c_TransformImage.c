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
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/ * cmsHTRANSFORM ;
typedef  int /*<<< orphan*/ * cmsHPROFILE ;

/* Variables and functions */
 int /*<<< orphan*/  Alarm ; 
 scalar_t__ BlackPointCompensation ; 
 int /*<<< orphan*/  Compressor ; 
 int /*<<< orphan*/  ComputeOutputFormatDescriptor (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CreateITU2PCS_ICC () ; 
 int /*<<< orphan*/ * CreatePCS2ITU_ICC () ; 
 int /*<<< orphan*/  Decompressor ; 
 int /*<<< orphan*/  DoTransform (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FatalError (char*) ; 
 scalar_t__ GamutCheck ; 
 int GetDevicelinkColorSpace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetInputPixelType () ; 
 int GetProfileColorSpace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IgnoreEmbedded ; 
 int /*<<< orphan*/  Intent ; 
 int /*<<< orphan*/  ObserverAdaptationState ; 
 int /*<<< orphan*/ * OpenStockProfile (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ PT_Lab ; 
 int PrecalcMode ; 
 int /*<<< orphan*/  PrintProfileInformation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ProofingIntent ; 
 int /*<<< orphan*/ * SaveEmbedded ; 
 int /*<<< orphan*/  SaveMemoryBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ T_COLORSPACE (int /*<<< orphan*/ ) ; 
 scalar_t__ Verbose ; 
 int /*<<< orphan*/  WriteOutputFields (int) ; 
 scalar_t__ _cmsICCcolorSpace (int /*<<< orphan*/ *,scalar_t__) ; 
 char* cProofing ; 
 int /*<<< orphan*/  cmsCloseProfile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsCreateProofingTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsDeleteTransform (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmsFLAGS_BLACKPOINTCOMPENSATION ; 
 int /*<<< orphan*/  cmsFLAGS_GAMUTCHECK ; 
 int /*<<< orphan*/  cmsFLAGS_HIGHRESPRECALC ; 
 int /*<<< orphan*/  cmsFLAGS_LOWRESPRECALC ; 
 int /*<<< orphan*/  cmsFLAGS_NOOPTIMIZE ; 
 int /*<<< orphan*/  cmsFLAGS_SOFTPROOFING ; 
 scalar_t__ cmsGetColorSpace (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromFile (char*,char*) ; 
 int /*<<< orphan*/ * cmsOpenProfileFromMem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetAdaptationState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmsSetAlarmCodes (int /*<<< orphan*/ ) ; 
 scalar_t__ cmsstrcasecmp (char*,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jcopy_markers_execute (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jpeg_copy_critical_parameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lIsDeviceLink ; 
 scalar_t__ read_icc_profile (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static
int TransformImage(char *cDefInpProf, char *cOutputProf)
{
       cmsHPROFILE hIn, hOut, hProof;
       cmsHTRANSFORM xform;
       cmsUInt32Number wInput, wOutput;
       int OutputColorSpace;
       cmsUInt32Number dwFlags = 0;
       cmsUInt32Number EmbedLen;
       cmsUInt8Number* EmbedBuffer;


       cmsSetAdaptationState(ObserverAdaptationState);

       if (BlackPointCompensation) {

            dwFlags |= cmsFLAGS_BLACKPOINTCOMPENSATION;
       }


       switch (PrecalcMode) {

       case 0: dwFlags |= cmsFLAGS_NOOPTIMIZE; break;
       case 2: dwFlags |= cmsFLAGS_HIGHRESPRECALC; break;
       case 3: dwFlags |= cmsFLAGS_LOWRESPRECALC; break;
       default:;
       }


       if (GamutCheck) {
            dwFlags |= cmsFLAGS_GAMUTCHECK;
            cmsSetAlarmCodes(Alarm);
       }

       // Take input color space
       wInput = GetInputPixelType();

        if (lIsDeviceLink) {

            hIn = cmsOpenProfileFromFile(cDefInpProf, "r");
            hOut = NULL;
            hProof = NULL;
       }
        else {

        if (!IgnoreEmbedded && read_icc_profile(&Decompressor, &EmbedBuffer, &EmbedLen))
        {
              hIn = cmsOpenProfileFromMem(EmbedBuffer, EmbedLen);

               if (Verbose) {

                  fprintf(stdout, " (Embedded profile found)\n");
                  PrintProfileInformation(NULL, hIn);
                  fflush(stdout);
              }

               if (hIn != NULL && SaveEmbedded != NULL)
                          SaveMemoryBlock(EmbedBuffer, EmbedLen, SaveEmbedded);

              free(EmbedBuffer);
        }
        else
        {
            // Default for ITU/Fax
            if (cDefInpProf == NULL && T_COLORSPACE(wInput) == PT_Lab)
                cDefInpProf = "*Lab";

            if (cDefInpProf != NULL && cmsstrcasecmp(cDefInpProf, "*lab") == 0)
                hIn = CreateITU2PCS_ICC();
            else
                hIn = OpenStockProfile(0, cDefInpProf);
       }

        if (cOutputProf != NULL && cmsstrcasecmp(cOutputProf, "*lab") == 0)
            hOut = CreatePCS2ITU_ICC();
        else
        hOut = OpenStockProfile(0, cOutputProf);

       hProof = NULL;
       if (cProofing != NULL) {

           hProof = OpenStockProfile(0, cProofing);
           if (hProof == NULL) {
            FatalError("Proofing profile couldn't be read.");
           }
           dwFlags |= cmsFLAGS_SOFTPROOFING;
          }
       }

        if (!hIn)
            FatalError("Input profile couldn't be read.");
        if (!lIsDeviceLink && !hOut)
            FatalError("Output profile couldn't be read.");

       // Assure both, input profile and input JPEG are on same colorspace
       if (cmsGetColorSpace(NULL, hIn) != _cmsICCcolorSpace(NULL, T_COLORSPACE(wInput)))
              FatalError("Input profile is not operating in proper color space");


       // Output colorspace is given by output profile

        if (lIsDeviceLink) {
            OutputColorSpace = GetDevicelinkColorSpace(hIn);
        }
        else {
            OutputColorSpace = GetProfileColorSpace(hOut);
        }

       jpeg_copy_critical_parameters(&Decompressor, &Compressor);

       WriteOutputFields(OutputColorSpace);

       wOutput      = ComputeOutputFormatDescriptor(wInput, OutputColorSpace);


       xform = cmsCreateProofingTransform(hIn, wInput,
                                          hOut, wOutput,
                                          hProof, Intent,
                                          ProofingIntent, dwFlags);
       if (xform == NULL)
                 FatalError("Cannot transform by using the profiles");

       DoTransform(xform, OutputColorSpace);


       jcopy_markers_execute(&Decompressor, &Compressor);

       cmsDeleteTransform(NULL, xform);
       cmsCloseProfile(NULL, hIn);
       cmsCloseProfile(NULL, hOut);
       if (hProof) cmsCloseProfile(NULL, hProof);

       return 1;
}