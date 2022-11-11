# SimonGame
Simon Says Memory Game, Made with QT and C++.

The ubiquitous Simon Says Memory Game, made in QT and C++. The aim is to accurately follow the sequence of flashing colours. Behind the scenes the program generates a 50 digit sequence consisting only of the numbers 1,2,3,4 and stored into a Vector for sequential playback. This corresponds to the sequence of coloured square labels that need to be pressed in order.

Each Coloured Square is a separate Label object, whose colour is provided as a parameter in the constructor. The flashing appearance is performed through the use of CSS Style Sheets which also work with QT. By providing a slightly offset hexcode, the colours "appear" to flash.

The main game logic is reading through the sequence array and flashing the appropriate coloured label. If you incorrectly guess the wrong colour in the sequence, the correct colour is flashed to show you where you've gone wrong and the game is reset. The title bar is updated as you play to show you the length of the sequence you have currently successfully remembered which can be a useful aid for achieving goals and pursuing memory improvement.

https://user-images.githubusercontent.com/111576658/201333848-25cdf47c-ff26-443b-8913-94281e532a00.mp4

