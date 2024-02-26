# Wordle Clone!

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


## Game Explanation

_**Wordle**_ is a web-based word game created and developed by Welsh software engineer Josh Wardle. Players have six attempts to guess a five-letter word, with feedback given for each guess in the form of colored tiles indicating when letters match or occupy the correct position.
In this clone the game starts immediately when you launch the app and you can start entering letters to enter a 5-letter word. And you **can use your phsical keyboard** with **enter, delete and for letter input**. The indicator is moving automatically when you enter and delete. **After every 5 letters you can press enter to move to the next line** if the word is present in the word list and if there is any letter in the same position as the letter in the answer it will be **highlighted** in **green**, if there is a letter but the position is not the same it will only be highlighted in **yellow**. If the word is not in the list you will not be able to move to the next line and you will see a message below that the word is not valid. You should use backspace button to delete letter and enter a valid one. After successfully entering 5 words you will enter the last word and if you enter a valid word the game will end with you losing or winning and if you lose then **you will be informed below with the answer.**

# Tech Stack
Qt5.14.2
Qml
Cpp

## File Structure

    main.cpp
    WordleBackend.h/cpp
    main.qml
    words.txt


## Todo

 - Play/reset again function/button without closing application for
   start playing again.
 - More documentation/comments, doxygen
 - Visual indicator tick mark next to each row after each successful
   valid word enter
 - Tidying up codebase.

## Build/Run

**For build**

 1. Download Qt5.14.2 according to your operating system and install:
    https://download.qt.io/archive/qt/5.14/5.14.2/
 2. git clone https://github.com/ferhatsencer/wordle_clone.git
 3. Open project with qtcreator, build and run the game.

~~***To be done:***
Or for just run the game:

 ~~1. Download this appimage ----link to appimage wordle clone----
 2. chmod +x wordle-clone.AppImage
 3. ./wordle-clone.AppImage~~~~
