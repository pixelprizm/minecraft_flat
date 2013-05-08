# Game Design Document
My game will be a continuous survival game whose characters are based on the Minecraft characters (mobs)

## Game characters:
![Steve](/images/steve.png "Steve") The Player will be freely controlled by the mouse, independent of the game's speeding up.
##### Enemies:
+ ![Zombie](/images/zombie.png "Zombie") Zombies will move slowly, always toward the player.
+ ![Creeper](/images/creeper.png "Creeper") Creepers will move slightly faster toward the player and explode if they get close.
+ ![Spider](/images/spider.png "Spider") Spiders will move in a random direction and speed; there is a random chance that it will change directions again.
+ ![Skeleton](/images/skeleton.png "Skeleton") Endermen will teleport randomly in a limited radius, with a greater chance of teleporting toward the player.
+ ![Enderman](/images/enderman.png "Enderman") Skeletons will circle the player with a random chance of switching directions.
##### Items:
+ ![Heart](/images/heart.png "Heart") Hearts will replenish the player's health.  These hearts will remain stationary.
+ ![Strength Potion](/images/potion_strength.png "Strength Potion") Strength Potions will grant the player invincibility for a limited amount of time, as displayed on the window's left.  They will move in small circles.


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
