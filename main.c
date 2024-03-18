#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define WDISPLAY 800
#define HDISPLAY 600

struct rectangle {
    float x, y; // coordinates
    float w ; // width
    float h; // height
    float dx, dy;
};

typedef struct rectangle RECTANGLE;

int main() {
    // Declarations
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_COLOR red = {0};
    ALLEGRO_TIMER * timer = NULL;
    ALLEGRO_EVENT_QUEUE * fifo = NULL;
    ALLEGRO_EVENT event = {0};
    bool fini = false;
    bool actif = false;

    RECTANGLE p = {0,0,50,30, 5, 5};

    // Initialisation
    assert(al_init());
    assert(al_install_keyboard());
    assert(al_init_primitives_addon());

    // centrer le rectangle
    p.x = WDISPLAY/2.0 -  p.w/2.0;
    p.y = HDISPLAY/2.0 - p.h/2.0;

    // creation
    // display
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(WDISPLAY, HDISPLAY);
    // timer
    timer = al_create_timer(1.0/30.0);
    // fifo
    fifo = al_create_event_queue();
    // red color
    red  = al_map_rgba(255,0,0,255);

    // sources
    // events coming from display
    al_register_event_source(fifo, al_get_display_event_source(display));
    // events coming from clavier
    al_register_event_source(fifo, al_get_keyboard_event_source());
    // events coming from timer
    al_register_event_source(fifo, al_get_timer_event_source(timer));


    // event loop
    al_start_timer(timer);
    while(!fini){
        // pioche un event
        al_wait_for_event(fifo, &event);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_TIMER:
                if(actif) {
                    if (p.x < 0) {
                        p.x = 0;
                    } else {
                        p.x = p.x - p.dx;
                    }
                }
                al_clear_to_color(al_map_rgb(255,255,255));
                al_draw_filled_rectangle(p.x, p.y, p.x + p.w, p.y + p.h, red);
                al_flip_display();
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        actif = true;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        p.x  = p.x  + p.dx;
                        break;

                }
                break;
            case ALLEGRO_EVENT_KEY_UP:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_LEFT:
                        actif = false;

                }
                break;
        }

    }



    // liberation
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(fifo);
    return 0;
}
