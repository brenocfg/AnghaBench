#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  Texture ;
struct TYPE_3__ {int /*<<< orphan*/  bmBits; int /*<<< orphan*/  bmHeight; int /*<<< orphan*/  bmWidth; } ;
typedef  scalar_t__ HBITMAP ;
typedef  int /*<<< orphan*/  BMP ;
typedef  TYPE_1__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  GL_BGR_EXT ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_LINEAR_MIPMAP_LINEAR ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  GetModuleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetObject (scalar_t__,int,TYPE_1__*) ; 
 int /*<<< orphan*/  IDB_BUTTERFLY1 ; 
 int /*<<< orphan*/  IDB_BUTTERFLY2 ; 
 int /*<<< orphan*/  IDB_BUTTERFLY3 ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 int /*<<< orphan*/  LR_CREATEDIBSECTION ; 
 scalar_t__ LoadImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glPixelStorei (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gluBuild2DMipmaps (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * texture ; 

void LoadGLTextures()											// Creates Textures From Bitmaps In The Resource File
{
	HBITMAP hBMP;												// Handle Of The Bitmap
	BITMAP	BMP;												// Bitmap Structure
    int loop;

	// The ID Of The 3 Bitmap Images We Want To Load From The Resource File
	byte	Texture[]={	IDB_BUTTERFLY1,	IDB_BUTTERFLY2,	IDB_BUTTERFLY3 };

	glGenTextures(sizeof(Texture), &texture[0]);				// Generate 3 Textures (sizeof(Texture)=3 ID's)
	for (loop=0; loop<sizeof(Texture); loop++)				// Loop Through All The ID's (Bitmap Images)
	{
		hBMP=(HBITMAP)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(Texture[loop]), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
		if (hBMP)												// Does The Bitmap Exist?
		{														// If So...
			GetObject(hBMP,sizeof(BMP), &BMP);					// Get The Object
																// hBMP: Handle To Graphics Object
																// sizeof(BMP): Size Of Buffer For Object Information
																// Buffer For Object Information
			glPixelStorei(GL_UNPACK_ALIGNMENT,4);				// Pixel Storage Mode (Word Alignment / 4 Bytes)
			glBindTexture(GL_TEXTURE_2D, texture[loop]);		// Bind Our Texture
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR); // Mipmap Linear Filtering

			// Generate Mipmapped Texture (3 Bytes, Width, Height And Data From The BMP)
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, BMP.bmWidth, BMP.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
		}
	}
}