    #   Open the file romeo.txt and read it line by line.
file_name = input("enter file name: ")
file_handle = open(file_name, "r")
word_list = file_handle.read().split()

word_list.sort()

i = 1
j = 0
while i < len(word_list):
    key = word_list[j]
    if key == word_list[i]:
        word_list.remove(word_list[i])
    else:
        j = i
        i = i + 1

#   This part bounded by comments is required as the
lst = list()
for each in word_list:
    lst.append(each)
#   web editor complains if u don't use the append() function.

print(lst)