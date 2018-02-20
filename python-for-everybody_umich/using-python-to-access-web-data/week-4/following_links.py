#   use the following links to test -
#   http://py4e-data.dr-chuck.net/known_by_Fikret.html,
#   http://py4e-data.dr-chuck.net/known_by_Dakotah.html

import urllib.request, urllib.parse, urllib.error
from bs4 import BeautifulSoup
import ssl

# Ignore SSL certificate errors
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

url = input('Enter URL: ')
count = input('Enter count: ')
position = input('Enter position: ')

print("Retrieving:", url)

for i in range(int(count)):
    html = urllib.request.urlopen(url, context=ctx).read()
    soup = BeautifulSoup(html, 'html.parser')
    tags = soup('a')
    url = tags[int(position)-1].get('href', None)
    print("Retrieving:", url)