from selenium import webdriver

driver = webdriver.Chrome('chromedriver')
driver.get("http://zzzscore.com/1to50")
driver.implicitly_wait(300)

num = 1

def clickbtn():
    global num
    btns = driver.find_elements_by_xpath('//*[@id="grid"]/div[*]')

    for btn in btns:
        if btn.text == str(num):
            btn.click()
            num+=1
            return

while num<=50:
    clickbtn()
