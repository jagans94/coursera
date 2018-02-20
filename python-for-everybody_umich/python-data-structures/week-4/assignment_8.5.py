#   Open the file mbox-short.txt and read it line by line
fname = input("Enter file name: ")
if len(fname) < 1 : fname = "mbox-short.txt"

fh = open(fname, "r")
count = 0

for each_line in fh:
    line = each_line.strip().split()
    if line and line[0] == 'From':
        print(line[1])
        count = count+1

print("There were", count, "lines in the file with From as the first word")
