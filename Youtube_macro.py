from selenium import webdriver
import time

from selenium.webdriver.common.keys import Keys

driver = webdriver.Chrome('chromedriver')
driver.get("https://www.youtube.com/")

time.sleep(3)

search = driver.find_element_by_xpath('//*[@id="search"]')

search.send_keys('좀비고')
time.sleep(1)

search.send_keys(Keys.ENTER)