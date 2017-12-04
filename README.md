Danmaku Arcana
==============
1v1 Bullet Hell VS

Controls
========
-------------------------------------------------------------
|   Input   |   Keyboard   |    XBox        |   PlayStation |
-------------------------------------------------------------
|   Move    |   WASD       |    D-Pad       |   D-Pad       |
|           |              |    Left Analog |   Left Analog |
|   A       |   Y          |    X           |   Square      |
|   B       |   U          |    Y           |   Triangle    |
|   C       |   I          |    RB          |   R1          |
|   D       |   O          |    LB          |   L1          |
|   E       |   H          |    A           |   Cross       |
|   F       |   J          |    B           |   Circle      |
|   G       |   K          |    RT          |   R2          |
|   H       |   L          |    LT          |   L2          |
-------------------------------------------------------------

Gameplay
========
Match Structure
---------------
At the beginning of a match, both players start on equal footing
The game will count down from 3, after which the player characters will begin clashing
When the initial clash is decided, the players will move into position and begin a round after a 3 count

Each round lasts a set duration indicated by the line in the center of the playfield

When a round is over, the players will move to their starting positions and initiate another clash
When a clash is resolved, the game will count down from 3 and begin another round

Clash Phase
-----------
The outcome of a clash is decided by holding up, down or neutral on the movement controls
High beats mid, mid beats low, low beats high

When clashing between rounds, players can hold left or right on the movement controls in order to alter their flight path
A clash will only occur if both players input the same direction
If no clash occurs or there is a draw, the players will swap sides
If the casting player wins a clash, their turn will be extended
If the shooting player wins a clash, they will attack their opponent for bonus damage

Battle Phase
------------
During battle, one player acts as the caster and the other as the shooter
The caster starts at the top of the playfield and uses bullet pattern attacks
The shooter starts at the bottom of the playfield and uses shot type attacks
The objective is to reduce your opponent's life bar to 0 by attacking them and avoiding damage

Each player has two card hands, one for casting and one for shooting
(At present, both players use fixed hands. In future these will be customizable.)
These are indicated by the grid below their life bar
The displayed hand will change based on whether you are in casting or shooting mode

Each card has a name, power cost and button label
It can only be activated if the player has sufficient power in reserve
Power is indicated by the blue bar beneath the health meter
To activate it, press the input corresponding to its button label

Notes
=====
No music yet
(The Touhou 8 soundtrack is a good backing while you play sets though - https://www.youtube.com/watch?v=buarznoa7ms&list=PL67F11CEA03E7FE5F&index=2)

No sound effects yet

Placeholder graphics, no visual effects yet
(I'm thinking 'set inside a computer' is an interesting / less-oft-used visual theme, ideas and input welcome!)

Features that are planned but not implemented:
-Customizable hands
-More card types (supplementary attacks for caster, movement, defense, 'card tricks' like time and bullet manipulation)
-Card 'schools' (limited subset of total cards, equivalent to characters/movesets in a traditional fighting game)
-More advanced card power system (patterns that don't last a whole round, cards that drain power over time, equip-time cost vs runtime cost)
-Bullet pattern warnings / startup animations
-Fighting game QoL features like win tracking and customizable rules
-Practice mode
-Extensive single-player card collecting campaign (HA HA HA maybe)

Online play is functional but imperfect:
-You may experience visual inconsistencies with certain player animations and countdown prompts
-Player collision is handled locally to maintain fairness, causing visual inconsistencies under high ping conditions