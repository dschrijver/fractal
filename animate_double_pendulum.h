#ifndef ANIMATE_DOUBLE_PENDULUM_H
#define ANIMATE_DOUBLE_PENDULUM_H


#define SCREEN_WIDTH    (int) 1000
#define SCREEN_HEIGHT   (int) 1000
#define DOT_SIZE        (int) 10
#define FPS          (double) 60.0 
#define ACCURACY        (int) 2   // Number of physics steps per frame

#define pi           (double) 3.14159265358979323846
#define grav         (double) 9.81  // gravitational acceleration [m/s^2]
#define m1           (double) 10.0  // [kg]
#define m2           (double) 1.0   // [kg]
#define l1           (double) 1.0   // [m]
#define l2           (double) 1.0   // [m]
#define MARGIN          (int) 4*DOT_SIZE // [pixels]
#define LENGTH       (double) ((double)SCREEN_WIDTH-(double)MARGIN)/(2.0*(l1+l2)) // [pixels/m]

#define N_p             (int) 1000      // Number of pendulums
#define dt           (double) (1.0/(((double)ACCURACY)*FPS))  // [s]
// #define N               (int) ((t1-t0)/dt)
#define dp           (double) (0.000001*pi)   // Starting angle difference between pendulums [rad]
#define theta0       (double) (0.6*pi) // [rad]

#endif