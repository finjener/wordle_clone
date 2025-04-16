# Wordle Clone - MVC Architecture with CMake

This is a clone of famous game Wordle. After developed this simple game I rewrote the game in order to using model-view-controller architecture especially for using with qml and hierarchical cmake structure for to see on hand if it is benefical.

## MCV

### Model

The Model component handles data and business logic:

- **WordModel**: Manages the word list, provides word validation, and selects random words
- **GameModel**: Manages game state, including attempts, current position, and game status
- **WordEvaluator**: Handles the logic for evaluating word attempts against the target word

### View

The View component is responsible for the user interface:

- **MainView.qml**: The main application window and layout
- **Components**: Modular UI elements (Header, GameGrid, GridItem, InfoBox, PlayAgainButton)

### Controller

The Controller connects the Model and View:

- **GameController**: Coordinates game logic by connecting user actions from the view to the appropriate model functions

## File Structure

```
├── CMakeLists.txt           # Main CMake file
├── src/                     # Source code directory
│   ├── CMakeLists.txt       # CMake for src directory
│   ├── main.cpp             # Main application entry point
│   ├── model/               # Model components
│   │   ├── CMakeLists.txt
│   │   ├── WordModel.h/.cpp
│   │   ├── GameModel.h/.cpp
│   │   └── WordEvaluator.h/.cpp
│   ├── controller/          # Controller components
│   │   ├── CMakeLists.txt
│   │   └── GameController.h/.cpp
│   └── view/                # View components
│       ├── CMakeLists.txt
│       ├── MainView.qml
│       └── components/      # Reusable UI components
│           ├── Header.qml
│           ├── GameGrid.qml
│           ├── GridItem.qml
│           ├── InfoBox.qml
│           └── PlayAgainButton.qml
├── qml.qrc                  # QML resource file
├── WORDS                    # Dictionary file
└── build.sh                 # Build script
```

## CMake Structure

### Root CMakeLists.txt
- Located in the project root directory
- Sets up global project configuration
- Defines project name, version, and language
- Configures Qt dependencies
- Sets C++ standard
- Includes subdirectories for different components

### Source Directory CMakeLists.txt
`src/` directory:
- Manages all source filescv
- Organizes build targets
- Includes subdirectories for MVC components
- Handles main application target configuration

### Model Layer CMakeLists.txt
`src/model/`:
- Manages model component compilation
- Includes WordModel, GameModel, and WordEvaluator
- Handles model-specific dependencies
- Ensures proper linking of model components

### Controller Layer CMakeLists.txt
`src/controller/`:
- Manages controller component compilation
- Includes GameController and WordleController
- Handles controller-specific dependencies
- Links with model components

### View Layer CMakeLists.txt
`src/view/`:
- Manages QML resources and components
- Handles UI-specific configurations
- Includes all QML files and assets
- Links with controller components

### Build Instructions

To build the project, simply run:

```bash
./build.sh
```

Or manually with CMake:

```bash
mkdir -p build_cmake
cd build_cmake
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

To run the application:

```bash
cd build_cmake
./wordle
```

## Game Rules

1. Guess the 5-letter word in 6 attempts or less.
2. After each guess, the color of the tiles will change to show how close your guess was to the word:
   - Green: Letter is in the correct spot
   - Yellow: Letter is in the word but in the wrong spot
   - Gray: Letter is not in the word

## License

[MIT License](LICENSE)

Original game link: https://www.nytimes.com/games/wordle/index.html

## Screenshots
![1](https://github.com/ferhatsencer/wordle_clone/blob/main/screenshots/1.png)
![2](https://github.com/ferhatsencer/wordle_clone/blob/main/screenshots/2.png)
![3](https://github.com/ferhatsencer/wordle_clone/blob/main/screenshots/3.png)
![4](https://github.com/ferhatsencer/wordle_clone/blob/main/screenshots/4.png)
![5](https://github.com/ferhatsencer/wordle_clone/blob/main/screenshots/5.png)
![6](https://github.com/ferhatsencer/wordle_clone/blob/main/screenshots/6.png)
![7](https://github.com/ferhatsencer/wordle_clone/blob/main/screenshots/7.png)
![9](https://github.com/ferhatsencer/wordle_clone/blob/main/screenshots/9.png)
![10](https://github.com/ferhatsencer/wordle_clone/blob/main/screenshots/10.png)
![11](https://github.com/ferhatsencer/wordle_clone/blob/main/screenshots/11.png)


# Tech Stack
- CMake 3.14
- Qt 6.0
- C++17


***To be done:***
- Appimage executable
