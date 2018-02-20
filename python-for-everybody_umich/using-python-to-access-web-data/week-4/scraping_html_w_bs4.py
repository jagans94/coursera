#   use the following links to test -
# http://py4e-data.dr-chuck.net/comments_42.html, http://py4e-data.dr-chuck.net/comments_29947.html
import urllib.request, urllib.parse, urllib.error
from bs4 import BeautifulSoup
import ssl

# Ignore SSL certificate errors
ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

url = input('Enter - ')
html = urllib.request.urlopen(url, context=ctx).read()
soup = BeautifulSoup(html, 'html.parser')

tags = soup('span')

total_sum = 0
for tag in tags:
    total_sum += int(tag.contents[0])

print(total_sum)