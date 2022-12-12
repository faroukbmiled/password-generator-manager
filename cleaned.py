import random
import string
import json
import sys
from sys import argv
import webbrowser

def generate_password():
    password = ''.join(random.choices(string.ascii_letters + string.digits + '@$!%*?&', k=16))

    if not any(c.isupper() for c in password):
        password = password[:random.randint(0, 7)] + random.choice(string.ascii_uppercase) + password[random.randint(0, 7):]

    if not any(c.isdigit() for c in password):
        password = password[:random.randint(0, 7)] + random.choice(string.digits) + password[random.randint(0, 7):]

    if not any(c in '@$!%*?&' for c in password):
        password = password[:random.randint(0, 7)] + random.choice('@$!%*?&') + password[random.randint(0, 7):]

    return password

def save_password(password, passwordname):
    obj = {}
    try:
        obj = json.load(open("C:/Users/Administrator/passgen/password.json"))
    except:
        pass

    obj[passwordname] = password
    open("C:/Users/Administrator/passgen/password.json", "w").write(json.dumps(obj, sort_keys=True, indent=4, separators=(',', ': ')))

try:
    if argv[1] == 'rm':
        obj  = json.load(open("C:/Users/Administrator/passgen/password.json"))
        if argv[2] in obj:
            del obj[argv[2]]
        open("C:/Users/Administrator/passgen/password.json", "w").write(json.dumps(obj, sort_keys=True, indent=4, separators=(',', ': ')))
        exit()
    if argv[1] == 'help' or argv[1] == 'h':
        print('list of commands:\n \
        gen or gen number (will generate a 16 random password or generate depending on given number ,ex: gen 50)\n \
        gen s (asks you to put a number and saves it to a json file\n \
        gen rm (remove a password from the json file: ex gen rm facebook)\n \
        gen c or show (this will print all the passwords)\n \
        gen d (this will generate a password without promts if you provide 2 argumets ex: gen d 50 facebook)\n \
        gen n (this will generate a password depending on the given input)\n \
        gen o or open (this will open the json file that contains all the passwords)')
        exit()
    elif argv[1] == 'o' or argv[1] == 'open':
        webbrowser.open("C:/Users/Administrator/passgen/password.json")
        exit()

    if argv[1] == 'c' or argv[1] == 'show':
        with open("C:/Users/Administrator/passgen/password.json",)
