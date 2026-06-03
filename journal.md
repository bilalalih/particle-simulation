# Building a Single Particle Simulation

### Step 1: Create a main.cpp file using:
> `touch main.cpp`

### Step 2: Create a SDL3 Window:
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

### Step 3: Add a Renderer:
- Using SDL_Image, we created Texture class to wrap SDL_Texture class.
- We modified our `init()`, `loadMedia()`, `close()` to make use of our Texture class
- we added two new global constants `gRenderer` and `gPngTexture`, a Renderer and our Texture wrapper class.

> In the function `bool init();` we now create a renderer with the window.

> This function `bool loadMedia();` loads images using our LTexture wrapper class.

> This function `void close();` cleans up the resourse used to load the window and renderer and destroys our texture.

```bash
bool init()
{
    # Initialization Flag
    bool success{ true };
    
    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        SDL_Log("SDL could not initialize! SDL Error: %s/n", SDL_GetError());
        success = false;
    } else 
    {
        # Create Window with Renderer
        if (SDL_CreateWindowAndRenderer(
            "Particle SImulation: Texture And Extension Libraries", 
            screenConstants::kScreenWidth, 
            screenConstants::kScreenHeight,
            0,
            &global::gWindow,
            &global::gRenderer
            ) == false
        ){
            SDL_Log("Window Could Not Be Created! SDL Error: %s/n", SDL_GetError());
            success = false;
        }

    }

    SDL_Log("SDL Initialized Succesfully");
    return success;
}

bool loadMedia()
{
    # File loading flag
    bool success{ true };

    # Load splash image
    if (global::gPngTexture.loadFromFile("assets/loaded.png") == false)
    {
        SDL_Log("Unable To Load PNG Image!\n");
        success = false;
    }

    return success;
}

void close()
{

    # Clean up Texture
    global::gPngTexture.destroy();

    # Destroy Window
    SDL_DestroyRenderer( global::gRenderer );
    global::gRenderer = nullptr;
    SDL_DestroyWindow( global::gWindow ); 
    global::gWindow = nullptr;

    # Quit SDL subsystems
    SDL_Quit();
}
```

### Step 4: Modularize Structure
I modularized my code here and split the code into two folders:
- `include/`: this stores all the header files for my project.
- `engine`: this stores the .cpp files that define our headers.
- `assets/`: this stores our project assets.

Those two folders follow this architecture.
All files in:
- `core/`: it represents core code like my app struct, our global variables, and my config structs.
- `physics/`: it implements physics concept like forces.
- `particles/`: it stores our particle struct.
- `rendering/`: it's for rendering.

To Build:
```bash
cd build/
cmake .. -G Ninja
cmake --build .

# Run in project directory:
./build/particle_sim.exe
```

### Step 5: Draw a Circle? Render Shapes.
- I created a `Particle` struct with only one attribute, position.
- The `Particle` was rendered on my screen as a circle by the `rendering::drawCircle()` function which takes four arguments `renderer`, `center_x`, `center_y`, `radius`.
- renderer is our SDL_Renderer, center x is the x_co-ord of our particle, center_y is the y_co-ord of our particle, radius is the radius of the circle we'll render on screen.
- I did some refactoring and changed `render()` into two different functions `render_img()`, and `render_circle_with_dark_bckgrd()`. render img accepts a paramerter called color, the parameter colors the background as our function renders an image on screen. the other function uses a darkbackground and then draws a circle.
- I built a render function for rectangles this time, `render_rectangle_with_dark_background()`
- the main now renders just a rectangle with the color you set in a dark bakground.
- I added a bounce feature but only for the right side of the x-axis(the positive side)