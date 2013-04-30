# Game Design Document
My game will be a continuous survival game whose characters are based on the Minecraft characters (mobs)

## Entities
#### Example of game characters:
![Minecraft Mobs](http://fc09.deviantart.net/fs71/f/2012/153/2/c/minecraft_mob_magnets_by_vandonovan-d51yxlt.jpg "Minecraft Characters")

Each character will move differently.  The Player (bottom-right in the above picture) will be freely controlled by the mouse, independent of the clock.
Enemies:
+ Zombies (top-middle) will move slowly, always toward the player.
+ Creepers (middle-left) will move slightly faster toward the player and explode if they get close.
+ Spiders (not pictured) will move in a random direction and speed; there is a random chance that it will change directions again.
+ Endermen (top-left) will teleport randomly in a limited radius, with a greater chance of teleporting toward the player.
+ Skeletons (top-right) will circle the player with a random chance of switching directions.
Additionally, there will be hearts that randomly appear, which will replenish the player's health.  These hearts will remain stationary.


## Gameplay
The user will move the mouse to directly control the on-screen Player's position, avoiding the mobs for as long as possible.  The player has a maximum speed, and the player follows the mouse cursor.


## Score
The score continuously goes up.  The final score is determined by the score's value when the player dies.


## Player's Lives
The player will have one life but multiple health points.  Different enemies will do different amounts of damage.


## User Interface
#### Sketch:
![UI Sketch](http://i.imgur.com/3BQU3em.png "UI Sketch")

User interface elements:
+ NEW GAME button starts a new game, prompting the user first if a game is in progress
+ QUIT button closes the game, prompting the user first if a game is in progress
+ Middle region is gameplay region (cursor pictured on top of the Player character)
+ Below middle region is the Player's health and score.
