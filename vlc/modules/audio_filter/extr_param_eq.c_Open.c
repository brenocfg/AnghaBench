#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {unsigned int i_rate; int i_channels; int /*<<< orphan*/  i_format; } ;
struct TYPE_9__ {TYPE_2__ audio; } ;
struct TYPE_7__ {TYPE_2__ audio; } ;
struct TYPE_10__ {TYPE_3__ fmt_in; int /*<<< orphan*/  pf_audio_filter; TYPE_1__ fmt_out; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_11__ {float* p_state; scalar_t__ coeffs; void* f_highgain; void* f_highf; void* f_lowgain; void* f_lowf; void* f_gain3; void* f_Q3; void* f_f3; void* f_gain2; void* f_Q2; void* f_f2; void* f_gain1; void* f_Q1; void* f_f1; } ;
typedef  TYPE_5__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CalcPeakEQCoeffs (void*,void*,void*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  CalcShelfEQCoeffs (void*,int,void*,int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  DoWork ; 
 int /*<<< orphan*/  VLC_CODEC_FL32 ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_5__* malloc (int) ; 
 void* var_InheritFloat (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    filter_t     *p_filter = (filter_t *)p_this;
    unsigned     i_samplerate;

    /* Allocate structure */
    filter_sys_t *p_sys = p_filter->p_sys = malloc( sizeof( *p_sys ) );
    if( !p_sys )
        return VLC_EGENERIC;

    p_filter->fmt_in.audio.i_format = VLC_CODEC_FL32;
    p_filter->fmt_out.audio = p_filter->fmt_in.audio;
    p_filter->pf_audio_filter = DoWork;

    p_sys->f_lowf = var_InheritFloat( p_this, "param-eq-lowf");
    p_sys->f_lowgain = var_InheritFloat( p_this, "param-eq-lowgain");
    p_sys->f_highf = var_InheritFloat( p_this, "param-eq-highf");
    p_sys->f_highgain = var_InheritFloat( p_this, "param-eq-highgain");
 
    p_sys->f_f1 = var_InheritFloat( p_this, "param-eq-f1");
    p_sys->f_Q1 = var_InheritFloat( p_this, "param-eq-q1");
    p_sys->f_gain1 = var_InheritFloat( p_this, "param-eq-gain1");
 
    p_sys->f_f2 = var_InheritFloat( p_this, "param-eq-f2");
    p_sys->f_Q2 = var_InheritFloat( p_this, "param-eq-q2");
    p_sys->f_gain2 = var_InheritFloat( p_this, "param-eq-gain2");

    p_sys->f_f3 = var_InheritFloat( p_this, "param-eq-f3");
    p_sys->f_Q3 = var_InheritFloat( p_this, "param-eq-q3");
    p_sys->f_gain3 = var_InheritFloat( p_this, "param-eq-gain3");
 

    i_samplerate = p_filter->fmt_in.audio.i_rate;
    CalcPeakEQCoeffs(p_sys->f_f1, p_sys->f_Q1, p_sys->f_gain1,
                     i_samplerate, p_sys->coeffs+0*5);
    CalcPeakEQCoeffs(p_sys->f_f2, p_sys->f_Q2, p_sys->f_gain2,
                     i_samplerate, p_sys->coeffs+1*5);
    CalcPeakEQCoeffs(p_sys->f_f3, p_sys->f_Q3, p_sys->f_gain3,
                     i_samplerate, p_sys->coeffs+2*5);
    CalcShelfEQCoeffs(p_sys->f_lowf, 1, p_sys->f_lowgain, 0,
                      i_samplerate, p_sys->coeffs+3*5);
    CalcShelfEQCoeffs(p_sys->f_highf, 1, p_sys->f_highgain, 0,
                      i_samplerate, p_sys->coeffs+4*5);
    p_sys->p_state = (float*)calloc( p_filter->fmt_in.audio.i_channels*5*4,
                                     sizeof(float) );

    return VLC_SUCCESS;
}