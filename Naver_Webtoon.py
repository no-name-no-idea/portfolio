from bs4 import BeautifulSoup as bs
from pprint import pprint
import requests

html = requests.get('https://comic.naver.com/webtoon/weekday.nhn')
# pprint(html.text)

soup = bs(html.text,'html.parser')

All_data = soup.findAll('div',{'class':'col_inner'})
# pprint(Mon_data)

week_title_list = []

for ALL in All_data:
    Title_data = ALL.findAll('a',{'class':'title'})
    #pprint(Title_data)

    title_list = [t.text for t in Title_data]
    week_title_list.append(title_list)

pprint(week_title_list)

