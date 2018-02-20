# Use the file name mbox-short.txt as the file name
fname = input("Enter file name: ")
fh = open(fname)
zop = 0.0
count = 0
for line in fh:
    if not line.startswith("X-DSPAM-Confidence:") : continue
    pos = line.find('0')
    zop = zop + float(line[pos:].strip())
    count = count + 1
print("Average spam confidence:",zop/count)
