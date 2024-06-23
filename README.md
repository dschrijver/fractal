# fractal
Creating fractals with the double pendulums. An in-depth explanation can be found [here](https://dschrijver.github.io/fractal.html).

## Requirements
For [fractal.py](fractal.py), install the required libraries using: ```pip install -r requirements.txt```. To compile [animate_double_pendulum.c](animate_double_pendulum.c) and [double_pendulum_fractal_animation.c](double_pendulum_fractal_animation.c), go through the following steps: 

This program is developed for GNU Linux. The required programs can be installed using the following command:

```
sudo apt install build-essential binutils clang git
```

Additionally, the [raylib](https://github.com/raysan5/raylib) library needs to be built and installed to a standard location. First install the required [libraries](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux). The following command installs the libraries for Ubuntu:

```
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

Download the raylib library using:

```
git clone https://github.com/raysan5/raylib.git
cd raylib/src/
```

Now edit the config file [config.h](https://github.com/raysan5/raylib/blob/master/src/config.h) in this folder to uncomment the following line (remove '//' at the start of the line):

```
//#define SUPPORT_CUSTOM_FRAME_CONTROL    1
```

The library can now be built and installed:

```
make PLATFORM=PLATFORM_DESKTOP
sudo make install
```

## Running the simulation
The programs [animate_double_pendulum.c](animate_double_pendulum.c) and [double_pendulum_fractal_animation.c](double_pendulum_fractal_animation.c) can be compiled and ran using the command ```make animate_double_pendulum``` and ```make double_pendulum_fractal_animation```. Settings can be changed in the respective header files. The python script can be run using a command like: ```python3 fractal.py```. The script is tested for Python 3.10.12. Settings can be changed in the 'Parameter Setup' section in [fractal.py](fractal.py). 
