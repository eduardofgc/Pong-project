#include <raylib.h>
#include <iostream>

int score = 0, oppScore = 0;
bool shouldReset = false;

class Rect{
    public:
        float width, height, rect_x, rect_y;

        Rect(float rect_x, float rect_y, float width, float height){
            this->rect_x = rect_x;
            this->rect_y = rect_y;
            this->width = width;
            this->height = height;
        }
};

void Reset(int x, int y){
    if (x - 20 <= 0){
        oppScore++;
    }
    else if (x + 20 >= GetScreenWidth()){
        score++;
    }
}

int main(){
    float ball_x = 800, ball_y = 400, ball_mov_x = 15, ball_mov_y = 15, ball_rad = 20;
    float cpu_mov_y = 8;

    InitWindow(1600, 800, "Pong");
    SetTargetFPS(60);

    Rect playerRect(20, 300, 50, 200);
    Rect oppRect(1520, 300, 55, 220);

    while(WindowShouldClose() == false){

        //input
        if (IsKeyDown(KEY_UP) && playerRect.rect_y != 0){
            playerRect.rect_y = playerRect.rect_y - 5;
        }
        else if (IsKeyDown(KEY_DOWN) && playerRect.rect_y != 590){
            playerRect.rect_y = playerRect.rect_y + 5;
        }

        //simulation

        ball_x = ball_x + ball_mov_x;
        ball_y = ball_y + ball_mov_y;

        //AI
        if (oppRect.rect_y + oppRect.height/2 > ball_y){
            oppRect.rect_y = oppRect.rect_y - cpu_mov_y;
        }
        else if (oppRect.rect_y + oppRect.height/2 <= ball_y) {
            oppRect.rect_y = oppRect.rect_y + cpu_mov_y;
        }

        //ceilling and floor collision
        if (ball_y + ball_rad >= GetScreenHeight() || ball_y - ball_rad <= 0){
            ball_mov_y = ball_mov_y * -1;
        }
        //if ball scores
        if (ball_x + ball_rad >= GetScreenWidth() || ball_x - ball_rad <= 0){
            Reset(ball_x, ball_y);

            ball_x = 800;
            ball_y = 400;

            ball_mov_x = ball_mov_x * -1;
        }
        //player collision
        if (CheckCollisionCircleRec(Vector2{ball_x, ball_y}, ball_rad, Rectangle{playerRect.rect_x, playerRect.rect_y, playerRect.width, playerRect.height+1})){
            ball_mov_x = ball_mov_x * -1;
        }

        //opp collision
        if (CheckCollisionCircleRec(Vector2{ball_x, ball_y}, ball_rad, Rectangle{oppRect.rect_x, oppRect.rect_y, oppRect.width, oppRect.height+1})){
            ball_mov_x = ball_mov_x * -1;
        }

        if (oppRect.rect_y < 0){
            oppRect.rect_y = 0;
        }
        else if (oppRect.rect_y + oppRect.height > GetScreenHeight()){
            oppRect.rect_y = GetScreenHeight() - oppRect.height;
        }

        //rendering
        BeginDrawing();

        ClearBackground(BLACK);

        DrawRectangle(playerRect.rect_x, playerRect.rect_y, 80*0.7, 300*0.7, BLUE);
        DrawRectangle(oppRect.rect_x, oppRect.rect_y, oppRect.width, oppRect.height, BLUE);
        DrawCircle(ball_x, ball_y, ball_rad, WHITE);

        DrawText(TextFormat("Score: %i", score), 20, 20, 20, WHITE);
        DrawText(TextFormat("CPU: %i", oppScore), 20, 40, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}