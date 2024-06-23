#ifndef DOUBLE_PENDULUM_FRACTAL_ANIMATION
#define DOUBLE_PENDULUM_FRACTAL_ANIMATION


#define SCREEN_WIDTH    (int) 600
#define SCREEN_HEIGHT   (int) 600
#define CELL_SIZE       (int) 3 // Width and height should be divisible by cell_size
#define FPS          (double) 30.0 
#define ACCURACY        (int) 2 // Number of physics steps per frame

#define pi           (double) 3.14159265358979323846
#define grav         (double) 9.81  // gravitational acceleration [m/s^2]
#define m1           (double) 10.0  // [kg]
#define m2           (double) 1.0   // [kg]
#define l1           (double) 1.0   // [m]
#define l2           (double) 1.0   // [m]

#define N_px            (int) (SCREEN_WIDTH / CELL_SIZE)
#define N_py            (int) (SCREEN_HEIGHT / CELL_SIZE)
#define dt           (double) (1.0/(((double)ACCURACY)*FPS))  // [s]
#define N               (int) ((t1-t0)/dt)

double theta[N_px][N_py][4] = {0};

#endif