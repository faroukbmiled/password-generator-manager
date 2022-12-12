@echo off

echo Adding current folder to PATH...
setx PATH "%PATH%;%CD%"

echo Done!, type 'gen help' in your command to test it, To make the change to the PATH environment variable permanent,
echo you will need to modify the system environment variables. Here's how to do that in Windows:
echo 1- Open the Control Panel. You can do this by searching for Control Panel in the Start menu or
echo by pressing the Windows key + R to open the Run dialog, then typing Control Panel and pressing Enter.
echo 2- In the Control Panel, search for environment variables and click on the Edit the system environment variables button.
echo 3- In the System Variables section, scroll down to the PATH variable and click on Edit.
echo 4- In the Edit environment variable window, add the current folder to the PATH variable by clicking on New
echo and typing the path to the current folder (e.g., C:\myfolder). Click on OK to save your changes
echo and close the window. After making these changes, the current folder will be permanently added
echo to the PATH environment variable, and you will be able to run executables in the current folder
echo without specifying the full path. Keep in mind that these changes will apply to all future sessions,
echo not just the current one.
pause