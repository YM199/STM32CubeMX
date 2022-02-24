#include "gui.h"


static void create_status_bar( void )
{
    lv_obj_t* status_bar = lv_obj_create( lv_layer_top() );
    lv_obj_set_size( status_bar, LV_HOR_RES, LV_VER_RES/10 ); /*设置大小*/
    lv_obj_align( status_bar, LV_ALIGN_TOP_MID, 0, 0); /*设置坐标*/

    static lv_style_t style_status_bar;
    lv_style_init( &style_status_bar );
    lv_style_set_bg_color( &style_status_bar, lv_color_hex(0x00bfff) ); /*设置背景颜色*/

    lv_obj_add_style( status_bar, &style_status_bar, LV_STATE_DEFAULT); /*默认style*/

    static lv_ft_info_t info;

    info.name = "AGENCYB.TTF";
    info.weight = 100;
    info.style = FT_FONT_STYLE_NORMAL;
    info.mem = NULL;
    if(!lv_ft_font_init(&info)) {
        LV_LOG_ERROR("create failed.");
    }

    /*Create style with the new font*/
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, info.font);
    lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);

    /*Create a label with the new style*/
    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "Hello world\nI'm a font created with FreeType");
    lv_obj_center(label);

    return;
}


void gui(void)
{
    create_status_bar();
}

