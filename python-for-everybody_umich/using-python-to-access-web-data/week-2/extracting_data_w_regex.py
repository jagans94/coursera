#   Use the following filenames to test -
#   small.txt (27486), sample.txt (445822), actual.txt (315492)
import re

fn = input("enter filename: ")
fh = open(fn, 'r')

'''
print( sum( [ int(i) for i in re.findall('[0-9]+', fh.read().strip()) ] ) )
'''

text = fh.read().strip().split()

#count = 0
total_sum = 0
for word in text:
    if re.search('[0-9]+', word):
        result = [int(numbers) for numbers in re.findall('[0-9]+', word)]
        #count += len(result)
        total_sum += sum(result)

print(total_sum)