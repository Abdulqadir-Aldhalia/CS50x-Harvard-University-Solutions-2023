import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3 :
        print("wrong input")
        sys.exit(1)

    STRS = []
    DataBase = []

    # TODO: Read database file into a variable
    try :
        with open(sys.argv[1]) as profile :
            Reader = csv.DictReader(profile)
            STRS = Reader.fieldnames[1:]
            for row in Reader:
                # Add person to profiles
                DataBase.append(row)
    except :
        print("could not open the first file")

    # TODO: Read DNA sequence file into  variable
    try :
        with open(sys.argv[2]) as seq :
            dna = seq.read()
    except :
        print ("could not open the second file")

    # TODO: Find longest match of each STR in DNA sequence

    STRs_count = dict.fromkeys(STRS, 0)

    for STR in STRS:
        STRs_count [STR] = longest_match(dna, STR)

    # TODO: Check database for matching profiles
    for person in DataBase :
        match_count = 0

        for STR in STRS:
            if int(person[STR]) != STRs_count[STR]:
                continue
            match_count += 1

        if match_count == len(STRS):
            print(person["name"])
            exit(0)

    print("No match")
    exit(1)

def longest_match(sequence, subsequence):
    # Number of bases in Short Tandem Repeat
    length = len(subsequence)

    longest_repeats = 0
    for i in range(len(sequence)):
        # Initialise and reset repeat counter
        repeats = 0

        if sequence[i: i + length] == subsequence:
            # Account for first match
            repeats += 1
            # Keep adding to count for consecutive repeats
            while sequence[i: i + length] == sequence[i + length: i + (2 * length)]:
                repeats += 1
                # Shift reading frame (value of i resets in for loop so we can update it here)
                i += length

        # Update max count if current repeat steak is greater than max
        if repeats > longest_repeats:
            longest_repeats = repeats

    return longest_repeats


main()









