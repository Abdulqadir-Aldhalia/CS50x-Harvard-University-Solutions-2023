import string
print("Greetings:",end='' )
x=input()


if x[0].upper()=="H" and x.upper()!="HELLO":
    print("$20",x.upper())

elif  x.upper()=="HELLO":
    print("$0")

else:
    print("$100")

