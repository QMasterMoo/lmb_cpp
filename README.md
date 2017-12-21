# No longer updated
Originally I wanted to remake lessermoobot in c++ to try and see if I could make it run faster. Since LMB wasn't resource heavy already, I quickly decided to cancel with the rewrite. I also don't want to have to redo all the string processing and database stuff in C++ since it's going to be a so much messier than python. 

That said the 5th iteration of this bot will be made sometime soonish. These are quickly turning into a catalog of my programming expieriences. I mean, for lessermoobot 1.0 I was using another program to log the IRC chat, and then would open the file, process it, and store it in a text file again. Then when I wanted to query someone's history, I'd load up the relevant files and do the same process all over again. In version 2.0 I made my own IRC logger, but it still used a flatfile system. In version 3.0 I transitioned to databases but it's still pretty messy since I never had designed one before then and had to base them off of random databses that we had accrued on our server. Version 4.0 was likely going to redesign the database but as you now know it never got too far. Version 5.0 will likely suffer from new mistakes, so I can't wait to make fun of myself next year.



# lmb_cpp
Fourth version of the same thing
