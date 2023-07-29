#define RSGL_NO_AUDIO
#define RSGL_IMPLEMENTATION
#include "RSGL.h"
#include "fonts.h"

#define paddle_volocity 8
#define ball_Xvolocity 5

char* si_u64_to_cstr(size_t num) {
	static char buffer[20 + 1]; /* NOTE(EimaMei): 20 chars is the maximum of numbers we can have in an u64. */
	char* cur_char = buffer;

	do {
		*cur_char++ = (num % 10) +'0';
		num /= 10;
	} while (num > 0);
	*cur_char = '\0';

	char* res = buffer;

	char* actual_str = res;

	char* a = actual_str;
    
    char* s;
    for (s = res; *s; s++);
    size_t len = s - res;

	char* b = actual_str + len - 1;
	len *= 0.5;

	while (len--) {
		do { typeof((*a)) tmp = (*a); (*a) = (*b); (*b) = tmp; } while (0);
		a++, b--;
	}

	res = actual_str;

	return res;
}

int main(int argc, char** argv) {
    RSGL_window* win = RSGL_createWindow("Lenny's Pong", RSGL_RECT(0,0,1000,500), RGFW_CENTER);

    RSGL_rect paddles[2] = {{30, 30, 48, 144}, {926, 30, 48, 144}};
    
    RSGL_circle ball = RSGL_CIRCLE((1000 - 48) / 2, (500 - 48) / 2, 48);
    RSGL_point ball_volocity = {0, 0};

    size_t points[2] = {0, 0};

    int i;

    srand(time(NULL));

    int font_ttf_index;
    for (font_ttf_index = 0; font_ttf_index < (sizeof(font_ttfs)/sizeof(char*)) && !si_path_exists(font_ttfs[font_ttf_index]); font_ttf_index++);

    if (!si_path_exists(font_ttfs[font_ttf_index])) {
        printf("No font file found\n");
        return 1;
    }
    
    int font = RSGL_loadFont(font_ttfs[font_ttf_index]);

    while (true) {
        /* check events */
        while (RSGL_window_checkEvent(win)) {
            if (win->event.type == RGFW_quit)
                goto quit;
            else if (win->event.type == RGFW_keyPressed && !ball_volocity.x) {
                ball_volocity.x = ball_Xvolocity * ((rand() % 1) ? 1 : -1);
            }
        }

        if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'a') {
            if (ball_volocity.x > 0 || RSGL_rectCollide(RSGL_RECT(paddles[0].x, ball.y, ball.d, ball.d), paddles[0]));

            else if (paddles[0].y < ball.y)
                paddles[0].y += paddle_volocity;
            else if (paddles[0].y > ball.y)
                paddles[0].y -= paddle_volocity;
        }

        else {
            if (RGFW_isPressedI(win, RGFW_W) && paddles[0].y > 0)
                paddles[0].y -= paddle_volocity;
            if (RGFW_isPressedI(win, RGFW_S)  && paddles[0].y < 500 - paddles[0].h)
                paddles[0].y += paddle_volocity;
        }
            
        if (RGFW_isPressedI(win, RGFW_Up) && paddles[1].y > 0)
            paddles[1].y -= paddle_volocity;
        if (RGFW_isPressedI(win, RGFW_Down) && paddles[1].y < 500 - paddles[1].h)
            paddles[1].y += paddle_volocity;

        ball = RSGL_CIRCLE((ball.x + ball_volocity.x), (ball.y + ball_volocity.y), ball.d);

        /* check physics */
        if (ball.x > (1000 - ball.d) || ball.x < 0) {
            ball = RSGL_CIRCLE((1000 - 48) / 2, (500 - 48) / 2, 48);
            paddles[0] = RSGL_RECT(30, 30, 48, 144); 
            paddles[1] = RSGL_RECT(926, 30, 48, 144);

            ball_volocity = RSGL_POINT(0, 0);
        }

        if (ball.y < 0 || (ball.y > 500 - ball.d))
            ball_volocity.y = -ball_volocity.y;

        for (i = 0; i < 2; i++) {
            /* check if paddle hit ball */
            if (RSGL_circleCollideRect(ball, paddles[i])) {
                ball_volocity.x = -ball_volocity.x;
                
                if (RSGL_circleCollideRect(ball, RSGL_RECT(paddles[i].x, paddles[i].y, paddles[i].w, paddles[i].h / 2)))
                    ball_volocity.y -= 1;
                else
                    ball_volocity.y += 1;
            }

            /* draw paddles */
            RSGL_drawRoundRect(paddles[i], RSGL_POINT(50, 50), RSGL_RGB(26, 127, 178));
            RSGL_drawRoundRect(RSGL_RECT(paddles[i].x + 5, paddles[i].y + 5, paddles[i].w - 10, paddles[i].h - 10), RSGL_POINT(40, 40), RSGL_RGB(77, 178, 229));
        }

        /* draw ball */
        RSGL_drawCircle(ball, RSGL_RGB(178, 26, 26));
        RSGL_drawCircle(RSGL_CIRCLE(ball.x + 4, ball.y + 4, ball.d - 8), RSGL_RGB(229, 77, 77));

        for (i = 0; i < 2; i++)
            RSGL_drawText(si_u64_to_cstr(points[i]), font, RSGL_CIRCLE((win->r.w / 2) - (40 * i), 20, 20), RSGL_RGB(255, 255, 255));

        RSGL_window_clear(win, RSGL_RGB(0, 0, 0));
    }

    quit:

    RSGL_window_close(win);
}