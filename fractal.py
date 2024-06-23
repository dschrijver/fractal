import numpy as np
from numba import njit
import matplotlib.pyplot as plt
from multiprocessing import Pool
from tqdm import tqdm


@njit
def double_pendulum(t, y, grav, m1, m2, l1, l2):
    theta1 = y[0]
    dtheta1 = y[1]
    theta2 = y[2]
    dtheta2 = y[3]
    dy = np.empty(y.shape)
    dy[0] = dtheta1
    dy[1] = (-grav*(2.0*m1+m2)*np.sin(theta1)-m2*grav*np.sin(theta1-2.0*theta2)-2.0*np.sin(theta1-theta2)*m2*(dtheta2*dtheta2*l2+dtheta1*dtheta1*l1*np.cos(theta1-theta2)))/(l1*(2.0*m1+m2-m2*np.cos(2.0*theta1-2.0*theta2)))
    dy[2] = dtheta2
    dy[3] = (2.0*np.sin(theta1-theta2)*(dtheta1*dtheta1*l1*(m1+m2)+grav*(m1+m2)*np.cos(theta1) + dtheta2*dtheta2*l2*m2*np.cos(theta1-theta2)))/(l2*(2.0*m1+m2-m2*np.cos(2.0*theta1-2.0*theta2)))
    return dy


@njit # Runge-Kutta 4
def runge_kutta(f, dt, t, y, params):
    k1 = dt*f(t, y, *params)
    k2 = dt*f(t+0.5*dt, y+0.5*k1, *params)
    k3 = dt*f(t+0.5*dt, y+0.5*k2, *params)
    k4 = dt*f(t+dt, y+k3, *params)
    return y + (1.0/6.0)*(k1 + 2.0*k2 + 2.0*k3 + k4)


@njit
def calc_flip(theta, t_list, dt, params):
    flip_t = 0
    for i in range(len(t_list)-1):
        t = t_list[i]
        theta_old = theta.copy()
        theta = runge_kutta(double_pendulum, dt, t, theta_old, params)
        if ((theta_old[0]<np.pi) and (theta[0]>np.pi)):
            flip_t = t_list[i+1]
            break
        if ((theta_old[0]>np.pi) and (theta[0]<np.pi)):
            flip_t = t_list[i+1]
            break
        if ((theta_old[2]<np.pi) and (theta[2]>np.pi)):
            flip_t = t_list[i+1]
            break
        if ((theta_old[2]>np.pi) and (theta[2]<np.pi)):
            flip_t = t_list[i+1]
            break
    return flip_t


def main():
    # --- Parameter Setup --- #
    # All variables are expressed in SI units.
    NUM_PROCESSES = 6
    num_theta_ini = 500 # Number of pendulums in x and y direction
    dt = 0.01
    t_final = 10_000
    grav = 1.0
    m1 = 1.0
    m2 = 1.0
    l1 = 1.0
    l2 = 1.0
    params = (grav, m1, m2, l1, l2)

    # --- Calculation of number of flips --- #
    t_list = np.arange(0, t_final+dt, dt)
    theta_1_ini = np.linspace(-np.pi, np.pi, num_theta_ini)
    theta_2_ini = np.linspace(-np.pi, np.pi, num_theta_ini)
    calc_params = []
    for x in range(num_theta_ini):
        for y in range(num_theta_ini):
            calc_params.append((np.array([theta_1_ini[x], 0, theta_2_ini[y], 0]), t_list, dt, params))
    pool = Pool(NUM_PROCESSES)
    result = pool.starmap(calc_flip, tqdm(calc_params, total=len(calc_params)))
    grid = np.array(result).reshape((num_theta_ini, num_theta_ini))
    grid[grid == 0] = t_final
    grid[grid < t_final] = 0

    # --- Plotting --- #
    px = 1/plt.rcParams['figure.dpi']
    fig = plt.figure(figsize=(1000*px, 1000*px), frameon=False)
    ax = plt.Axes(fig, [0., 0., 1., 1.])
    ax.set_axis_off()
    fig.add_axes(ax)
    ax.imshow(grid.T, origin="lower", cmap='gray', vmin=np.min(grid), vmax=np.max(grid), 
              extent=[theta_1_ini[0], theta_1_ini[1], theta_2_ini[0], theta_2_ini[1]])
    ax.grid()
    fig.savefig("Fractal_cropped.jpg")


if __name__ == "__main__":
    main()