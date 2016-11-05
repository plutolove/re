###正則表達式轉DFA
只支持e*, e+, e?, e1e2, e1|e2五種語法  
* 首先將正則表達式轉換成後綴表達式  

* 再將後綴表達式轉換成NFA,分五種情況準換  
>* e   ![cmd-markdown-logo](image/1.png)  
>* e1e2   ![cmd-markdown-logo](image/2.png)  
>* e1|e2   ![cmd-markdown-logo](image/3.png)
>* e?   ![cmd-markdown-logo](image/4.png)
>* e*   ![cmd-markdown-logo](image/5.png)
>* e+   ![cmd-markdown-logo](image/6.png)

* 用子集構造方法將NFA轉換爲DFA
