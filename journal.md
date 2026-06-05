# Building A Particle Simulation

### Step 1: Create a main.cpp file using:
> `touch main.cpp`

### Step 2: Create a SDL3 Window:
- We defined a function `bool init()` to initialize SDL.
```bash
# SDL_Init() is used to initialize SDL, so we can start using it.
SDL_Init(SDL_INIT_VIDEO); # is specifically used to initialize the video subsystem.
```
- This function `bool init()`: Initializes SDL and creates a window.
- This function `bool loadMedia()`: Loads images.
- This function `void close()`: Cleans up the resources used to load the window

```bash
cd build

# Compile with this:
g++ ../main.cpp -o app.exe $(pkg-config --cflags --libs sdl3)

# Run:
./app.exe
```

### Step 3: Add a Renderer:
- Created a `Texture` class to wrap `SDL_Texture`.
- `init()`, `loadMedia()`, `close()` were modified to make use of `Texture`.
- We added two new global constants `gRenderer` and `gPngTexture`.

**Global Constants:**
- `gRenderer` is of type `SDL_Renderer`
- `gPngTexture` is of type `Texture`

> `bool init()` was refactored to initialize the `SDL_Renderer` and `SDL_Window` objects.

> `bool loadMedia()` loads images using the LTexture wrapper class.

> `void close()` cleans up the window, renderer, and texture resources.

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
I modularized my code and split the code into two folders:

- `include/`: This stores all the header files for my project.
- `engine/`: This stores the .cpp files that define our headers.


> `assets/`: This stores our project assets.

The two folders `include/`, and `engine/` follow this architecture.

The files in these folders are grouped like this:
- `core/`: It represents core code like my app struct, our global variables, and my config structs.
- `physics/`: It implements physics concept like forces.
- `particles/`: It stores our particle struct.
- `rendering/`: It's for rendering.

To build:
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

- `renderer` is our `SDL_Renderer`, `center_x` is the x_co-ord of our particle, `center_y` is the y_co-ord of our particle, and `radius` is the radius of the circle we'll render on the screen.

**Refactored `render()` into two different functions `render_img()`, and `render_circle_with_dark_bckgrd()`:**

- `render img()` accepts a paramerter called color, the parameter colors the background as our function renders an image on screen. the other function uses a darkbackground and then draws a circle.

- `render_circle_with_dark_bckgrd()` used `drawCircle()`:
- `drawCircle()` was a naive approach to drawing circles and `render_circle_with_dark_bckgrd()` renders them on a dark background texture;

- `render_rectangle_with_dark_background()` renders a rectangle to the screen.

**I added a bouncing feature:**
- The `Particle` object bounces when it's y-position is greater than the screen height

**Condition:**
> `particle.y >= screenHeight`

**How it bounces:**
- We first check if a `particle` satisfies the above condition. 
- If it does, we change it's y-position to screenHeight and multiply it's velocity by `-0.8f`.
- The velocity changes to 80% of it's value, `-0.8f` is negative.
- The multiplication of velocity by `-0.8f` reverses the direction of our velocity.

### Step 6: Event Handling
- This whole commit is about handling a keyboard event in our app.
- I added some more functions, and made our `App` able to store and possess multiple textures(UP, DOWN, LEFT, RIGHT).
- To load the `Texture`'s, the `loadFourMediaTextures()` function that takes care of that.
- The `main` handles a keyboard event and allows us to change texture based on the key we pressed.

> I learned color keying and used it to set a surface color key for my `foo.png`

### Step 7: A Particle System
- I built a particle simulation in the `main.cpp`.
- It listens for a mouse event, and initializes the particles after detecting a mouse click.

- It has a `ParticleRenderer` class that renders particles on the screen.

After that, I built a `ParticleSystem` class.
It has the methods `emit()`, `update()`, and `render()`.

**The functions:** 
- `emit()`: It takes three parameters the x-position, y-position, and count of particles you want to emit.
- `update()`: It's the state-update method, it takes three parameters gravity, floor, and dt and calls the `update()` method of the `Particle` class.
- `render()`: This method draws every particle in the member variable `particles` and renders them using the `ParticleRenderer::draw()` function as points on the screen. 