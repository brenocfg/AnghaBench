#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct vertex_buffer {size_t Free; int /*<<< orphan*/ * Edgeflag; int /*<<< orphan*/  Clip; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* ClipInterpAuxFunc ) (TYPE_1__*,int /*<<< orphan*/ ,size_t,double,int,int) ;scalar_t__ ClipMask; struct vertex_buffer* VB; } ;
typedef  int GLuint ;
typedef  double GLdouble ;
typedef  TYPE_1__ GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_SPACE ; 
 int /*<<< orphan*/ * GLfloat (double*) ; 
 int VB_SIZE ; 
 double** coord ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,size_t,double,int,int) ; 
 int /*<<< orphan*/  stub10 (TYPE_1__*,int /*<<< orphan*/ ,size_t,double,int,int) ; 
 int /*<<< orphan*/  stub11 (TYPE_1__*,int /*<<< orphan*/ ,size_t,double,int,int) ; 
 int /*<<< orphan*/  stub12 (TYPE_1__*,int /*<<< orphan*/ ,size_t,double,int,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,size_t,double,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,size_t,double,int,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__*,int /*<<< orphan*/ ,size_t,double,int,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__*,int /*<<< orphan*/ ,size_t,double,int,int) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__*,int /*<<< orphan*/ ,size_t,double,int,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__*,int /*<<< orphan*/ ,size_t,double,int,int) ; 
 int /*<<< orphan*/  stub8 (TYPE_1__*,int /*<<< orphan*/ ,size_t,double,int,int) ; 
 int /*<<< orphan*/  stub9 (TYPE_1__*,int /*<<< orphan*/ ,size_t,double,int,int) ; 

GLuint gl_viewclip_polygon( GLcontext* ctx, GLuint n, GLuint vlist[] )

{
   struct vertex_buffer* VB = ctx->VB;
   GLfloat (*coord)[4] = VB->Clip;

   GLuint previ, prevj;
   GLuint curri, currj;
   GLuint vlist2[VB_SIZE];
   GLuint n2;
   GLdouble dx, dy, dz, dw, t, neww;

/*
 * We use 6 instances of this code to implement clipping against the
 * 6 sides of the view volume.  Prior to each we define the macros:
 *    INLIST = array which lists input vertices
 *    OUTLIST = array which lists output vertices
 *    INCOUNT = variable which is the number of vertices in INLIST[]
 *    OUTCOUNT = variable which is the number of vertices in OUTLIST[]
 *    INSIDE(i) = test if vertex v[i] is inside the view volume
 *    COMPUTE_INTERSECTION(in,out,new) = compute intersection of line
 *              from v[in] to v[out] with the clipping plane and store
 *              the result in v[new]
 */

#define GENERAL_CLIP                                                    \
   if (INCOUNT<3)  return 0;						\
   previ = INCOUNT-1;		/* let previous = last vertex */	\
   prevj = INLIST[previ];						\
   OUTCOUNT = 0;                                                        \
   for (curri=0;curri<INCOUNT;curri++) {				\
      currj = INLIST[curri];						\
      if (INSIDE(currj)) {						\
         if (INSIDE(prevj)) {						\
            /* both verts are inside ==> copy current to outlist */     \
	    OUTLIST[OUTCOUNT] = currj;					\
	    OUTCOUNT++;							\
         }                                                              \
         else {                                                         \
            /* current is inside and previous is outside ==> clip */	\
	    COMPUTE_INTERSECTION( currj, prevj,	VB->Free )		\
	    /* if new point not coincident with previous point... */	\
	    if (t>0.0) {						\
	       /* interpolate aux info using the value of t */		\
	       if (ctx->ClipMask)					\
		  ctx->ClipInterpAuxFunc( ctx, CLIP_SPACE, VB->Free, t, currj, prevj ); \
	       VB->Edgeflag[VB->Free] = VB->Edgeflag[prevj];		\
	       /* output new point */					\
	       OUTLIST[OUTCOUNT] = VB->Free;				\
	       VB->Free++;						\
	       if (VB->Free==VB_SIZE)   VB->Free = 1;			\
	       OUTCOUNT++;						\
	    }								\
	    /* Output current */					\
	    OUTLIST[OUTCOUNT] = currj;					\
	    OUTCOUNT++;							\
         }                                                              \
      }                                                                 \
      else {                                                            \
         if (INSIDE(prevj)) {						\
            /* current is outside and previous is inside ==> clip */	\
	    COMPUTE_INTERSECTION( prevj, currj, VB->Free )		\
	    /* if new point not coincident with previous point... */	\
	    if (t>0.0) {						\
	       /* interpolate aux info using the value of t */		\
	       if (ctx->ClipMask)					\
		  ctx->ClipInterpAuxFunc( ctx, CLIP_SPACE, VB->Free, t, prevj, currj ); \
	       VB->Edgeflag[VB->Free] = VB->Edgeflag[prevj];		\
	       /* output new point */					\
	       OUTLIST[OUTCOUNT] = VB->Free;				\
	       VB->Free++;						\
	       if (VB->Free==VB_SIZE)   VB->Free = 1;			\
	       OUTCOUNT++;						\
	    }								\
         }								\
         /* else both verts are outside ==> do nothing */		\
      }									\
      /* let previous = current */					\
      previ = curri;							\
      prevj = currj;							\
      /* check for overflowing vertex buffer */				\
      if (OUTCOUNT>=VB_SIZE-1) {					\
	 /* Too many vertices */					\
         if (OUTLIST==vlist2) {						\
	    /* copy OUTLIST[] to vlist[] */				\
	    int i;							\
	    for (i=0;i<VB_SIZE;i++) {					\
	       vlist[i] = OUTLIST[i];					\
	    }								\
	 }								\
	 return VB_SIZE-1;						\
      }									\
   }


#define X(I)	coord[I][0]
#define Y(I)	coord[I][1]
#define Z(I)	coord[I][2]
#define W(I)	coord[I][3]

/*
 * Clip against +X
 */
#define INCOUNT n
#define OUTCOUNT n2
#define INLIST vlist
#define OUTLIST vlist2
#define INSIDE(K)      (X(K) <= W(K))

#define COMPUTE_INTERSECTION( in, out, new )		\
        dx = X(out) - X(in);				\
        dw = W(out) - W(in);				\
        t = (X(in)-W(in)) / (dw-dx);			\
	neww = W(in) + t * dw;				\
	X(new) = neww;					\
	Y(new) = Y(in) + t * (Y(out) - Y(in));		\
	Z(new) = Z(in) + t * (Z(out) - Z(in)); 		\
	W(new) = neww;

   GENERAL_CLIP

#undef INCOUNT
#undef OUTCOUNT
#undef INLIST
#undef OUTLIST
#undef INSIDE
#undef COMPUTE_INTERSECTION


/*
 * Clip against -X
 */
#define INCOUNT n2
#define OUTCOUNT n
#define INLIST vlist2
#define OUTLIST vlist
#define INSIDE(K)       (X(K) >= -W(K))
#define COMPUTE_INTERSECTION( in, out, new )		\
        dx = X(out)-X(in);                      	\
        dw = W(out)-W(in);                      	\
        t = -(X(in)+W(in)) / (dw+dx);           	\
	neww = W(in) + t * dw;				\
        X(new) = -neww;					\
        Y(new) = Y(in) + t * (Y(out) - Y(in));		\
        Z(new) = Z(in) + t * (Z(out) - Z(in));		\
        W(new) = neww;

   GENERAL_CLIP

#undef INCOUNT
#undef OUTCOUNT
#undef INLIST
#undef OUTLIST
#undef INSIDE
#undef COMPUTE_INTERSECTION


/*
 * Clip against +Y
 */
#define INCOUNT n
#define OUTCOUNT n2
#define INLIST vlist
#define OUTLIST vlist2
#define INSIDE(K)       (Y(K) <= W(K))
#define COMPUTE_INTERSECTION( in, out, new )		\
        dy = Y(out)-Y(in);                      	\
        dw = W(out)-W(in);                      	\
        t = (Y(in)-W(in)) / (dw-dy);            	\
	neww = W(in) + t * dw; 				\
        X(new) = X(in) + t * (X(out) - X(in));		\
        Y(new) = neww;					\
        Z(new) = Z(in) + t * (Z(out) - Z(in));		\
        W(new) = neww;

   GENERAL_CLIP

#undef INCOUNT
#undef OUTCOUNT
#undef INLIST
#undef OUTLIST
#undef INSIDE
#undef COMPUTE_INTERSECTION


/*
 * Clip against -Y
 */
#define INCOUNT n2
#define OUTCOUNT n
#define INLIST vlist2
#define OUTLIST vlist
#define INSIDE(K)       (Y(K) >= -W(K))
#define COMPUTE_INTERSECTION( in, out, new )		\
        dy = Y(out)-Y(in);                      	\
        dw = W(out)-W(in);                      	\
        t = -(Y(in)+W(in)) / (dw+dy);           	\
	neww = W(in) + t * dw;				\
        X(new) = X(in) + t * (X(out) - X(in));		\
        Y(new) = -neww;					\
        Z(new) = Z(in) + t * (Z(out) - Z(in));		\
        W(new) = neww;

   GENERAL_CLIP

#undef INCOUNT
#undef OUTCOUNT
#undef INLIST
#undef OUTLIST
#undef INSIDE
#undef COMPUTE_INTERSECTION



/*
 * Clip against +Z
 */
#define INCOUNT n
#define OUTCOUNT n2
#define INLIST vlist
#define OUTLIST vlist2
#define INSIDE(K)       (Z(K) <= W(K))
#define COMPUTE_INTERSECTION( in, out, new )		\
        dz = Z(out)-Z(in);                      	\
        dw = W(out)-W(in);                      	\
        t = (Z(in)-W(in)) / (dw-dz);            	\
	neww = W(in) + t * dw;				\
        X(new) = X(in) + t * (X(out) - X(in));		\
        Y(new) = Y(in) + t * (Y(out) - Y(in));		\
        Z(new) = neww;					\
        W(new) = neww;

   GENERAL_CLIP

#undef INCOUNT
#undef OUTCOUNT
#undef INLIST
#undef OUTLIST
#undef INSIDE
#undef COMPUTE_INTERSECTION


/*
 * Clip against -Z
 */
#define INCOUNT n2
#define OUTCOUNT n
#define INLIST vlist2
#define OUTLIST vlist
#define INSIDE(K)       (Z(K) >= -W(K))
#define COMPUTE_INTERSECTION( in, out, new )		\
        dz = Z(out)-Z(in);                      	\
        dw = W(out)-W(in);                      	\
        t = -(Z(in)+W(in)) / (dw+dz);           	\
	neww = W(in) + t * dw;				\
        X(new) = X(in) + t * (X(out) - X(in));		\
        Y(new) = Y(in) + t * (Y(out) - Y(in));		\
        Z(new) = -neww;					\
        W(new) = neww;

   GENERAL_CLIP

#undef INCOUNT
#undef INLIST
#undef OUTLIST
#undef INSIDE
#undef COMPUTE_INTERSECTION

   /* 'OUTCOUNT' clipped vertices are now back in v[] */
   return OUTCOUNT;

#undef GENERAL_CLIP
#undef OUTCOUNT
}