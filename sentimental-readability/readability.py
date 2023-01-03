from cs50 import get_string

# returs number of letters


def count_letters(text):
    n_l = 0
    i = 0
    length_text = len(text)

    # check the number of letters
    while (i < length_text):
        curr_letter = ord(text[i])
        if ((curr_letter >= 65 and curr_letter <= 90) or (curr_letter >= 97 and curr_letter <= 122)):
            n_l += 1
        i += 1
    return n_l

# returs number of words


def count_words(text):
    n_w = 0
    i = 0
    length_text = len(text)

    # check the number of words
    while (i < length_text):
        curr_letter = text[i]
        if (curr_letter.isspace() == True):
            n_w += 1
        i += 1
    n_w += 1  # 54 whitespaces, meaning 55 words
    return n_w

# returs number of sentences
# I add morre comments to pass the style50


def count_sentences(text):
    n_s = 0
    i = 0
    length_text = len(text)

    # check the number of sentences
    while (i < length_text):
        curr_letter = ord(text[i])
        if (curr_letter == 46 or curr_letter == 33 or curr_letter == 63):
            n_s += 1
        i += 1
    return n_s


# initialitzations
text_user = get_string("Text: ")
c_l = count_letters(text_user)
c_w = count_words(text_user)
c_s = count_sentences(text_user)
letters = float(c_l)
words = float(c_w)
sentences = float(c_s)

step = 0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8
index = round(step)

if (index < 1):
    print("Before Grade 1", end="")
elif (index > 16):
    print("Grade 16+\n", end="")
else:
    print(f"Grade {index}", end="")