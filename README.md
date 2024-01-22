
# Ping~Pong game in C

Recently delved into the realm of old-school game development by creating a Pong game using plain C and Raylib. This was more of a small project aimed at familiarizing myself with Raylib, and it turned out to be quite an interesting experience.

## Features

#### 1. Title Screen:

- Displays game title: "PING - PONG!" by Darshan.
- Provides instructions and information about controls.
- Prompts the user to press ENTER to start the game.

#### 2. Gameplay Screen:

- Renders a visually appealing game court with a green background.
- Includes a central yellow line dividing the screen.
- Features rounded rectangle bats for both the player and CPU.
- Displays the ball as a red circle moving dynamically on the screen.
- Shows real-time scores for both the left and right players.
- Alerts players when one reaches a score of 5 points.
- Utilizes sound effects for ball hits and end-game scenarios.

#### 3. Game Logic:

- Implements collision detection for the ball with bats and screen boundaries.
- Provides smooth ball movement and bouncing physics.
- Includes an CPU-controlled right bat for single-player mode.
- Allows player control of the left bat using the Q and A keys.

#### 4. Scoring System:

- Updates and displays the score based on successful hits or misses.
- Declares a winner when one player reaches a score of 5 points.
- Handles end-game scenarios with appropriate sound effects.

#### 5. Ending Screen:

- Displays the winner and a corresponding message.
- Provides options to play again by pressing ENTER or quit by pressing ESCAPE.

#### 6. Graphics:

- Uses rounded rectangles for a modern look.
- Provides clear visual indicators for game elements.
- Presents a visually pleasing and coherent color scheme.

#### 7. Audio:

- Integrates background music during the title screen.
- Includes sound effects for ball hits and game outcomes.
- Adjusts sound volumes for a better gaming experience.

#### 8. Controls:

- Enables player control using the Q and A keys for the left bat.
- Implements gesture detection for touch-based input.
- Allows navigation using the ENTER key to progress through screens.

#### 9. General:

- Implements a simple game loop for continuous gameplay.
- Handles window initialization and deinitialization appropriately.
- Incorporates modular functions for better code organization.
- Provides a structured and user-friendly interface for an engaging gaming experience.







## Current Bugs and Future Scope

#### Current Bugs:

- Ball getting stuck to bat or playable boundary limit.
- Random jittering of ball causing bat to jitter with it.
- CPU bat goes out of boundary ( may be fixed by adding movement limit )

#### Future updates:

- Adding sprites and animation.
- Better looking user interface.
## Acknowledgements

 - [Raylib](https://www.raylib.com/)
 - [Raylib Cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html)
 - [Raylib Community](https://discord.gg/raylib)
 - [Andre Hamels Codes](https://www.youtube.com/@andrewhamelcodes712)


