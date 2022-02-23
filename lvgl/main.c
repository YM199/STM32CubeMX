#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include "lvgl.h"
#include "fbdev.h"
#include "evdev.h"
#include "gui.h"

#define DISP_HOR_RES 800
#define DISP_VER_RES 480

#define MY_DISP_HOR_RES 800
#define MY_DISP_VER_RES 480

pthread_mutex_t mutex;

static void *thread_tick_inc( void *arg )
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        lv_tick_inc(5);
        pthread_mutex_unlock(&mutex);
        usleep(5000);
    }
    return NULL;
}

int main(void)
{
    int ret;

    lv_init();

    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf1[DISP_HOR_RES * DISP_VER_RES / 10];                        /*Declare a buffer for 1/10 screen size*/
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, MY_DISP_HOR_RES * MY_DISP_VER_RES / 10);  /*Initialize the display buffer.*/

    fbdev_init();
    lv_disp_drv_t disp_drv;               /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);          /*Basic initialization*/
    disp_drv.flush_cb = fbdev_flush;    /*Set your driver function*/
    disp_drv.draw_buf = &draw_buf;          /*Assign the buffer to the display*/
    disp_drv.hor_res = MY_DISP_HOR_RES;   /*Set the horizontal resolution of the display*/
    disp_drv.ver_res = MY_DISP_VER_RES;   /*Set the verizontal resolution of the display*/
    lv_disp_drv_register(&disp_drv);      /*Finally register the driver*/

    evdev_init();
    lv_indev_drv_t indev_drv;                  /*Descriptor of a input device driver*/
    lv_indev_drv_init(&indev_drv);             /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
    indev_drv.read_cb = evdev_read;      /*Set your driver function*/
    lv_indev_drv_register(&indev_drv);         /*Finally register the driver*/

    pthread_t tid;

    ret = pthread_create( &tid, NULL, thread_tick_inc, NULL );
    if(ret != 0)
    {
        printf("error\n");
    }
    gui();
    while (1)
    {
        pthread_mutex_lock(&mutex);
        lv_task_handler();
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}
