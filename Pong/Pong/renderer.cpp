//ultimo plano
void render_background (){
	unsigned int* pixel = (unsigned int*)buffer_memory;

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			*pixel++ = 0xff5500;
		}
	}

}

//clear
void clear_screen(unsigned int color) {
	unsigned int* pixel = (unsigned int*)buffer_memory;

	for (int i = 0; i < height; i++) {

		for (int j = 0; j < width; j++) {

			*pixel++ = color;
		}
	}
}

//força os pixels usados em draw_rect() a serem menores do que os limites da janela (width e height)
inline int
clamp(int min, int val, int max) {

	if (val < min) return min;
	if (val > max) return max;

	return val;
}


static void draw_rect_in_pixels(int x0, int y0, int x1, int y1, unsigned int color) { //onde x1 e y1 sao os limites de ate onde sera desenhado, e x0 e y0 sao o começo
	
	//escala os valores recebidos
	x0 = clamp(0, x0, width);
	y0 = clamp(0, y0, height);
	y1 = clamp(0, y1, height);
	x1 = clamp(0, x1, width);

	for (int y = y0; y < y1; y++) {
		unsigned int* pixel = (unsigned int*)buffer_memory + x0 + y * width;

		for (int x = x0; x < x1; x++) {

			*pixel++ = color;
		}
	}
}

static float render_scale = 0.01f;

//escala os pixels para o tamanho da janela
static void draw_rect(float x, float y, float halfsize_x, float halfsize_y, unsigned int color) {

	x *= height * render_scale;
	y *= height * render_scale;
	halfsize_x *= height * render_scale;
	halfsize_y *= height * render_scale;

	x += width /2.f;
	y += height /2.f;

	//mudando os pixels
	int x0 = x - halfsize_x;
	int y0 = y - halfsize_y;
	int x1 = x + halfsize_x;
	int y1 = y + halfsize_y;

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}