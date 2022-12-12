# python-password-generator-manager
a simple password generator but intended to be used as a windows command, it also manage generated passwords

req: python3

1- run setup.cmd to add current folder as an env in windows (temporary) </br>
2- type gen h or gen help to see available commands

ps: to make the command permanent follow these steps:
* Open the Control Panel. You can do this by searching for Control Panel in the Start menu or 
by pressing the Windows key + R to open the Run dialog, then typing Control Panel and pressing Enter. 
* In the Control Panel, search for environment variables and click on the Edit the system environment variables button. 
* In the System Variables section, scroll down to the PATH variable and click on Edit. 
* In the Edit environment variable window, add the current folder to the PATH variable by clicking on New 
and typing the path to the current folder (e.g., C:\myfolder). Click on OK to save your changes 
and close the window. After making these changes, the current folder will be permanently added 
to the PATH environment variable, and you will be able to run executables in the current folder 
without specifying the full path. Keep in mind that these changes will apply to all future sessions, 
not just the current one.

current commands:
list of commands:\n \
```
                gen or gen number (will generate a 16 random password or generate depending on given number ,ex: gen 50) </br>
                gen s (asks you to put a number and saves it to a json file </br>
                gen rm/rmsh (remove a password from the json file: ex gen rm facebook, rmsh will remove json history file) </br>
                gen c or show (this will print all the passwords) </br>
                gen d (this will generate a password without promts if you provide 2 argumets ex: gen d 50 facebook) </br>
                gen n (this will generate a password depending on the given input) </br>
                gen f or find (this will find a password/value for the given name/key) </br>
                gen -s or -s number(this will generate a password for a given number without symbols, ex: gen -s 50/ gen -s 50 facebook </br>
                gen n (this will generate a password depending on the given input) </br>
                gen sh/history (show generated password history that wasnt saved/ generated with gen/ gen number) </br>
                gen o or open or oh/showhistory (this will open the json file that contains all the passwords) </br>
                testing:\n\t\tgen enc/encrypt or gen dec/decrypt (this will encrypt and decrypt one of the passwords json files, </br>
                params: h/history for history passwords, s/saved for saved passwords, full example gen enc h --> this will encrypt the whole json values </br>
                ```
