//
//  main.cpp
//  COP3503 Project 2
//
//  Created by Chad Wishner on 10/12/17.
//  Copyright © 2017 Chad Wishner. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}


/* Free     Free       Free     Free    4kb each
 Free     Free       Free     Free
 
 Insert Program --> Name (p1), size (9kb)
 Name (p2), size (2kb)
 Name (p3), size (8kb)
 
 p1     p1       p1       p2            (4kb each)
 p3     p3       Free     Free
 
 Kill Program -->   Kill p2
 
 p1     p1       p1       Free          (4kb each)
 p3     p3       Free     Free
 
 Insert Program --> Name (p4), size (1kb) (BEST FIT), reduce the ammount of fragments (or spaces between used memory)
 
 p1     p1       p1       p4            (4kb each)
 p3     p3       Free     Free
 
 Insert Program --> Name (p4), size (1kb) (Worst FIT), reduce the ammount of fragments (or spaces between used memory)
 
 p1     p1       p1       Free          (4kb each)
 p3     p3       p4       Free
 
 Count Fragments --> counts the amount of spaces between used memory
 */

