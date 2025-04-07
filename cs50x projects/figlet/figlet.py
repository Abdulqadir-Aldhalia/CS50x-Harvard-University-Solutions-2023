from pyfiglet import Figlet
import sys



if sys.argv[1]in ["-f","--f"]:
    s=input("Input:")
    try:
        f = Figlet(font=sys.argv[2])
    except:
        print("worng font name")
    print (f.renderText(s))
else:
    print("wrong input")
    sys.exit()

