# TODO
def main():
    program()

def program():
    r=input("Inter the height")
    while(isInt(r)==False):
        r=input("Inter the height")

    h=int(r)
    while h<1 or h>8:
        h=int(input("Inter the height"))

    x=h-1
    for i in range(1,h+1):
        for s in range(x,0,-1):
            print(end=" ")
        for j in range(i):
            print("#",end="")
        print(end="  ")
        for j in range(i):
            print("#",end="")
        x-=1
        print()

def isInt(r):
    for i in range(len(r)):
        if (r[i].isdigit()==False):
            return False

    return True


main()





