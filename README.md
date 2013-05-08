# Game Programming Assignment Repository
### Student Information
  + Name: Eric Gauderman
  + USC email: gauderma@usc.edu
  + USC ID: 2865 5123 61

### Game Information
  + Game Name: Minecraft Flat!
  + Game Description: A top-down endless survival game.
  + [Game Design Doc](GameDesignDoc.md)


### Compile & Run Instructions
The grader should use the following procedure to compile and run the code:
#### Compile Instructions
```shell
qmake -project
qmake
make
```
#### Doxygen Instructions
```shell
doxygen -g config.txt
doxygen config.txt
firefox html/index.html
```
#### Command to run
For a pre-filled list of high scores:
```shell
./game_gauderma example_scores.txt
```
For a new, empty list of high scores:
```shell
./game_gauderma scores.txt
```
