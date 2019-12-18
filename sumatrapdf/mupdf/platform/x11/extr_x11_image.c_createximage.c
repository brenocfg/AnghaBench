#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ shmid; char* shmaddr; int /*<<< orphan*/  readOnly; } ;
typedef  TYPE_1__ XShmSegmentInfo ;
struct TYPE_12__ {int bytes_per_line; int height; char* data; } ;
typedef  TYPE_2__ XImage ;
typedef  int /*<<< orphan*/  Visual ;
struct TYPE_13__ {scalar_t__ useshm; } ;
typedef  int /*<<< orphan*/  Status ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int IPC_CREAT ; 
 int /*<<< orphan*/  IPC_PRIVATE ; 
 int /*<<< orphan*/  IPC_RMID ; 
 TYPE_2__* XCreateImage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDestroyImage (TYPE_2__*) ; 
 int /*<<< orphan*/  XShmAttach (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* XShmCreateImage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  XShmQueryExtension (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XSync (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPixmap ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__ info ; 
 char* malloc (int) ; 
 char* shmat (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmctl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shmdt (char*) ; 
 scalar_t__ shmget (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static XImage *
createximage(Display *dpy, Visual *vis, XShmSegmentInfo *xsi, int depth, int w, int h)
{
	XImage *img;
	Status status;

	if (!XShmQueryExtension(dpy))
		goto fallback;
	if (!info.useshm)
		goto fallback;

	img = XShmCreateImage(dpy, vis, depth, ZPixmap, NULL, xsi, w, h);
	if (!img)
	{
		fprintf(stderr, "warn: could not XShmCreateImage\n");
		goto fallback;
	}

	xsi->shmid = shmget(IPC_PRIVATE,
		img->bytes_per_line * img->height,
		IPC_CREAT | 0777);
	if (xsi->shmid < 0)
	{
		XDestroyImage(img);
		fprintf(stderr, "warn: could not shmget\n");
		goto fallback;
	}

	img->data = xsi->shmaddr = shmat(xsi->shmid, NULL, 0);
	if (img->data == (char*)-1)
	{
		XDestroyImage(img);
		fprintf(stderr, "warn: could not shmat\n");
		goto fallback;
	}

	xsi->readOnly = False;
	status = XShmAttach(dpy, xsi);
	if (!status)
	{
		shmdt(xsi->shmaddr);
		XDestroyImage(img);
		fprintf(stderr, "warn: could not XShmAttach\n");
		goto fallback;
	}

	XSync(dpy, False);

	shmctl(xsi->shmid, IPC_RMID, NULL);

	return img;

fallback:
	info.useshm = 0;

	img = XCreateImage(dpy, vis, depth, ZPixmap, 0, NULL, w, h, 32, 0);
	if (!img)
	{
		fprintf(stderr, "fail: could not XCreateImage");
		abort();
	}

	img->data = malloc(h * img->bytes_per_line);
	if (!img->data)
	{
		fprintf(stderr, "fail: could not malloc");
		abort();
	}

	return img;
}