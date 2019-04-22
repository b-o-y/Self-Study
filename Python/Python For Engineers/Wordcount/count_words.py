#!/usr/bin/python3

f = open("words.txt", "r")
data = f.read()
f.close()
words = data.split(" ")
# print("The words in the text file are: ")
# print(words)
print("the number of words is ", len(words))
lines = data.split("\n")
# print("Lines of text are: ")
# print(lines)

for l in lines:
    if not l:
        lines.remove(l)
print("Number of lines ", len(lines))

