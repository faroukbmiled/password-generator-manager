import random
import string
import json
import os
from sys import argv
import webbrowser
import datetime

json_fname = 'password.json'

json_history = 'history.json'

json_loc = os.path.dirname(__file__)+f"\{json_fname}"

cache_temp = os.path.dirname(__file__)+f"\{json_history}"

if not os.path.exists(json_fname):
    with open(json_fname, "w") as file:
        data = {}
        json.dump(data, file)
elif not os.path.exists(cache_temp):
     with open(cache_temp, "w") as file:
        data = {}
        json.dump(data, file)
else:
    pass

try:
    try:
        try:
            if argv[1] == 'rm':
                obj  = json.load(open(json_loc))
                if argv[2] in obj:
                    del obj[argv[2]]
                open(json_loc, "w").write(json.dumps(obj, sort_keys=True, indent=4, separators=(',', ': ')))
                exit()
            if argv[1] == 'rmsh':
                os.remove(cache_temp)
                exit()
            if argv[1] == 'help' or argv[1] == 'h':
                print('list of commands:\n \
                gen or gen number (will generate a 16 random password or generate depending on given number ,ex: gen 50)\n \
                gen s (asks you to put a number and saves it to a json file\n \
                gen rm/rmsh (remove a password from the json file: ex gen rm facebook, rmsh will remove json history file)\n \
                gen c or show (this will print all the passwords)\n \
                gen d (this will generate a password without promts if you provide 2 argumets ex: gen d 50 facebook)\n \
                gen n (this will generate a password depending on the given input)\n \
                gen f or find (this will find a password/value for the given name/key)\n \
                gen -s or -s number(this will generate a password for a given number without symbols, ex: gen -s 50/ gen -s 50 facebook\n \
                gen n (this will generate a password depending on the given input)\n \
                gen sh/history (show generated password history that wasnt saved/ generated with gen/ gen number)\n \
                gen o or open or oh/showhistory (this will open the json file that contains all the passwords)')
                exit()
            elif argv[1] == 'o' or argv[1] == 'open':
                webbrowser.open(json_loc)
                exit()
            elif argv[1] == 'oh' or argv[1] == 'showhistory':
                webbrowser.open(cache_temp)
                exit()

        except IndexError:
            pass
    except UnboundLocalError or IndexError:
        pass


    try:
        if argv[1] == 'c' or argv[1] == 'show':
            with open(json_loc, 'r') as f:
                contents = f.read()
            print (contents)
            exit()
        if argv[1] == 'sh' or argv[1] == 'history':
            with open(json_history, 'r') as f:
                contents = f.read()
            print (contents)
            exit()
        if argv[1] == 'f' or argv[1] == 'find':
            with open(json_loc, 'r') as f:
                contents = f.read()
                try:
                    p = json.loads(contents)[argv[2]]
                    print (p)
                except KeyError:
                    print('invalid key, try another password name or use gen c to show all')
            exit()
        else:
            pass

    except UnboundLocalError:
        print("please provide another arguments for the desired password")
        exit()
    except IndexError:
            pass

    def generate_password():
        global passwordname
        symlbols = string.punctuation
        try:
            if argv[1] == 'd':
                num = argv[2]
                passwordname = argv[3]
            if argv[1] == 's':
                num = input('num of characters: ')
                if len(num) == 0:
                    num = 16
                passwordname = input('save pass as: ')
            if argv[1] == 'n':
                num = input('num of characters: ')
            if argv[1].isdigit():
                passwordname = None
                num = argv[1]
            else:
                pass
            if argv[1] == '-s':
                symlbols = ""
                num = 16
                passwordname = None
                if len(argv) > 2:
                    num = argv[2]
                    passwordname = None
                if len(argv) > 3:
                    num = argv[2]
                    passwordname = argv[3]
        except IndexError:
            num = None
            passwordname = None
        if len(argv) > 1:
            check = int(num)
        else:
            check = 16

        allowed_chars = string.ascii_letters + string.digits + symlbols

        password = "".join(random.choice(allowed_chars) for _ in range(check))

        return password

    password = generate_password()

    print(password)

    try:
        if passwordname != None:
            with open(json_loc, "r") as f:
                data = json.load(f)
            if len(passwordname) == 0:
                print('please enter a name to save')
                exit()
            else:
                data[passwordname] = password
            with open(json_loc, "w") as f:
                json.dump(data, f, indent=4)
        else:
            with open(cache_temp, "r") as f:
                data = json.load(f)
                now = datetime.datetime.now()
                dateformat = now.strftime("%H:%M:%S")
                data[dateformat] = password
            with open(cache_temp, "w") as f:
                json.dump(data, f, indent=4)
    except NameError:
        pass
except UnboundLocalError:
    print("please provide another arguments for the desired password or use 'gen h or gen help' to see available commands")
