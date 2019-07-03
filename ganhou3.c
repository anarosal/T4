#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#define FRASES 2

void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}



/*enum BOUNCER_TYPE {
    BT_HELLO = 0,
    BT_MYSHA,
    BT_TRIANGLE,
    BT_RECTANGLE_1,
    BT_RECTANGLE_2,
    BT_CIRCLE1,
    BT_CIRCLE2,
    BT_CIRCLE3,
    BT_CIRCLE4,
    BT_CIRCLE5,
    BT_CIRCLE6,
    BT_LINE1,
    BT_LINE2,
    BT_N
};*/

/*typedef struct FRASES
{
    float x, y;
    float dx, dy;
    //int type;
}FRASES;*/

int main()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY* disp = al_create_display(700, 700);
    must_init(disp, "display");

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT* font = al_load_font("arial.ttf", 32, 0);
    must_init(font, "font");

    must_init(al_init_image_addon(), "image addon");
    ALLEGRO_BITMAP* acido = al_load_bitmap("acido.jpg");

    must_init(acido, "acido");
    //must_init(heart, "heart");
    //must_init(zumbi, "zumbi");

    //must_init(al_init_primitives_addon(), "primitives");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    float x[FRASES];
    float dx[FRASES];



   for(int i = 0; i < FRASES; i++){
     if(i%2==0){
      x[i] = -500*i;
    }
    else{
      x[i] = 700 + 500*i;
    }
    dx[i] = 1;
    }

    /*BOUNCER obj[BT_N];
    for(int i = 0; i < BT_N; i++)
    {
        BOUNCER* b = &obj[i];
        b->x = rand() % 640;
        b->y = rand() % 480;
        b->dx = ((((float)rand()) / RAND_MAX) - 0.5) * 2 * 4;
        b->dy = ((((float)rand()) / RAND_MAX) - 0.5) * 2 * 4;
        b->type = i;
    }*/

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(queue, &event);
        switch(event.type)
        {

            case ALLEGRO_EVENT_TIMER:
                //for(int i = 0; i < BT_N; i++)
                //{


                  for(int i = 0 ; i < FRASES; i++){
                    if(i%2==0){
                      x[i] += dx[i];
                      if(x[i] < 350)
                      {
                          x[i]  += 5;
                          dx[i] *= 0.5;
                      }

                      else{
                        dx[i] = 0;
                      }
                    }
                    else{
                      x[i] -= dx[i];
                      if(x[i] > 350)
                      {
                          x[i]  -= 5;
                          dx[i] *= 0.5;
                      }

                      else{
                        dx[i] = 0;
                      }
                    }
                  }
                    /*if(b->x > 640)
                    {
                        b->x -= (b->x - 640);
                        b->dx *= -1;
                    }
                    if(b->y < 0)
                    {
                        b->y  *= -1;
                        b->dy *= -1;
                    }
                    if(b->y > 480)
                    {
                        b->x -= (b->y - 480);
                        b->dy *= -1;
                    }*/
                //}

                redraw = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue))
        {

            //ALLEGRO_VERTEX v[4];
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_text(font, al_map_rgb(255, 0, 0), x[0], 250, 1, "VOCÊ GANHOU ÁCIDO SULFÚRICO");
            al_draw_bitmap(acido, x[1]-25, 350, 0);
            //al_draw_text(font, al_map_rgb(255, 0, 0), x[2], 450, 1, "AGORA VOCÊ TEM ÁLCOOL PROPÍLICO");
            //al_draw_text(font, al_map_rgb(255, 0, 0), x[3], 500, 1, "E PODE SE DESCOLAR !");

            //for(int i = 0; i < BT_N; i++)
            //{
                //BOUNCER* b = &obj[i];
                //switch(b->type)
                //{
                    //case BT_HELLO:
                        //al_draw_text(font, al_map_rgb(255, 255, 255), b->x, b->y, 0, "Hello world!");
                        //break;

                    /*case BT_MYSHA:
                        al_draw_bitmap(mysha, b->x, b->y, 0);
                        break;

                    case BT_TRIANGLE:
                        al_draw_filled_triangle(b->x, b->y, b->x + 50, b->y + 25, b->x, b->y + 50, al_map_rgb_f(0, 1, 0));
                        break;

                    case BT_RECTANGLE_1:
                        al_draw_filled_rectangle(b->x, b->y, b->x + 100, b->y + 80, al_map_rgba_f(0, 0, 0.5, 0.5));
                        break;

                    /*case BT_RECTANGLE_2:
                        v[0].x = b->x;       v[0].y = b->y;       v[0].z = 0; v[0].color = al_map_rgb_f(1, 0, 0);
                        v[1].x = b->x + 120; v[1].y = b->y;       v[1].z = 0; v[1].color = al_map_rgb_f(0, 1, 0);
                        v[2].x = b->x;       v[2].y = b->y + 100; v[2].z = 0; v[2].color = al_map_rgb_f(0, 0, 1);
                        v[3].x = b->x + 120; v[3].y = b->y + 100; v[3].z = 0; v[3].color = al_map_rgb_f(1, 1, 0);

                        al_draw_prim(v, NULL, NULL, 0, 4, ALLEGRO_PRIM_TRIANGLE_STRIP);
                        break;*/

                  /*  case BT_CIRCLE1:
                        al_draw_circle(b->x, b->y, 30, al_map_rgb_f(1, 0, 1), 2);
                        break;

                    case BT_CIRCLE2:
                        al_draw_circle(b->x, b->y, 30, al_map_rgb_f(1, 0, 0), 2);
                        break;

                    case BT_CIRCLE3:
                        al_draw_circle(b->x, b->y, 30, al_map_rgb_f(1, 1, 0), 2);
                        break;

                    case BT_CIRCLE4:
                        al_draw_circle(b->x, b->y, 30, al_map_rgb_f(1, 0.5, 0), 2);
                        break;

                    case BT_CIRCLE5:
                        al_draw_circle(b->x, b->y, 30, al_map_rgb_f(0, 0, 1), 2);
                        break;

                    case BT_CIRCLE6:
                        al_draw_circle(b->x, b->y, 30, al_map_rgb_f(0, 1, 0), 2);
                        break;


                    case BT_LINE1:
                        al_draw_line(b->x, b->y, b->x + 20, b->y + 100, al_map_rgb_f(1, 0, 0), 1);
                        break;

                    case BT_LINE2:
                        al_draw_line(b->x, b->y, b->x + 70, b->y - 20, al_map_rgb_f(1, 1, 0), 1);
                        break;*/
                //}
            }

            al_flip_display();
            redraw = false;

    }


    al_destroy_bitmap(acido);

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}
