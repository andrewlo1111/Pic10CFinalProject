# Pic10CFinalProject

PIC10C Game
Variation of a turn based war game. In this game, using food and gold resources, a player must build an army to conquer their opponent.
Villagers are used to build buildings that will get you resources.

 -Mines: provide 100 gold per end turn

-Farms: provide 100 food per end turn

-town center: provide 50 gold and 50 food per end turn

Warriors have 1 attack and 1 defense.
Archers have .75 attack and 1.5 defense.
Knights have 2 attack and .75 defense.
 
 Battle:
 - if attacker's attack is higher than defender's defense then attacker wins battle
 - equal or lower attack results in defender wins battle
 
 In each turn, player gets 3 total moves they can expend however they want
 
 
 This game is created using Qt Creator. 
 Resources used:
 1. Use of Stacked Widget
 https://doc.qt.io/archives/qt-4.8/qstackedwidget.html#addWidget
 
 https://doc.qt.io/archives/qt-4.8/qstackedwidget.html#currentIndex-prop
 
 2. Use of QButtonGroup
 https://doc.qt.io/archives/qt-4.8/qbuttongroup.html
 
 https://doc.qt.io/archives/qt-4.8/qbuttongroup.html#addButton
 
 https://doc.qt.io/archives/qt-4.8/qbuttongroup.html#buttonClicked-2
 
 3. QPainter/QImage 
 https://doc.qt.io/qt-5/qpainter.html
 https://www.qtcentre.org/threads/62995-QImage-and-drawImage-method
 
 4. QPaintEvent
 http://zetcode.com/gui/qt5/painting/
 
 5. QFont
 https://www.qtcentre.org/threads/14783-QFont-setPointSize()-does-not-take-effect
 
 6. QLabel
 https://doc.qt.io/qt-5/qlabel.html#alignment-prop
 
 https://doc.qt.io/Qt-5/qt.html#AlignmentFlag-enum
 
 7. QComboBox
 https://doc.qt.io/Qt-5/qcombobox.html#addItems
 
 8. Qt Key
 https://doc.qt.io/qt-5/qt.html#Key-enum
 
 
 
Progress throughout the project:

 At the very start of the project, it was rather simple as I just created basic classes that laid down the foundation for what encompass
 the basic concepts of the game such as unit stats and the existence of units and buildings. Units have the ability to simply move and attack with their own unique set of attack and defense stats. Therefore, the base class unit was used while the villager with its unique build function, warrior, archer, and knight inherited these aspects. The building class was similar with the town center, mine, and farm class inheriting it. However, this class was later removed as it proved to be useless. The player class was created to keep track of all the things the player controls in the game. 
 
 Then, a control window was created in the main file which displayed the amount of resources that a player has. Since this is a two player game, I felt that a stacked widget would allow me to freely go between the control windows for each player. However, when researching the change current index slot for stacked widgest to alternate between windows for player 1 and player two, I realized that I could not successfully connect a QPushButton with the clicked signal with the change index slot for the stacked widget object. In order to combat this problem, I looked into the QButtonGroup and was able to group two push buttons together to allow for the changing of stacked widgets. 
 
 Afterwards, I wrote the update slots for the different resources and buildings. In order to use the update slots in conjunction with the update label slots that would accompany the changes with the update resources, the mainwindow class would need to have access to the control window. As a result, I transferred everything related to the control window from the main file into the constructor of the mainwindow. 
 
 The next task was to create a train unit button that would be used for each specific player. Initially, I was unable to push back the variety of units into the unit list of each player. This was resolved by adding the keyword public in front of "unit" when inheriting the properities of unit into the warrior, archer, and knight class. At this time, I also decided to readjust the display of the control window. I looked into QFont and also QLabel to figure out how to change the alignment and the size of the text for the labels. The final aspect to the training unit required selecting which unit would be trained. I decided to use a QComboBox to prevent the possibility of any input errors. 
 
 In order to see the results of the actions taken and allow a user to interact with the game I was created, it was crucial that I be able to use the paintEvent function. Initially, I was unable to paint anything. After looking into the example of another use of QPaintEvent, I realized that I had named the private function drawMap, but it must still be named paintEvent as it is being overloaded so I simply renamed the function name and I was able to successfully paint the event. 
 
 Next, I continued to expand on my train unit functionality establishing villager as the default. I created a unit count label with the ability to update and also attempted to draw an image I downloaded to represent the unit I trained. I looked into examples on the use of downloading an image, but for some reason, my attempts did not lead to the drawing of an image so I moved on. The exact location to which the unit would be drawn at would be decided in the space it fills in a 6 x 6 game board array that represent the rows and columns. However, I was unable to successfully draw an image. My workaround was simply using simple things that QPainter could already draw. I used a filled in circle to represent a town center and letters to correspond to the unit or building created. 
 
 One of the problems with the game board was that they only represented the unit or building type. However, it did not reflect who had control of the unit. I felt that it would be too long of an enumeration declaration if I established each unit and building type with their own player one and player two version. In order to solve this issue, I decided to make a 6x6 array similar to the game board array but instead this one would simply indicate whether the spot was occupied by player one, player two and none. The 6 x 6 arrays were synced up so a given row and column could provide information concerning the unit or building type from the game board and who owns that specific unit using the player indicator. 
 
 As I reviewed some of my code, I felt that I could optimize some of the more repetitive aspects. For example, instead of just manually adding items into the combo box for training units, I decided to use a lambda function for both player one and player two select unit boxes. There were several reasons for this. We had just learned about how to use lambda functions so I wanted to try to apply what I had just learned. Even though afterwards I learned of bind functions, I still decided to continue with a lambda function here. This is because the function was used only twice and although lambda functions are typically used only once, writing a completely separate function just for a simple for loop seemed unnecessary. In addition, writing another function would mean having to go through the trouble of scrolling to find the exact location for such a short and simple function. 
 
 With a variety of units available for use for a given player, I realized that using a simple key press event would not be sufficient as it would not be clear as to which unit should move. As a result, I introduced both a selected and cursor aspect to the board. The cursor is denoted by a yellow square and a selected spot is denoted by a green square. The cursor is free to move around and when pressing the enter key to a location owned by the player whose turn it is, the selected spot will move to where the cursor is. For the selected unit, you can move left, right, up, or down as long as it does not make the unit go off the board. At first, it started through a set of move buttons, but was later expanded to allow for the arrow keys to improve ease of use.
 
 The villager class is unique compared to the other units in that it has the ability to build. As a result, I created a window that is displayed only when the villager is selected. This window gives the choice to move or build. If move is clicked, then the window closes and moving is normal for the villager. However, if one of the build buttons is clicked, the corresponding building is created at the location in which the cursor is located. The building will only be built if the cursor is adjacent to the unit. 
 
 In order to speed up the pace of the game I decided to introduce a move count. For each given turn, a player gets 3 moves. It will then  reset at the end of the turn. This move count was something that the player should be able to see so I added it to the display window. While adding in the move count, I realized that the unit count was essentially useless as anybody could ese how many units they actually had, so I replaced the location where the unit count lable was with the move count. 
 
 Now, the last significant aspect of the game needed to be completed was the battle between units. Instead of giving the player the choice to start a battle through a button, I felt that it would streamline movement if battle was just initiated through moving to a spot where the other player's unit is. This helped simplify code since I would not have to create another pop up window and it also reduced the number of actions a user needs to battle an enemy.
 
 After the battle aspect of the game was completed, I decided to also add a commentary window. The main purpose of this window was for the user to know what was done, but it was also useful as a debugging mechanism. The commentary window lets me know whether a specific action is completed and so if something goes differently in the game than expected, I can trace back to the specific part needed to ease my troubleshooting process. In order to have one single line, that is just constantly changing depending on the action, I made QLabel one of my private variables ensuring that scope was maintained within the class and that I would not have to constantly make a new QLabel object. For example, this led me to realize that there was no restrictions when it came to creating buildings.
 
 Overall, I was able to achieve almost all my goals in constructing this game with the exception of using images to represent the various units and buildings which I simply replaced with letters. 
 
 Takeaways:
 From this project, one of the most important things I learned was to have a clear idea and plan of what my project is going to look like. For certain aspects when I did not know how to truly integrate certain aspects, I blindly wrote the code without any concern for its future implications. This led to a lot of extraneous code that ultimately wasted my time. In addition, I realized the importance of having a good sense of organization for code as when projects get extremely long, they can be difficult to manage. I also ended up developing a lot of practice in reading documentation. Since I was exploring a lot of new functions or classes from Qt that were not taught in class, I had to use the qt website and read its documentation to get an understanding of the function and how to apply it to my code. 
