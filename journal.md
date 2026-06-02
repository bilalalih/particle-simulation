# Building a Single Particle Simulation

## Step 1: Create a main.cpp file using:
- `touch main.cpp`

## Step 2: Create a SDL3 Window:
- We first create a function `bool init();` to initialize our SDL.
```bash
# SDL_Init() is used to initialize SDL, so we can start using it.
SDL_Init(SDL_INIT_VIDEO); # is specifically used to initialize the video subsystem.
```
- This function `bool init();` initializes our SDL and creates a window.
- This function `bool loadMedia();` loads images.
- This function `void close();` cleans up the resourse used to load the window

```bash
cd build

# Compile with this:
g++ ../main.cpp -o app.exe $(pkg-config --cflags --libs sdl3)

# Run:
./app.exe
```