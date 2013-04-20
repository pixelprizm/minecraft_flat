# Game Design Document
My game will be a continuous survival game whose characters are based on the Minecraft characters (mobs)

## Entities
#### Example of game characters:
![Minecraft Mobs](http://fc09.deviantart.net/fs71/f/2012/153/2/c/minecraft_mob_magnets_by_vandonovan-d51yxlt.jpg "Minecraft Characters")

Each character will move differently.  The Player (bottom-right in the above picture) will be freely controlled by the mouse, independent of the clock.
Enemies:
+ Zombies (top-middle) will move slowly, always toward the player.
+ Creepers (middle-left) will move slightly faster toward the player and explode if they get close.
+ Spiders (not pictured) will move toward the player fast.
+ Endermen (top-left) will teleport randomly in a limited radius, and never right on top of the player (but they can get close.)
+ Skeletons (top-right) will circle the player and shoot small projectiles at the player.
Additionally, there will be hearts that randomly appear, which will replenish the player's health.  These hearts will remain stationary.


## Gameplay
The user will move the mouse to directly control the on-screen Player's position, avoiding the mobs for as long as possible.


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












This is a place holder for your game design document. You are advised to write your document in [Markdown](http://daringfireball.net/projects/markdown/) and the following section will show you how to write a document using Markdown markup.

Alternativley, you can write your document in plain text if you wish.

----

## Markdown
Markdown is a human-readable structured plain text format that is used to convert text into HTML. GitHub automatically renders Markdown into HTML.

This is a crash course on how to use Markdown. The following section will show you the plain text used to generate the document shown in the rendering section.

### Code

```
# Header 1
## Header 2
### Header 3
#### Header 4
##### Header 5

You can also write in **bold** or _italics_. You can also ~~strike through~~ or write inline `Code Segments`

>Blockquotes are done as such.

Just make sure to separate paragraphs with an emptyline. 
Otherwise, they are considered in the same paragraph.

You link to [Google](https://www.google.com) as such and lists are written has follows:
  1. First you indent with two empty spaces.
  1. Then, you use:
    * `1.` to signal an ordered (i.e. numbered) list, or
    * `*`, `-`, `+` to represent an unordered list.
      1. Make sure to maintain indentation
      1. As it is used to identify sub-lists
  1. Numbering and symboles don't matter as they are auto-generated later.

Tables are pretty easy to make:

| Tables        | Are           | Easy          |
| ------------- |:-------------:| -------------:|
| left-aligned  | centered      | right-aligned |
| header are    | bolded and    | centered      |
| zebra stripes | are neat      | 1             |


Images are added inline by using the following syntax
![alt text](http://octodex.github.com/images/Professortocat_v2.png "Image Title")
```

----

### Rendering
This section shows the rendering of the plain text above.

# Header 1
## Header 2
### Header 3
#### Header 4
##### Header 5

You can also write in **bold** or _italics_. You can also ~~strike through~~ or write inline `Code Segments`

>Blockquotes are done as such.

Just make sure to separate paragraphs with an emptyline. 
Otherwise, they are considered in the same paragraph.

You link to [Google](https://www.google.com) as such and lists are written has follows:
  1. First you indent with two empty spaces.
  1. Then, you use:
    * `1.` to signal an ordered (i.e. numbered) list, or
    * `*`, `-`, `+` to represent an unordered list.
      1. Make sure to maintain indentation
      1. As it is used to identify sub-lists
  1. Numbering and symboles don't matter as they are auto-generated later.

Tables are pretty easy to make:

| Tables        | Are           | Easy          |
| ------------- |:-------------:| -------------:|
| left-aligned  | centered      | right-aligned |
| header are    | bolded and    | centered      |
| zebra stripes | are neat      | 1             |


Images are added inline by using the following syntax
![alt text](http://octodex.github.com/images/Professortocat_v2.png "Image Title")

