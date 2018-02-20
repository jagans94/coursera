#   use the following urls to test -
#   http://py4e-data.dr-chuck.net/comments_42.json (2553),
#   http://py4e-data.dr-chuck.net/comments_29950.json (2519)
import urllib.request, urllib.parse, urllib.error
import json

address = input('Enter location: ')
print('Retrieving', address)
uh = urllib.request.urlopen(address)
data = uh.read()
print('Retrieved', len(data), 'characters')
info = json.loads(data.decode())

print("Count:", len(info['comments']))
print("Sum:", sum([int(i['count']) for i in info['comments']]))
