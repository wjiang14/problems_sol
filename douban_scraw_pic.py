#coding=utf-8
from bs4 import BeautifulSoup
import urllib2
from Queue import Queue
import urllib
url_list = []
queue = Queue()
req_header = {'User-Agent':'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.6) Gecko/20091201 Firefox/3.5.6'}
req_timeout = 20
 
def next_page():
    base_url = 'http://www.douban.com/photos/album/106713162/'
    for i in range(2):
        
        req = urllib2.Request(base_url,None,req_header)
        html = urllib2.urlopen(req,None,req_timeout)       
        #html = urllib2.urlopen(base_url).read()
        soup = BeautifulSoup(html)         
        next_url = soup.find('link',{'rel':'next'}).get('href')
        yield base_url
        base_url = next_url 
        
def callback(next_page):               
    for page in next_page():
        queue.put(page)
        #print page
    print 'There are %d pages'%queue.qsize()
    
def get_url_list():        
    while not queue.empty():
        page_url = queue.get()
        req = urllib2.Request(page_url,None,req_header)
        html = urllib2.urlopen(req,None,req_timeout)
                
        #html = urllib2.urlopen(page_url).read()
        soup = BeautifulSoup(html)
        img_urls = soup.find_all(['img'])
        for myimg in img_urls:
            Jpgurl = myimg.get('src')
            url_list.append(Jpgurl)
    print 'There are %d pictures'%len(url_list) 
    
def down():   
    for down_url in url_list:
        urllib.urlretrieve(down_url,'/Users/wei/Documents/pic'+'/'+down_url[-11:])
        print 'Now is loading the %dst picture'%url_list.index(down_url)
        
def main():
    callback(next_page)
    get_url_list()
    down()
        
if __name__ == '__main__':
    main()