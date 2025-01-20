# Ryzen_Auto_Master

Program to automatically start AMD Ryzen Master software and apply either Profile 1 or Profile 2

"Ryzen Master for Ryzen 3000 series and newer" supported only!(Second version would need tweaking the click counts)

## Usage

-Modify the path in main.cpp to the path of the Ryzen Master executable.

-Build using Visual Studio.

-Launch the executable with argument 1 for Profile 1, argument 2 for Profile 2, no argument for default which is Profile 1.

-You can create a task in windows Task Scheduler for this executable to run on user login.

-Make sure Ryzen Master is in advanced mode and your profiles are setup correctly

## How it works

1. Launch the Ryzen Master software
2. Click ok on pop up window
3. Use TAB and Enter to navigate the main menu
4. Apply the selected profile
5. Close Ryzen Master

