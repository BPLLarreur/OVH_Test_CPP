# OVH TEST ROBOTS

**In the following project i tried to answer this problem :**

6 robots must collaborate to record this secret: “Hidden beneath the old oak tree, golden coins patiently await discovery.” Each word of the secret is sent sequentially to one of the robots, with the receiving robot chosen randomly for each word. This means no single robot possesses the entire secret. All robots can communicate with each other, but only through messages. Please simulate these robots and write an algorithm that allows them to rebuild the secret. The only thing robots know about the secret is that it ends with the only period. Once the secret is rebuilt, only one robot should write it to a well-known file. All robots can be simulated in the same executable for simplicity.

**I did it in C++ since Go isn't really the language I can express myself the best at the moment even if I started learning it by reading this blog :**
https://blog.stephane-robert.info/docs/developper/programmation/golang/

Anyway here is the explanation of the code I wrote :

-First, 6 robots are initialized

-Then a Scheduler receive the entire secret sentence, store it and send it word by word until there are no more left in the secret sentence.

-After, the scheduler sends randomly the words to the robots, iterating through them and sending a random word to each robot until there is no words left.
each word come with an index so it can be stored by a robot inside a map (2D array, here with an index attributed to each received word).

-The communication between the robot starts. each robot sequencially ask all other robots to see if anyone is having a word at an index which is not know by the asking robot.

-After each exchange between two robots, check are performed to know if the harvested words can be combined at the correct index and if the built sentence is ending with a period. If all the checks are positive, the robot performing all the checks is building the secret string and writing it to a text file so we can look at it.
