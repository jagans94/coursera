#   use the following files to test -
#   http://py4e-data.dr-chuck.net/comments_42.xml (2553),
#   http://py4e-data.dr-chuck.net/comments_29949.xml (2639)

import urllib.request, urllib.parse, urllib.error
import xml.etree.ElementTree as ET

address = input('Enter location: ')
print('Retrieving', address)
uh = urllib.request.urlopen(address)
data = uh.read()
print('Retrieved', len(data), 'characters')
tree = ET.fromstring(data)

counts = tree.findall('.//count')
print("Count",len(counts))
print("Sum:", sum([int(i.text) for i in counts ]))
