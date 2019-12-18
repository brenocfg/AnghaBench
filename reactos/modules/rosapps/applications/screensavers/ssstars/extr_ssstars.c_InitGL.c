#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ bFinePerspective; scalar_t__ bEnableFiltering; scalar_t__ bSmoothShading; } ;
struct TYPE_6__ {float x1; float y1; float x2; float y2; float z; } ;
struct TYPE_5__ {int /*<<< orphan*/  bmBits; int /*<<< orphan*/  bmHeight; int /*<<< orphan*/  bmWidth; } ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  TYPE_1__ BITMAP ;

/* Variables and functions */
 float FAR_PLANE ; 
 float FIELD_DEPTH ; 
 float FIELD_HEIGHT ; 
 float FIELD_WIDTH ; 
 int /*<<< orphan*/  GL_AMBIENT_AND_DIFFUSE ; 
 int /*<<< orphan*/  GL_BLEND ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_COLOR_MATERIAL ; 
 int /*<<< orphan*/  GL_CONSTANT_ATTENUATION ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_FASTEST ; 
 int /*<<< orphan*/  GL_FILL ; 
 int /*<<< orphan*/  GL_FLAT ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  GL_FRONT_AND_BACK ; 
 int /*<<< orphan*/  GL_LIGHT0 ; 
 int /*<<< orphan*/  GL_LIGHTING ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_LINEAR_ATTENUATION ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_NICEST ; 
 int /*<<< orphan*/  GL_PERSPECTIVE_CORRECTION_HINT ; 
 int /*<<< orphan*/  GL_QUADRATIC_ATTENUATION ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_SMOOTH ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  GetObject (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 unsigned int MAX_STARS ; 
 float RAND_MAX ; 
 int /*<<< orphan*/  STAR_BLUE ; 
 int /*<<< orphan*/  STAR_GREEN ; 
 int /*<<< orphan*/  STAR_RED ; 
 int /*<<< orphan*/  STAR_TAIL ; 
 TYPE_3__ Settings ; 
 TYPE_2__* Vertex ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glColorMaterial (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDisable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLightModeli (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glLightf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  glPolygonMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glShadeModel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glStarTex ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gluBuild2DMipmaps (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void InitGL(HBITMAP hStarTex)
{
    BITMAP       bm;
    unsigned int i;
    float        xp, yp, zp;

    // set the GL clear color - use when the color buffer is cleared
    glClearColor(STAR_RED, STAR_GREEN, STAR_BLUE, STAR_TAIL);

    if (Settings.bSmoothShading)
        // set the shading model to 'smooth'
        glShadeModel( GL_SMOOTH );
    else
        // set the shading model to 'flat'
        glShadeModel( GL_FLAT );

    // set GL to render front of polygons
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    // enable depth test
    glDisable( GL_DEPTH_TEST );

    // enable lighting
    glEnable( GL_LIGHTING );
    // enable lighting for front
    glLightModeli( GL_FRONT, GL_TRUE );
    // material have diffuse and ambient lighting 
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
    // enable color
    glEnable( GL_COLOR_MATERIAL );
    // enable light 0
    glEnable( GL_LIGHT0 );

    // set light attenuation
    glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION,  0.01f); //0.01f );
    glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION,    0.01f); //0.2f );
    glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.005f); //0.001f );

    // clear the color buffer once
    glClear( GL_COLOR_BUFFER_BIT );

    // randomly generate
    srand( time( NULL ) );

    // Initialize *ALL* stars vertexes (not just programmed ones).
    for (i = 0; i < MAX_STARS; i++)
    {
        xp = ( (float) rand() / RAND_MAX - .5f ) * FIELD_WIDTH;
        yp = ( (float) rand() / RAND_MAX - .5f ) * FIELD_HEIGHT;
        zp = ( (float) rand() / RAND_MAX       ) * FIELD_DEPTH + FAR_PLANE;

        Vertex[i].x1 = -1.f + xp;
        Vertex[i].y1 = -1.f + yp;
        Vertex[i].x2 =  1.f + xp;
        Vertex[i].y2 =  1.f + yp;
        Vertex[i].z  = zp;
    }

    glGenTextures(1, &glStarTex);           // Create One Texture

    // Create Linear Filtered Texture
    glBindTexture(GL_TEXTURE_2D, glStarTex);

    if (Settings.bEnableFiltering)
    {
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    } else {
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    }

    // Get Texture properties
    GetObject(hStarTex, sizeof(BITMAP), &bm);

    // Create texture as a mipmap
#if 0
    glTexImage2D(GL_TEXTURE_2D, 0, 4, bm.bmWidth, bm.bmHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bm.bmBits);
#else
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, bm.bmWidth, bm.bmHeight, GL_RGBA, GL_UNSIGNED_BYTE, bm.bmBits);
#endif

    // Disable Texture Mapping (background smoothing)
    glDisable(GL_TEXTURE_2D);

    if (Settings.bFinePerspective)
        // Really Fast Perspective Calculations
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    else
        // Really Nice Perspective Calculations
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // enable blending
    glEnable( GL_BLEND );
}