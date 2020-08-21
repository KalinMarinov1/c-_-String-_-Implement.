# c-_-String-_-Implement.

This is a free to use source code of a string implementation of the *Standart Template Library*


This implementation does not use fast-string optimization. Every allocation is being set/(or read) from the heap. 


The few things i would like to optimize/ make safer are : <br>
  1.Change raw pointers to smart pointers. <br>
  2.Make it more user friendly. <br>
  3.Reduce amount of functions used by using template functions. <br> 
  4.Adjust the "getcapacity()" function to make bigger jumps between capacity sizes.<br>
  5.Add full list of functions that are published in : http://www.cplusplus.com/reference/string/string/ <br>
  6.Optimize functions, if possible. <br>


  #Side Notes : <br>
  *The reason i made this project is because i thought it would be challenging enough and that i would learn
 more about the way the STL is made and optimized.*  <br>


  *I would like to clarify that i have not used STL as guide on how to write the functions and code. The only
 information i used was http://www.cplusplus.com/reference/string/string/. I used it to see the functions that
 the STL had, the return types and description of few functions.* <br><br>


  *I am glad to say that i have learned a lot about optimizing classes, constructors and letting the compiler do
 the default initialization, copy, and move assignments.* <br><br>


  *I would also like to create a new project so i can better understand the "unordered_map" details and the way it works
 with buckets, rehashing, resizing and key-pair values insertion.* 


