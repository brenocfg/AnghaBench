#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int wBitsPerSample; int nChannels; int nSamplesPerSec; } ;
typedef  TYPE_2__ WAVEFORMATEX ;
struct TYPE_6__ {long long ll; } ;
struct TYPE_8__ {scalar_t__ sizeOut; TYPE_1__ value; int /*<<< orphan*/  param; } ;
typedef  int BOOL ;
typedef  TYPE_3__ ALpv ;
typedef  scalar_t__ ALport ;

/* Variables and functions */
 int /*<<< orphan*/  AL_RATE ; 
 int /*<<< orphan*/  AL_SAMPFMT_TWOSCOMP ; 
 int /*<<< orphan*/  AL_SAMPLE_16 ; 
 int /*<<< orphan*/  AL_SAMPLE_8 ; 
 int False ; 
 int True ; 
 int /*<<< orphan*/  alClosePort (scalar_t__) ; 
 int alGetChannels (int /*<<< orphan*/ ) ; 
 char* alGetErrorString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alGetFillable (scalar_t__) ; 
 int /*<<< orphan*/  alGetResource (scalar_t__) ; 
 int alGetWidth (int /*<<< orphan*/ ) ; 
 scalar_t__ alOpenPort (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alSetChannels (int /*<<< orphan*/ ,int) ; 
 scalar_t__ alSetParams (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  alSetSampFmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alSetWidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audioconfig ; 
 int combinedFrameSize ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int g_snd_rate ; 
 int g_swapaudio ; 
 int /*<<< orphan*/  maxFillable ; 
 int /*<<< orphan*/  oserror () ; 
 scalar_t__ output_port ; 
 int /*<<< orphan*/  resource ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  width ; 

BOOL
wave_out_set_format(WAVEFORMATEX * pwfx)
{
	int channels;
	int frameSize, channelCount;
	ALpv params;

#if (defined(IRIX_DEBUG))
	fprintf(stderr, "wave_out_set_format: init...\n");
#endif

	g_swapaudio = False;
	if (pwfx->wBitsPerSample == 8)
		width = AL_SAMPLE_8;
	else if (pwfx->wBitsPerSample == 16)
	{
		width = AL_SAMPLE_16;
		/* Do we need to swap the 16bit values? (Are we BigEndian) */
#if (defined(B_ENDIAN))
		g_swapaudio = 1;
#else
		g_swapaudio = 0;
#endif
	}

	/* Limited support to configure an opened audio port in IRIX.  The
	   number of channels is a static setting and can not be changed after
	   a port is opened.  So if the number of channels remains the same, we
	   can configure other settings; otherwise we have to reopen the audio
	   port, using same config. */

	channels = pwfx->nChannels;
	g_snd_rate = pwfx->nSamplesPerSec;

	alSetSampFmt(audioconfig, AL_SAMPFMT_TWOSCOMP);
	alSetWidth(audioconfig, width);
	if (channels != alGetChannels(audioconfig))
	{
		alClosePort(output_port);
		alSetChannels(audioconfig, channels);
		output_port = alOpenPort("rdpsnd", "w", audioconfig);

		if (output_port == (ALport) 0)
		{
			fprintf(stderr, "wave_out_set_format: alOpenPort failed: %s\n",
				alGetErrorString(oserror()));
			return False;
		}

	}

	resource = alGetResource(output_port);
	maxFillable = alGetFillable(output_port);
	channelCount = alGetChannels(audioconfig);
	frameSize = alGetWidth(audioconfig);

	if (frameSize == 0 || channelCount == 0)
	{
		fprintf(stderr, "wave_out_set_format: bad frameSize or channelCount\n");
		return False;
	}
	combinedFrameSize = frameSize * channelCount;

	params.param = AL_RATE;
	params.value.ll = (long long) g_snd_rate << 32;

	if (alSetParams(resource, &params, 1) < 0)
	{
		fprintf(stderr, "wave_set_format: alSetParams failed: %s\n",
			alGetErrorString(oserror()));
		return False;
	}
	if (params.sizeOut < 0)
	{
		fprintf(stderr, "wave_set_format: invalid rate %d\n", g_snd_rate);
		return False;
	}

#if (defined(IRIX_DEBUG))
	fprintf(stderr, "wave_out_set_format: returning...\n");
#endif
	return True;
}