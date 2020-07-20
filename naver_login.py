from selenium import webdriver

from selenium.webdriver.common.keys import Keys

driver = webdriver.Chrome('chromedriver')
driver.get("https://bible.ctm.kr/")

driver.find_element_by_name('id').send_keys('tnscks1013')

driver.find_element_by_name('pwd').send_keys('cksdl1013')
