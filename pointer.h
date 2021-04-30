//
//  pointer.h
//  MSDscript
//
//  Created by Vladimir Antigua on 3/16/21.
//

#ifndef __msdscript_pointer__
#define __msdscript_pointer__

#include <memory>

#define USE_PLAIN_POINTERS 1 // When finish refactoring change the 1  to number 0
// then run the leak
// leaks -atExit -- ./msdscript --interp
// 1+2
#if USE_PLAIN_POINTERS

# define NEW(T)    new T
# define PTR(T)    T*
# define CAST(T)   dynamic_cast<T*>
# define CLASS(T)  class T
# define THIS      this

#else

# define NEW(T)    std::make_shared<T>
# define PTR(T)    std::shared_ptr<T>
# define CAST(T)   std::dynamic_pointer_cast<T>
# define CLASS(T)  class T : public std::enable_shared_from_this<T>
# define THIS      shared_from_this()

#endif

#endif

//Zero Leaks:

//leaks Report Version: 4.0
//Process 15619: 159 nodes malloced for 16 KB
//Process 15619: 0 leaks for 0 total leaked bytes.




//                     Detecting Leaks

// lecture page #2 instruction to test for memory leak: https://utah.instructure.com/courses/667448/files/113991875?wrap=1

//$ leaks -atExit -- ./msdscript --interp1+23Process:         msdscript [97927]....leaks Report Version: 4.0Process 97927: 222 nodes malloced for 20 KBProcess 97927: 7 leaks for 128 total leaked bytes.    7 (128 bytes) << TOTAL >>      3 (64 bytes) ROOT LEAK: <AddExpr 0x1267040a0> [32]         1 (16 bytes) <NumExpr 0x126704080> [16]         1 (16 bytes) <NumExpr 0x126704090> [16]      1 (16 bytes) ROOT LEAK: <NumExpr 0x1267040f0> [16]      1 (16 bytes) ROOT LEAK: <NumVal 0x1267040c0> [16]      1 (16 bytes) ROOT LEAK: <NumVal 0x1267040d0> [16]      1 (16 bytes) ROOT LEAK: <NumVal 0x1267040e0> [16]
