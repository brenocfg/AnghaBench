#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int time_t ;
struct toxav_thread_data {scalar_t__ state; int sig; int /*<<< orphan*/ * BobAV; int /*<<< orphan*/ * AliceAV; int /*<<< orphan*/  incoming; void* arb; int /*<<< orphan*/  arb_mutex; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct PaStreamParameters {long device; int channelCount; int /*<<< orphan*/ * hostApiSpecificStreamInfo; int /*<<< orphan*/  suggestedLatency; int /*<<< orphan*/  sampleFormat; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int int64_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  ToxAV ;
typedef  int /*<<< orphan*/  Tox ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  defaultHighOutputLatency; } ;
struct TYPE_5__ {int frames; int samplerate; int channels; } ;
typedef  int /*<<< orphan*/  TOXAV_ERR_SEND_FRAME ;
typedef  int TOXAV_ERR_CALL_CONTROL ;
typedef  int TOXAV_ERR_CALL ;
typedef  int TOXAV_ERR_ANSWER ;
typedef  int /*<<< orphan*/  SNDFILE ;
typedef  TYPE_1__ SF_INFO ;
typedef  scalar_t__ PaError ;
typedef  TYPE_2__ PaDeviceInfo ;
typedef  int /*<<< orphan*/  IplImage ;
typedef  int /*<<< orphan*/  CvCapture ;
typedef  struct toxav_thread_data CallControl ;

/* Variables and functions */
 long Pa_GetDefaultOutputDevice () ; 
 TYPE_2__* Pa_GetDeviceInfo (long) ; 
 int /*<<< orphan*/  Pa_Initialize () ; 
 scalar_t__ Pa_OpenStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct PaStreamParameters*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ Pa_StartStream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pa_StopStream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pa_Terminate () ; 
 int /*<<< orphan*/  SFM_READ ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_TRANSFER_A ; 
 scalar_t__ TEST_TRANSFER_V ; 
 int /*<<< orphan*/  TOXAV_CALL_CONTROL_CANCEL ; 
 int TOXAV_ERR_ANSWER_OK ; 
 int TOXAV_ERR_CALL_CONTROL_OK ; 
 int TOXAV_ERR_CALL_OK ; 
 scalar_t__ TOXAV_FRIEND_CALL_STATE_FINISHED ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  adout ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  c_sleep (int) ; 
 scalar_t__ current_time_monotonic () ; 
 int /*<<< orphan*/ * cvCreateFileCapture (char const*) ; 
 int /*<<< orphan*/ * cvQueryFrame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvReleaseCapture (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,long) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  initialize_tox (int /*<<< orphan*/ **,int /*<<< orphan*/ **,struct toxav_thread_data*,int /*<<< orphan*/ **,struct toxav_thread_data*) ; 
 int /*<<< orphan*/  iterate_tox (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterate_toxav ; 
 int /*<<< orphan*/  memset (struct toxav_thread_data*,int /*<<< orphan*/ ,int) ; 
 char* optarg ; 
 int /*<<< orphan*/  paInt16 ; 
 scalar_t__ paNoError ; 
 int /*<<< orphan*/  paNoFlag ; 
 int /*<<< orphan*/  pa_write_thread ; 
 int print_audio_devices () ; 
 int print_help (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct toxav_thread_data*) ; 
 int /*<<< orphan*/  pthread_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_yield () ; 
 void* rb_new (int) ; 
 scalar_t__ rb_read (void*,void**) ; 
 int /*<<< orphan*/  send_opencv_img (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sf_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sf_open (char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sf_read_short (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 void* strtol (char*,char**,int) ; 
 int time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tox_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toxav_answer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int*) ; 
 int toxav_audio_send_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toxav_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  toxav_call_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * toxav_get_tox (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toxav_kill (int /*<<< orphan*/ *) ; 

int main (int argc, char **argv)
{
    freopen("/dev/zero", "w", stderr);
    Pa_Initialize();

    struct stat st;

    /* AV files for testing */
    const char *af_name = NULL;
    const char *vf_name = NULL;
    long audio_out_dev_idx = -1;

    int32_t audio_frame_duration = 20;
    int32_t video_frame_duration = 10;

    /* Parse settings */
CHECK_ARG:

    switch (getopt(argc, argv, "a:b:v:x:o:dh")) {
        case 'a':
            af_name = optarg;
            goto CHECK_ARG;

        case 'b': {
            char *d;
            audio_frame_duration = strtol(optarg, &d, 10);

            if (*d) {
                printf("Invalid value for argument: 'b'");
                exit(1);
            }

            goto CHECK_ARG;
        }

        case 'v':
            vf_name = optarg;
            goto CHECK_ARG;

        case 'x': {
            char *d;
            video_frame_duration = strtol(optarg, &d, 10);

            if (*d) {
                printf("Invalid value for argument: 'x'");
                exit(1);
            }

            goto CHECK_ARG;
        }

        case 'o': {
            char *d;
            audio_out_dev_idx = strtol(optarg, &d, 10);

            if (*d) {
                printf("Invalid value for argument: 'o'");
                exit(1);
            }

            goto CHECK_ARG;
        }

        case 'd':
            return print_audio_devices();

        case 'h':
            return print_help(argv[0]);

        case '?':
            exit(1);

        case -1:
            ;
    }

    { /* Check files */
        if (!af_name) {
            printf("Required audio input file!\n");
            exit(1);
        }

        if (!vf_name) {
            printf("Required video input file!\n");
            exit(1);
        }

        /* Check for files */
        if (stat(af_name, &st) != 0 || !S_ISREG(st.st_mode)) {
            printf("%s doesn't seem to be a regular file!\n", af_name);
            exit(1);
        }

        if (stat(vf_name, &st) != 0 || !S_ISREG(st.st_mode)) {
            printf("%s doesn't seem to be a regular file!\n", vf_name);
            exit(1);
        }
    }

    if (audio_out_dev_idx < 0)
        audio_out_dev_idx = Pa_GetDefaultOutputDevice();

    const PaDeviceInfo *audio_dev = Pa_GetDeviceInfo(audio_out_dev_idx);

    if (!audio_dev) {
        fprintf(stderr, "Device under index: %ld invalid", audio_out_dev_idx);
        return 1;
    }

    printf("Using audio device: %s\n", audio_dev->name);
    printf("Using audio file: %s\n", af_name);
    printf("Using video file: %s\n", vf_name);

    /* START TOX NETWORK */

    Tox *bootstrap;
    ToxAV *AliceAV;
    ToxAV *BobAV;

    CallControl AliceCC;
    CallControl BobCC;

    initialize_tox(&bootstrap, &AliceAV, &AliceCC, &BobAV, &BobCC);

    if (TEST_TRANSFER_A) {
        SNDFILE *af_handle;
        SF_INFO af_info;

        printf("\nTrying audio enc/dec...\n");

        memset(&AliceCC, 0, sizeof(CallControl));
        memset(&BobCC, 0, sizeof(CallControl));

        pthread_mutex_init(AliceCC.arb_mutex, NULL);
        pthread_mutex_init(BobCC.arb_mutex, NULL);

        AliceCC.arb = rb_new(16);
        BobCC.arb = rb_new(16);

        { /* Call */
            TOXAV_ERR_CALL rc;
            toxav_call(AliceAV, 0, 48, 0, &rc);

            if (rc != TOXAV_ERR_CALL_OK) {
                printf("toxav_call failed: %d\n", rc);
                exit(1);
            }
        }

        while (!BobCC.incoming)
            iterate_tox(bootstrap, AliceAV, BobAV);

        { /* Answer */
            TOXAV_ERR_ANSWER rc;
            toxav_answer(BobAV, 0, 48, 0, &rc);

            if (rc != TOXAV_ERR_ANSWER_OK) {
                printf("toxav_answer failed: %d\n", rc);
                exit(1);
            }
        }

        while (AliceCC.state == 0)
            iterate_tox(bootstrap, AliceAV, BobAV);

        /* Open audio file */
        af_handle = sf_open(af_name, SFM_READ, &af_info);

        if (af_handle == NULL) {
            printf("Failed to open the file.\n");
            exit(1);
        }

        int16_t PCM[5760];

        time_t start_time = time(NULL);
        time_t expected_time = af_info.frames / af_info.samplerate + 2;


        /* Start decode thread */
        struct toxav_thread_data data = {
            .AliceAV = AliceAV,
            .BobAV = BobAV,
            .sig = 0
        };

        pthread_t dect;
        pthread_create(&dect, NULL, iterate_toxav, &data);
        pthread_detach(dect);

        int frame_size = (af_info.samplerate * audio_frame_duration / 1000) * af_info.channels;

        struct PaStreamParameters output;
        output.device = audio_out_dev_idx;
        output.channelCount = af_info.channels;
        output.sampleFormat = paInt16;
        output.suggestedLatency = audio_dev->defaultHighOutputLatency;
        output.hostApiSpecificStreamInfo = NULL;

        PaError err = Pa_OpenStream(&adout, NULL, &output, af_info.samplerate, frame_size, paNoFlag, NULL, NULL);
        assert(err == paNoError);

        err = Pa_StartStream(adout);
        assert(err == paNoError);

//         toxav_audio_bit_rate_set(AliceAV, 0, 64, false, NULL);

        /* Start write thread */
        pthread_t t;
        pthread_create(&t, NULL, pa_write_thread, &BobCC);
        pthread_detach(t);

        printf("Sample rate %d\n", af_info.samplerate);

        while (start_time + expected_time > time(NULL) ) {
            uint64_t enc_start_time = current_time_monotonic();
            int64_t count = sf_read_short(af_handle, PCM, frame_size);

            if (count > 0) {
                TOXAV_ERR_SEND_FRAME rc;

                if (toxav_audio_send_frame(AliceAV, 0, PCM, count / af_info.channels, af_info.channels, af_info.samplerate,
                                           &rc) == false) {
                    printf("Error sending frame of size %ld: %d\n", count, rc);
                }
            }

            iterate_tox(bootstrap, AliceAV, BobAV);
            c_sleep(abs(audio_frame_duration - (current_time_monotonic() - enc_start_time) - 1));
        }

        printf("Played file in: %lu; stopping stream...\n", time(NULL) - start_time);

        Pa_StopStream(adout);
        sf_close(af_handle);

        { /* Hangup */
            TOXAV_ERR_CALL_CONTROL rc;
            toxav_call_control(AliceAV, 0, TOXAV_CALL_CONTROL_CANCEL, &rc);

            if (rc != TOXAV_ERR_CALL_CONTROL_OK) {
                printf("toxav_call_control failed: %d\n", rc);
                exit(1);
            }
        }

        iterate_tox(bootstrap, AliceAV, BobAV);
        assert(BobCC.state == TOXAV_FRIEND_CALL_STATE_FINISHED);

        /* Stop decode thread */
        data.sig = -1;

        while (data.sig != 1)
            pthread_yield();

        pthread_mutex_destroy(AliceCC.arb_mutex);
        pthread_mutex_destroy(BobCC.arb_mutex);

        void *f = NULL;

        while (rb_read(AliceCC.arb, &f))
            free(f);

        while (rb_read(BobCC.arb, &f))
            free(f);

        printf("Success!");
    }

    if (TEST_TRANSFER_V) {
        printf("\nTrying video enc/dec...\n");

        memset(&AliceCC, 0, sizeof(CallControl));
        memset(&BobCC, 0, sizeof(CallControl));

        { /* Call */
            TOXAV_ERR_CALL rc;
            toxav_call(AliceAV, 0, 0, 2000, &rc);

            if (rc != TOXAV_ERR_CALL_OK) {
                printf("toxav_call failed: %d\n", rc);
                exit(1);
            }
        }

        while (!BobCC.incoming)
            iterate_tox(bootstrap, AliceAV, BobAV);

        { /* Answer */
            TOXAV_ERR_ANSWER rc;
            toxav_answer(BobAV, 0, 0, 5000, &rc);

            if (rc != TOXAV_ERR_ANSWER_OK) {
                printf("toxav_answer failed: %d\n", rc);
                exit(1);
            }
        }

        iterate_tox(bootstrap, AliceAV, BobAV);

        /* Start decode thread */
        struct toxav_thread_data data = {
            .AliceAV = AliceAV,
            .BobAV = BobAV,
            .sig = 0
        };

        pthread_t dect;
        pthread_create(&dect, NULL, iterate_toxav, &data);
        pthread_detach(dect);

        CvCapture *capture = cvCreateFileCapture(vf_name);

        if (!capture) {
            printf("Failed to open video file: %s\n", vf_name);
            exit(1);
        }

//         toxav_video_bit_rate_set(AliceAV, 0, 5000, false, NULL);

        time_t start_time = time(NULL);

        while (start_time + 90 > time(NULL)) {
            IplImage *frame = cvQueryFrame(capture );

            if (!frame)
                break;

            send_opencv_img(AliceAV, 0, frame);
            iterate_tox(bootstrap, AliceAV, BobAV);
            c_sleep(10);
        }

        cvReleaseCapture(&capture);

        { /* Hangup */
            TOXAV_ERR_CALL_CONTROL rc;
            toxav_call_control(AliceAV, 0, TOXAV_CALL_CONTROL_CANCEL, &rc);

            if (rc != TOXAV_ERR_CALL_CONTROL_OK) {
                printf("toxav_call_control failed: %d\n", rc);
                exit(1);
            }
        }

        iterate_tox(bootstrap, AliceAV, BobAV);
        assert(BobCC.state == TOXAV_FRIEND_CALL_STATE_FINISHED);

        /* Stop decode thread */
        printf("Stopping decode thread\n");
        data.sig = -1;

        while (data.sig != 1)
            pthread_yield();

        printf("Success!");
    }


    Tox *Alice = toxav_get_tox(AliceAV);
    Tox *Bob = toxav_get_tox(BobAV);
    toxav_kill(BobAV);
    toxav_kill(AliceAV);
    tox_kill(Bob);
    tox_kill(Alice);
    tox_kill(bootstrap);

    printf("\nTest successful!\n");

    Pa_Terminate();
    return 0;
}