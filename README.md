Question 1
____________________________

Run : ./a.out <#Hydrogen atoms> <#oxygen atoms> <#positions> <#Threshold>

1. Made thread for hydrogen and oxygens
2. when 2 hyd and 1 oxy is available it will call make_bond()
3. make bond checks availability of site and do reaction.
4. sleep(3) is given.



Question 2 
________________________________

Run : ./a.out <#of geeks> <#of non-geeks> <#of singer>

1. We have make threads for all three types of people i.e. Geek Non-Geek and Singer
2. thread call is made for GeekArrives() for Geek.
   thread call is made for NonGeekArrives() for Non-Geek.
   thread call is made for SingerArrives() for Singer.
3. We take Lock and Read Status of Bridge and update if it is safe .
4. 3 will wait untile 4 th come. when 4 th come he will call Go Bridge and Broadcast all waiting three.
5. When last Geek Non-Geek Combination is unsafe it will send one of them first and then three will go.
6. For remaining singers we send all of them saperately.

Question 3 
________________________________

Run : ./a.out <#of students> <#of courses>

1. Each student creates preference list containing 8 courses. From each knowledge spectrum 2 courses are selected randomly so that probability of geting a course for each knowledge spectrum remains same.


