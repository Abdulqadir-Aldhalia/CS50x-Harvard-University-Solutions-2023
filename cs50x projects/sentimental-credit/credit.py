
from cs50 import get_int


def main():
    # Prompts user for card number
    number = get_int("Number: ")

    # If card is valid, then check the card company
    if check_valid(number):
        card_Type(number)
    # Card not valid
    else:
        print("INVALID")


def check_valid(num):
    # Calculates sum according to Luhn's Algorithm
    sum = 0
    for i, c in enumerate(reversed(str(num))):
        if i % 2 == 0:
            sum += int(c)
        else:
            for j in str(int(c) * 2):
                sum += int(j)

    # Checks if sum is divisible by 10
    if sum % 10 == 0:
        return True
    else:
        return False


def card_Type(card):
    # Removes all the digits from card number except first 2
    num = int(str(card)[0:2])

    # Check for conditions of all companies
    if (num == 34 or num == 37) and len(str(card)) == 15:
        print("AMEX")
    elif num > 50 and num < 56 and len(str(card)) == 16:
        print("MASTERCARD")
    elif num >= 40 and num < 50 and (len(str(card)) == 13 or len(str(card)) == 16):
        print("VISA")
    else:
        print("INVALID")


main()




# def main():

#     num=input("please enter the number")

#     while checkInput(num)==False:

#             num=input("please enter correct nuber")


#     if checkSum(num):
#         if checkCredit(num)==0:
#             print("AMEX")
#         if checkCredit(num)==1:
#             print("MASTERCARD")
#         if checkCredit(num)==2:
#             print("VISA")

#     print("INVALID")


# def checkSum(num):
#     le=len(num)
#     sum=0
#     sum2=0

#     for i in range(le-2,0,-2):
#         temp=(int(num[i]))*2
#         while(temp%10!=temp):
#             n=temp%10
#             sum+=n
#             temp/=10

#     for j in range(le-1,0,-2):
#         sum2+=int(num[j])

#     result=sum+sum2
#     if(result%10==0):
#         return True
#     else:
#          return False

# def checkCredit(num):
#     le=len(num)

#     if int(num[0])==3 and int(num[1])==7 and le==15:
#         if int(num[0])==3 and int(num[1])==4 and le==15:
#            return 0

#     if (int(num[0])==5 and int(num[1])==1 and le==16):
#         if(int(num[0])==5 and int(num[1])==2 and le==16):
#            if(int(num[0])==5 and int(num[1])==4 and le==16):
#                if(int(num[0])==5 and int(num[1])==5 and le==16):
#                      return 1

#     if (int(num[0])==4 and le==13):
#         if(int(num[0])==4 and le==16):
#             return 2
#     return 400




# def checkInput(num):
#  c=False
#  for i in range(len(num)):
#          if num[i].isdigit()==True:
#              c=True
#          else:
#              c= False
#              return c
#  return c



# main()


