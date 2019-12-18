#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jobject ;
typedef  int /*<<< orphan*/  jfloatArray ;
typedef  int /*<<< orphan*/  fz_matrix ;
struct TYPE_11__ {int /*<<< orphan*/  self; TYPE_2__** env; } ;
typedef  TYPE_1__ fz_java_device ;
typedef  int /*<<< orphan*/  fz_image ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_colorspace ;
typedef  int /*<<< orphan*/  fz_color_params ;
struct TYPE_12__ {scalar_t__ (* ExceptionCheck ) (TYPE_2__**) ;int /*<<< orphan*/  (* CallVoidMethod ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int) ;} ;
typedef  TYPE_2__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_MAX_COLORS ; 
 int /*<<< orphan*/  fz_colorspace_n (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw_java (int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  mid_Device_fillImageMask ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float,int) ; 
 scalar_t__ stub2 (TYPE_2__**) ; 
 int to_ColorParams_safe (int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_ColorSpace (int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_Image (int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_Matrix (int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_jfloatArray (int /*<<< orphan*/ *,TYPE_2__**,float const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fz_java_device_fill_image_mask(fz_context *ctx, fz_device *dev, fz_image *img, fz_matrix ctm, fz_colorspace *cs, const float *color, float alpha, fz_color_params cs_params)
{
	fz_java_device *jdev = (fz_java_device *)dev;
	JNIEnv *env = jdev->env;
	jobject jimg = to_Image(ctx, env, img);
	jobject jctm = to_Matrix(ctx, env, ctm);
	jobject jcs = to_ColorSpace(ctx, env, cs);
	jfloatArray jcolor = to_jfloatArray(ctx, env, color, cs ? fz_colorspace_n(ctx, cs) : FZ_MAX_COLORS);
	int jcp = to_ColorParams_safe(ctx, env, cs_params);

	(*env)->CallVoidMethod(env, jdev->self, mid_Device_fillImageMask, jimg, jctm, jcs, jcolor, alpha, jcp);
	if ((*env)->ExceptionCheck(env))
		fz_throw_java(ctx, env);
}