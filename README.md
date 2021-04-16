# MSScript User Instructions Handbook

## Description

#### The MSDScript is a C++ interpreter able to parse functions, loops, perform arithmetic operations like add and multiply and if and else expressions.

## How to run the MSDScript: 

**MSDScript can be be run or build as a plain mode or library to be run as part of another application.** 

To run the MSDScript as a part of another application following the instructions below: 

Please use the library files which is provided in the zip file.

- ##### Add the following #includes to your executable app file: 

```
#include "parse.h"
#include "expr.h"
#include "step.h"
#include "pointer.h"
```



- ##### Create the .o files from all the .cpp files in the zip folder. For example: 

  - `$ gcc --std=c++14  -c cont.cpp`

- ##### To create an Archive file: 

  - ###### `$ ar -ruv libraryImage.a test.o expr.o parse.o val.o env.o step.o cont.o`

- ##### Link the archive  libraryImage.a to your executable:

  - `$ c++ -o which_day which_day.cpp ../libraryImage.a`

#### The Library contain the following items found in the zip file called `Library_Files`: 

- expr.cpp
- expr.h
- parse.cpp
- parse.h
- val.cpp
- val.h
- env.cpp
- env.h
- step.cpp
- step.h
- cont.cpp
- cont.h
- test.cpp
- pointer.h
- catch.h

#### To run the Plain MSDScript follow the instructions below: 

- ###### Save all the files below found on the zip file called `Plain_MSDScript_Files` in a directory on your computer:

  - pointer.h
  - parse.h
  - parse.cpp
  - catch.h
  - cmdline.cpp
  - cmdline.h
  - cont.cpp
  - cont.h
  - env.cpp
  - env.h
  - exec.cpp
  - exec.h
  - expr.cpp
  - expr.h
  - main.cpp
  - Makefile
  - msdscript
  - step.cpp
  - step.h
  - test.cpp
  - val.cpp
  - val.h

- create the executable called `msdscript` and the .o files by running make from the directory you created above:

  - `$ make`

  - Run the executable `./msdscript`

  - After successful compile and run please try one of the following command for example: 

    

    - To see all the MSDScript flags avaible type:  `/.msdscript --help`

      ```
      You can use the following commands within this MSDScript program --help, --test, --print, --interp and --step: for a example to run the program and check if all test pass run the following command on the terminal: ./msdscript --test if want to interp run: ./msdcript --interp 
      ```

      

    - To return the value of the given expression run: `/.msdscript --interp`

    - Note: To see the result of the expressions evaluated below remember press enter after enter the add expression `3+2` then in the next line press control d to see the printed result.

    - ##### Add Expression:

      ```
      $ `/.msdscript --interp`
      3+2 
      5
      ```

    - ##### Multiply Expression:

      ```
      $ `/.msdscript --interp`
      3*2 
      6
      ```

    - ##### Let Expression:

      ```
      $ `/.msdscript --interp`
      _let x = 1 _in x + 2                         
      3
      ```

    - ##### Boolean Epression:

      ```
      $ `/.msdscript --interp`
      _if _true _then 1 _else 2
      1
      ```

      

    - ##### Function Expression: 

      ```
      _let pair = _fun (a) _fun (b)
                    _fun(sel)
                    _if sel _then a _else b
      _in _let fst = _fun (p) p(_true)
      _in _let snd = _fun (p) p(_false)
      _in _let fib = _fun (fib)
                      _fun (x)
                        _if x == 0
                        _then pair(1)(1)
                        _else _if x == 1
                              _then pair(1)(1)
                              _else _let p = fib(fib)(x + -1)
                                    _in pair(fst(p) + snd(p))(fst(p))
      _in  fst(fib(fib)(30))
      
      1346269
      ```

      

    - To run all MSDScript test: `/.msdscript --test`

      ```
      All tests passed (155 assertions in 17 test cases)
      ```

      

    - ##### Loops: 

      - To evalue big operations:   `/.msdscript --step`

      ```
      _let countdown = _fun(countdown)
                         _fun(n)
                           _if n == 0
                           _then 0
                           _else countdown(countdown)(n + -1)
      _in countdown(countdown)(1000000)
      ```

      

    - To add the proper parenthesis for the expressions:  `/.msdscript --print`

      ```
      7*3+6
      - press control d
      ((7*3)+6
      ```

  

  

## API Documentation:



##### Backus - Naur Form (BNF) Grammar:

```
Expressions grammar:

〈expr〉=〈number〉
       |〈boolean〉
       |〈expr〉==〈expr〉
       |〈expr〉+〈expr〉
       |〈expr〉*〈expr〉
       |〈expr〉(〈expr〉)
       |〈variable〉
       |_let〈variable〉=〈expr〉_in〈expr〉
       |_if〈expr〉_then〈expr〉_else〈expr〉
       |_fun(〈variable〉)〈expr〉


```



#### Parsing with Functions and Calls:

> 〈expr〉           =〈comparg〉
>
> ​			              |〈comparg〉==〈expr〉
>
> 〈comparg〉  =〈addend〉
>
> ​						 |〈addend〉+〈comparg〉
>
> 〈addend〉   =〈multicand〉
>
> ​						|〈multicand〉*〈addend〉
>
> 〈multicand  =〈inner〉
>
> ​						|〈multicand〉(〈expr〉)
>
> 〈inner〉      =〈number〉|(〈expr〉)|〈variable〉
>
> ​				       |   _let〈variable〉=〈expr〉_in〈expr〉
>
> ​				       |  _true|_false
>
> ​				       | _if〈expr〉_then〈expr〉__else〈expr〉_
>
> ​                       | _fun(〈variable〉)〈expr



#### Report MSDScript Bugs and Errors: 

Please use the following site to report bugs or errors: 

```
https://github.com/vladimirantigua/MSDScriptInterpreter/issues/new
```

#### 

#### License:

- Please use the MIT license:

```
The MIT License (X11 License)[6] is a permissive free software license originating at the Massachusetts Institute of Technology (MIT)[7] in the late 1980s.[8] As a permissive license, it puts only very limited restriction on reuse and has, therefore, high license compatibility. https://en.wikipedia.org/wiki/MIT_License
```



















