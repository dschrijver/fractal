#include <stdio.h>
#include <math.h> // Raylib requires math.h
#include <raylib.h>

#include "runge_kutta.h" // ode_solve_n()
#include "double_pendulum_fractal_animation.h"


void double_pendulum(double t, double *y, double *dy) {
    (void) t;
    double theta1 = y[0];
    double dtheta1 = y[1];
    double theta2 = y[2];
    double dtheta2 = y[3];
    dy[0] = dtheta1;
    dy[1] = (-grav*(2.0*m1+m2)*sin(theta1)-m2*grav*sin(theta1-2.0*theta2)-2.0*sin(theta1-theta2)*m2*(dtheta2*dtheta2*l2+dtheta1*dtheta1*l1*cos(theta1-theta2)))/
            (l1*(2.0*m1+m2-m2*cos(2.0*theta1-2.0*theta2)));
    dy[2] = dtheta2;
    dy[3] = (2.0*sin(theta1-theta2)*(dtheta1*dtheta1*l1*(m1+m2)+grav*(m1+m2)*cos(theta1) + dtheta2*dtheta2*l2*m2*cos(theta1-theta2)))/
            (l2*(2.0*m1+m2-m2*cos(2.0*theta1-2.0*theta2)));
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Double Pendulum Fractal Animation");

    // Initial conditions of the fractal
    double t = 0.0;
    for (int i = 0; i < N_px; i++) {
        for (int j = 0; j < N_py; j++) {
            theta[i][j][0] = ((double)(i-N_px/2))*(2*PI)/N_px;
            theta[i][j][1] = 0.0;
            theta[i][j][2] = ((double)(j-N_py/2))*(2*PI)/N_py;
            theta[i][j][3] = 0.0;
        }
    }

    double start_time = 0.0, end_time = GetTime(), frame_time = GetTime();// For FPS management
    char fps_counter[10];
    Color color = {0, 255, 255, 255};
    int paused = 0;
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        PollInputEvents(); // Poll input events (SUPPORT_CUSTOM_FRAME_CONTROL)

        start_time = GetTime();
        if (IsKeyReleased(KEY_SPACE)) {
            paused = !paused;
        }
        if (IsKeyReleased(KEY_ENTER)) {
            t = 0;
            for (int i = 0; i < N_px; i++) {
                for (int j = 0; j < N_py; j++) {
                    theta[i][j][0] = ((double)(i-N_px/2))*(2*PI)/N_px;
                    theta[i][j][1] = 0.0;
                    theta[i][j][2] = ((double)(j-N_py/2))*(2*PI)/N_py;
                    theta[i][j][3] = 0.0;
                }
            }
            if (paused) paused = 0;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            for (int i = 0; i < N_px; i++) {
                for (int j = 0; j < N_py; j++) {
                    color.g = (char)(255.0*((theta[i][j][0])+PI)/(2.0*PI));
                    color.b = (char)(255.0*((theta[i][j][2])+PI)/(2.0*PI));
                    DrawRectangle(i*CELL_SIZE, j*CELL_SIZE, CELL_SIZE, CELL_SIZE, color);
                }
            }
            DrawText("ESCAPE to exit", 20, 20, 20, RED);
            DrawText("SPACE to pause and ENTER to reset", 20, 40, 20, RED);
            sprintf(fps_counter, "%.01f fps", 
                    1.0/(GetTime() - frame_time));
            frame_time = GetTime();
            DrawText(fps_counter, SCREEN_WIDTH-100, 20, 20, DARKGRAY);
        EndDrawing();
        SwapScreenBuffer(); // Flip the back buffer to screen (front buffer)

        if (!paused) {
            for (int i = 0; i < ACCURACY; i++) {
                for (int j = 0; j < N_px; j++) {
                    for (int k = 0; k < N_py; k++) {
                        runge_kutta_nstep(double_pendulum, dt, 4, t, theta[j][k], theta[j][k]);
                    }
                }
                t += dt;
            }
        }
        end_time = GetTime();
        if ((((double)ACCURACY)*dt-(end_time-start_time))>0.0) WaitTime(((double)ACCURACY)*dt-(end_time-start_time));
    }
    CloseWindow();

    return 0;
}