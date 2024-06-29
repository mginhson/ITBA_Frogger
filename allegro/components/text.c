#include "text.h"
#include "../util.h"
#include <string.h>
#include <stdio.h>
text_t * create_text(char* text, g_info_t * g_info, assets_t * font, float x, float y, int font_size, int centered){
    if (centered){
        x -= (strlen(text) * font_size) / 2;
    }
    text_t new_text = {
        0, text, g_info, font, x, y, font_size, centered
    };
    text_t * p_to_text = malloc(sizeof(text_t));
    *p_to_text = new_text;
    return p_to_text;
    
}

void draw_text(text_t *text){
    sprite_to_text(text->text, text->g_info, text->font, text->x, text->y, text->font_size, text->centered);
    return;
}
int text_was_selected(text_t* text, int x, int y){
    /*printf("%f\n", (text->x));
    printf("%f\n", (text->x + strlen(text->text) * REZISE(SHORT_SIZE)));
    printf("%d\n", (text->y <= y));*/
    if ((text->x <= x )&& (text->x + strlen(text->text) * REZISE(text->font_size)) >= x  && (text->y <= y) && y <= (text->y + text->font_size)){
        return 1;
    }
    return 0;

}
void destroy_text(text_t * text){
    free(text);
}