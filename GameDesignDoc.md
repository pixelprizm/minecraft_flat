# Game Design Document
My game will be a continuous survival game whose characters are based on the Minecraft characters (mobs)

## Characters
#### Player:
![Steve](/images/steve.png "Steve") The Player will be freely controlled by the mouse, independent of the game's speeding up.
#### Enemies:
+ ![Zombie](/images/zombie.png "Zombie") Zombies will move slowly, always toward the player.
+ ![Creeper](/images/creeper.png "Creeper") Creepers will move slightly faster toward the player and explode if they get close.
+ ![Spider](/images/spider.png "Spider") Spiders will move in a random direction and speed; there is a random chance that it will change directions again.
+ ![Skeleton](/images/skeleton.png "Skeleton") Skeletons will circle the player with a variable radius, set by the current distance between them and the player. with a random chance of switching directions.
+ ![Enderman](/images/enderman.png "Enderman") Endermen will teleport randomly in a limited radius, with a greater chance of teleporting toward the player.

#### Items:
+ ![Heart](/images/heart.png "Heart") Hearts will replenish the player's health.  These hearts will remain stationary.
+ ![Strength Potion](/images/potion_strength.png "Strength Potion") Strength Potions will grant the player invincibility for a limited amount of time, as displayed on the window's left.  They will move in small circles.


## Gameplay
The user will move the mouse to directly control the on-screen Player's position, avoiding the mobs for as long as possible.  The player has a maximum speed, and the player follows the mouse cursor.


## Score
The score continuously goes up.  The score increases by 100 when the player acquires a heart.  The final score is determined by the score's value when the player dies.


## Player's Lives
The player will have one life but multiple health points.  Different enemies will do different amounts of damage.


## User Interface
#### Screenshot:
![UI Screenshot](/images/GameDesignDoc_UIScreenshot.png "UI Screenshot")

#### User interface elements:
+ **New Game** button starts a new game, prompting the user first if a game is in progress
+ **Quit** button closes the game, prompting the user first if a game is in progress
+ **Pause** button pauses the game if one is in progress
+ Below the buttons is displayed the player's username, health, score, and invincibility status.
+ Below that is a list of the top 20 scores, which are saved between executions to the file passed in as a parameter when running.
+ The large region is the gameplay space
