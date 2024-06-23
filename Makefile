double_pendulum_fractal_animation: clean_double_pendulum_fractal_animation double_pendulum_fractal_animation.out
	@./double_pendulum_fractal_animation.out

double_pendulum_fractal_animation.out:
	@clang double_pendulum_fractal_animation.c runge_kutta.c -o double_pendulum_fractal_animation.out -O3 -Wall -Wextra -lraylib -lm

clean_double_pendulum_fractal_animation:
	@rm -f double_pendulum_fractal_animation.out


animate_double_pendulum: clean_animate_double_pendulum animate_double_pendulum.out
	@./animate_double_pendulum.out

animate_double_pendulum.out:
	@clang animate_double_pendulum.c runge_kutta.c -o animate_double_pendulum.out -O3 -Wall -Wextra -lraylib -lm

clean_animate_double_pendulum:
	@rm -f animate_double_pendulum.out
