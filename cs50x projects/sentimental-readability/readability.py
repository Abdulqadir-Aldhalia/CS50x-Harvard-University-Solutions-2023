# TODO
#get input text
def main():
    text = input("Enter your text ")

    while(len(text) == 0):
        text = input("Enter your text")
#run the funtion
    letters = calculate_letters(text)
    words = calculate_words(text)
    sentences = calculate_sentences(text)
#run the calculation
    letter_count = 0.0588 * float(letters) / words * 100
    sentence_count = 0.296 * float(sentences) / words * 100
    index = letter_count - sentence_count - 15.8
    grade = round(index)
    # output
    if grade < 1:
        print("Before Grade 1")
    elif 16 <= grade:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")

def calculate_letters(text):
    letters = 0
    for i in range(len(text)):
        if text[i].isalpha() :
            letters += 1
    return letters

def calculate_words(text):
    words = 1
    for i in range(len(text)):
        if text[i].isspace() :
            words += 1
    return words

def calculate_sentences(text):
    sentences = 0
    for i in range(len(text)):
        if text[i] == '.' or text[i] == '!' or text[i] == '?' :
            sentences +=1
    return sentences

main()




