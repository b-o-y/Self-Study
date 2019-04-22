#! /usr/bin/python3
import sys

def count_words(data):
    words = data.split(" ")
    return len(words)

def count_lines(data):
    lines = data.split("\n")
    for l in lines:
        if not l:
            lines.remove(l)
    return len(lines)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python word_count.py <file>")
        exit(1)
    f = open(sys.argv[1], "r")
    data = f.read();
    f.close();
    
    print("The number of words: ", count_words(data))
    print("The number of lines: ", count_lines(data))
