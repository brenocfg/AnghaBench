#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_16__ ;
typedef  struct TYPE_18__   TYPE_12__ ;

/* Type definitions */
typedef  int dwOutsideConeAngle ;
struct TYPE_25__ {scalar_t__ x; scalar_t__ y; scalar_t__ z; } ;
struct TYPE_18__ {int lVolume; int lPan; } ;
struct TYPE_19__ {scalar_t__ x; scalar_t__ y; scalar_t__ z; } ;
struct TYPE_21__ {int dwMode; int flMaxDistance; int flMinDistance; int dwInsideConeAngle; int dwOutsideConeAngle; int lConeOutsideVolume; TYPE_6__ vPosition; TYPE_16__ vConeOrientation; } ;
struct TYPE_20__ {int dwFlags; } ;
struct TYPE_24__ {int ds3db_lVolume; TYPE_12__ volpan; TYPE_4__* device; TYPE_2__ ds3db_ds3db; TYPE_1__ dsbd; } ;
struct TYPE_22__ {int /*<<< orphan*/  vOrientTop; int /*<<< orphan*/  vOrientFront; TYPE_6__ vPosition; } ;
struct TYPE_23__ {TYPE_3__ ds3dl; } ;
typedef  TYPE_5__ IDirectSoundBufferImpl ;
typedef  int DWORD ;
typedef  TYPE_6__ D3DVECTOR ;
typedef  int D3DVALUE ;

/* Variables and functions */
 int AngleBetweenVectorsDeg (TYPE_16__*,TYPE_6__*) ; 
 int AngleBetweenVectorsRad (TYPE_6__*,TYPE_6__*) ; 
#define  DS3DMODE_DISABLE 130 
#define  DS3DMODE_HEADRELATIVE 129 
#define  DS3DMODE_NORMAL 128 
 int DSBCAPS_MUTE3DATMAXDISTANCE ; 
 int DSBVOLUME_MIN ; 
 int /*<<< orphan*/  DSOUND_RecalcVolPan (TYPE_12__*) ; 
 int M_PI ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 TYPE_6__ VectorBetweenTwoPoints (TYPE_6__*,TYPE_6__*) ; 
 int VectorMagnitude (TYPE_6__*) ; 
 TYPE_6__ VectorProduct (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int log10 (int) ; 

void DSOUND_Calc3DBuffer(IDirectSoundBufferImpl *dsb)
{
	/* volume, at which the sound will be played after all calcs. */
	D3DVALUE lVolume = 0;
	/* stuff for distance related stuff calc. */
	D3DVECTOR vDistance;
	D3DVALUE flDistance = 0;
	/* panning related stuff */
	D3DVALUE flAngle;
	D3DVECTOR vLeft;
	/* doppler shift related stuff */
#if 0
	D3DVALUE flFreq, flBufferVel, flListenerVel;
#endif

	TRACE("(%p)\n",dsb);

	/* initial buffer volume */
	lVolume = dsb->ds3db_lVolume;
	
	switch (dsb->ds3db_ds3db.dwMode)
	{
		case DS3DMODE_DISABLE:
			TRACE("3D processing disabled\n");
			/* this one is here only to eliminate annoying warning message */
			DSOUND_RecalcVolPan (&dsb->volpan);
			break;
		case DS3DMODE_NORMAL:
			TRACE("Normal 3D processing mode\n");
			/* we need to calculate distance between buffer and listener*/
			vDistance = VectorBetweenTwoPoints(&dsb->ds3db_ds3db.vPosition, &dsb->device->ds3dl.vPosition);
			flDistance = VectorMagnitude (&vDistance);
			break;
		case DS3DMODE_HEADRELATIVE:
			TRACE("Head-relative 3D processing mode\n");
			/* distance between buffer and listener is same as buffer's position */
			flDistance = VectorMagnitude (&dsb->ds3db_ds3db.vPosition);
			break;
	}
	
	if (flDistance > dsb->ds3db_ds3db.flMaxDistance)
	{
		/* some apps don't want you to hear too distant sounds... */
		if (dsb->dsbd.dwFlags & DSBCAPS_MUTE3DATMAXDISTANCE)
		{
			dsb->volpan.lVolume = DSBVOLUME_MIN;
			DSOUND_RecalcVolPan (&dsb->volpan);		
			/* i guess mixing here would be a waste of power */
			return;
		}
		else
			flDistance = dsb->ds3db_ds3db.flMaxDistance;
	}		

	if (flDistance < dsb->ds3db_ds3db.flMinDistance)
		flDistance = dsb->ds3db_ds3db.flMinDistance;
	
	/* attenuation proportional to the distance squared, converted to millibels as in lVolume*/
	lVolume -= log10(flDistance/dsb->ds3db_ds3db.flMinDistance * flDistance/dsb->ds3db_ds3db.flMinDistance)*1000;
	TRACE("dist. att: Distance = %f, MinDistance = %f => adjusting volume %d to %f\n", flDistance, dsb->ds3db_ds3db.flMinDistance, dsb->ds3db_lVolume, lVolume);

	/* conning */
	/* sometimes it happens that vConeOrientation vector = (0,0,0); in this case angle is "nan" and it's useless*/
	if (dsb->ds3db_ds3db.vConeOrientation.x == 0 && dsb->ds3db_ds3db.vConeOrientation.y == 0 && dsb->ds3db_ds3db.vConeOrientation.z == 0)
	{
		TRACE("conning: cones not set\n");
	}
	else
	{
		/* calculate angle */
		flAngle = AngleBetweenVectorsDeg(&dsb->ds3db_ds3db.vConeOrientation, &vDistance);
		/* if by any chance it happens that OutsideConeAngle = InsideConeAngle (that means that conning has no effect) */
		if (dsb->ds3db_ds3db.dwInsideConeAngle != dsb->ds3db_ds3db.dwOutsideConeAngle)
		{
			/* my test show that for my way of calc., we need only half of angles */
			DWORD dwInsideConeAngle = dsb->ds3db_ds3db.dwInsideConeAngle/2;
			DWORD dwOutsideConeAngle = dsb->ds3db_ds3db.dwOutsideConeAngle/2;
			if (dwOutsideConeAngle == dwInsideConeAngle)
				++dwOutsideConeAngle;

			/* full volume */
			if (flAngle < dwInsideConeAngle)
				flAngle = dwInsideConeAngle;
			/* min (app defined) volume */
			if (flAngle > dwOutsideConeAngle)
				flAngle = dwOutsideConeAngle;
			/* this probably isn't the right thing, but it's ok for the time being */
			lVolume += ((dsb->ds3db_ds3db.lConeOutsideVolume)/((dwOutsideConeAngle) - (dwInsideConeAngle))) * flAngle;
		}
		TRACE("conning: Angle = %f deg; InsideConeAngle(/2) = %d deg; OutsideConeAngle(/2) = %d deg; ConeOutsideVolume = %d => adjusting volume to %f\n",
		       flAngle, dsb->ds3db_ds3db.dwInsideConeAngle/2, dsb->ds3db_ds3db.dwOutsideConeAngle/2, dsb->ds3db_ds3db.lConeOutsideVolume, lVolume);
	}
	dsb->volpan.lVolume = lVolume;
	
	/* panning */
	if (dsb->device->ds3dl.vPosition.x == dsb->ds3db_ds3db.vPosition.x &&
	    dsb->device->ds3dl.vPosition.y == dsb->ds3db_ds3db.vPosition.y &&
	    dsb->device->ds3dl.vPosition.z == dsb->ds3db_ds3db.vPosition.z) {
		dsb->volpan.lPan = 0;
		flAngle = 0.0;
	}
	else
	{
		vDistance = VectorBetweenTwoPoints(&dsb->device->ds3dl.vPosition, &dsb->ds3db_ds3db.vPosition);
		vLeft = VectorProduct(&dsb->device->ds3dl.vOrientFront, &dsb->device->ds3dl.vOrientTop);
		flAngle = AngleBetweenVectorsRad(&vLeft, &vDistance);
		/* for now, we'll use "linear formula" (which is probably incorrect); if someone has it in book, correct it */
		dsb->volpan.lPan = 10000*2*flAngle/M_PI - 10000;
	}
	TRACE("panning: Angle = %f rad, lPan = %d\n", flAngle, dsb->volpan.lPan);

	/* FIXME: Doppler Effect disabled since i have no idea which frequency to change and how to do it */
#if 0	
	/* doppler shift*/
	if ((VectorMagnitude(&ds3db_ds3db.vVelocity) == 0) && (VectorMagnitude(&dsb->device->ds3dl.vVelocity) == 0))
	{
		TRACE("doppler: Buffer and Listener don't have velocities\n");
	}
	else if (ds3db_ds3db.vVelocity != dsb->device->ds3dl.vVelocity)
	{
		/* calculate length of ds3db_ds3db.vVelocity component which causes Doppler Effect
		   NOTE: if buffer moves TOWARDS the listener, it's velocity component is NEGATIVE
		         if buffer moves AWAY from listener, it's velocity component is POSITIVE */
		flBufferVel = ProjectVector(&dsb->ds3db_ds3db.vVelocity, &vDistance);
		/* calculate length of ds3dl.vVelocity component which causes Doppler Effect
		   NOTE: if listener moves TOWARDS the buffer, it's velocity component is POSITIVE
		         if listener moves AWAY from buffer, it's velocity component is NEGATIVE */
		flListenerVel = ProjectVector(&dsb->device->ds3dl.vVelocity, &vDistance);
		/* formula taken from Gianicoli D.: Physics, 4th edition: */
		/* FIXME: replace dsb->freq with appropriate frequency ! */
		flFreq = dsb->freq * ((DEFAULT_VELOCITY + flListenerVel)/(DEFAULT_VELOCITY + flBufferVel));
		TRACE("doppler: Buffer velocity (component) = %lf, Listener velocity (component) = %lf => Doppler shift: %ld Hz -> %lf Hz\n", flBufferVel, flListenerVel,
		      dsb->freq, flFreq);
		/* FIXME: replace following line with correct frequency setting ! */
		dsb->freq = flFreq;
		DSOUND_RecalcFormat(dsb);
		DSOUND_MixToTemporary(dsb, 0, dsb->buflen);
	}
#endif	
	
	/* time for remix */
	DSOUND_RecalcVolPan(&dsb->volpan);
}