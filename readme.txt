Hi, this is just a project from university that I thought I could upload here,
the game is executable from cmd, powershell and unix terminal (linux, MacOS)
although it is much more fluent in unix and it is advised to use that OS.
To play the game you just need to download the file from the release, then open your 
terminal (cmd, powershell, linux terminal, MacOS terminal), go inside the folder
where you have saved the game and use this command to compile it:
        $ gcc snake_lab -o snake

of course you need to have installed gcc on your system first, or MinGW if you are using Windows.
in that case the command to compile should be 
        $ g++ snake_lab -o snake

after the compiling is complete go ahead and type this to run the game:
        $ ./snake

to run the game, it will ask you to select from single player (WASD) or AI (you just watch it completed
the mazes), after that you'll have to copy-paste one of the mazes in the file "test_matrix.txt"
be sure to paste the 2 numbers before the maze, those are the columns and rows of the maze and are still
required for the game to work. if you paste something other than that you could run into some problems,
for anything just close the terminal, or try ctrl+./command+. 
You can also generate the mazes from a website or make them yourself, the important thing is that
you type in the column and rows first (in this order) and for the maze to be recognised properly you
need to use this format:
# = wall; $ = coin; ! = obstacle; o = start; _ = finish; T = drill;
Once you complete one maze the game closes so you'll have to restart it with the command.
Hope it's fun to try!
:)