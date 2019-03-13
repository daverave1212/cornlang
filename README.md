# Corn : A python-like language which compiles to C++
How to install Corn:
0. Clone the repository on your Windows 7/10 machine.
To install he actual compiler, go to 'Corn Folder After Instalation' and copy the 'Corn' folder somewhere else, prefferably to a location where it has read/write privileges. This will be the Corn folder. You can delete all other files you downloaded.
Note: you can keep the Corn Compiler/src if you wish to view the source code
1. Run setup.bat as administrator (won't work otherwise)
   If it asks to press any key, just do so
   Corn will be installed in the same directory as setup.bat
2. Run check.bat to make sure both the C++ and Corn compilers are Working
*3. Open Notepad++ and go to Language > Define your language > Import > Select Corn.xml from the Notepad++ Colors directory
Also, change your Notepad++ font to Consolas because the default font is shittt

To create a new project:
1. Shift+RClick and select "Open Command window here" or navigate to a folder with 'cd'
2. "corn create ProjectName"


To compile a project, navigate inside the project folder.
"corn main.corn YourProgramName"	compiles the program
"corn main.corn YourProgramName -r"	compiles and runs the program

You should probabily read Documentation of Corn
