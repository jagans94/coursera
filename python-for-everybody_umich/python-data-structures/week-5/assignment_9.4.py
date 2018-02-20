#   use the following as file name - mbox-short.txt
name = input("Enter file:")
if len(name) < 1 : name = "mbox-short.txt"
handle = open(name)

countOfCommits =dict()
maxCommits = None
maxCommitsByPerson = None

for line in handle:
    text = line.strip().split()
    if text and text[0] == 'From':
        countOfCommits[text[1]] = countOfCommits.get(text[1],0) + 1
        if maxCommits == None or maxCommits <= countOfCommits[text[1]]:
            maxCommits = countOfCommits[text[1]]
            maxCommitsByPerson = text[1]
print(maxCommitsByPerson,maxCommits)