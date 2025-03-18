#include <windows.h>

int width, height;
bool running = true;
void* buffer_memory;

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wparam, LPARAM lparam) {
	LRESULT result = 0;

	//fecha a janela caso clique no X no canto superior direito
	if (uMsg == WM_CLOSE || uMsg == WM_DESTROY) {
		running = false;
	}
	else if (uMsg == WM_SIZE){ //CASO mude tamanho da janela, com rect = retangulo a ser alocado o buffer
		RECT rect;
		GetClientRect(hwnd, &rect);

		width = rect.right - rect.left;
		height = rect.bottom - rect.top;

		int buffer_size = width * height * sizeof(unsigned int);

		if (buffer_memory) VirtualFree(buffer_memory, 0, MEM_RELEASE); //CASO o buffer_memory ja tenha sido alocado anteriormente
		buffer_memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	}
	else {
		result = DefWindowProc(hwnd, uMsg, wparam, lparam);
	}

	return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	//criando classe window
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game";
	window_class.lpfnWndProc = window_callback;

	//registrando a classe criada
	RegisterClass(&window_class);

	//criando a classe window registrada
	HWND window = CreateWindow(window_class.lpszClassName, "Pong Game", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);

	//game loop
	while (running == true) {

		//Input
		MSG message;

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessage(&message);


		}


		//simulate



		//render


	}
		


}