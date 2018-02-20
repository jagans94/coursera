#   Use the following as filename - mbox-short.txt
name = input("Enter file:")
if len(name) < 1 : name = "mbox-short.txt"
handle = open(name)

hour_count = dict()

for line in handle:
    words = line.strip().split()
    if words and words[0] == "From":
        hrs = words[5][0:2]
        hour_count[hrs] = hour_count.get(hrs,0) + 1

sorted_hour_count = sorted([(k,v) for (k,v) in hour_count.items()])

for (k,v) in sorted_hour_count:
    print(k,v)