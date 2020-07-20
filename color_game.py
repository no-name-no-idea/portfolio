from selenium import webdriver
from pprint import pprint
import time

driver = webdriver.Chrome('chromedriver')
driver.get('http://zzzscore.com/color/')
driver.implicitly_wait(300)

#시작 시각
start = time.time()

while time.time() - start <= 60:
    try:
        btn = driver.find_element_by_class_name("main")
        btn.click()
    except:
        pass