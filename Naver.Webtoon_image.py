from urllib.request import urlretrieve

from bs4 import BeautifulSoup as bs
from pprint import pprint
import requests, re

html = requests.get('https://comic.naver.com/webtoon/weekday.nhn')
# pprint(html.text)

soup = bs(html.text, 'html.parser')

All_data = soup.findAll('div', {'class': 'col_inner'})
# pprint(Mon_data)

li_list = []

for ALL in All_data:
    li_list.extend(ALL.findAll('li'))

# pprint(li_list)

for li in li_list:
    img = li.find('img')
    title = img['title']
    img_src = img['src']
    # print(title, img_src)
    title = re.sub('[^0-9a-zA-Zㄱ-힗]', '', title)
    urlretrieve(img_src, title + '.jpg')
