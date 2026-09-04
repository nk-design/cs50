def main():
    text = input("Text: ")

    letters = sum(c.isalpha() for c in text)
    words = len(text.split())
    sentences = sum(text.count(c) for c in ".!?")

    L = letters / words * 100
    S = sentences / words * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
