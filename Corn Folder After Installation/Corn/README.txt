How to install Corn:
1. Run setup.bat as administrator (won't work otherwise)
   If it asks to press any key, just do so
   Corn will be installed in the same directory as setup.bat
2. Run check.bat to make sure both the C++ and Corn compilers are Working
*3. Open Notepad++ and go to Language > Define your language > Import > Select Corn.xml from the Notepad++ Colors directory

To create a new project:
1. Shift+RClick and select "Open Command window here"
2. "corn create ProjectName"


To compile a project, navigate inside the project folder.
"corn main.corn YourProgramName"	compiles the program
"corn main.corn YourProgramName -r"	compiles and runs the program