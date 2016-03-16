//
//  RandomNumber.h
//  Project5
//
//  Created by Howard Stahl on 1/11/16.
//  Copyright © 2016 Howard Stahl. All rights reserved.
//

#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H

// This class has been provided to CS 31 students.
// No changes need to be made to this class.
class RandomNumber
{
public:
    RandomNumber( int min, int max, bool minInclusive=true, bool maxInclusive=true );
    
    // supply a number between min and max inclusive
    int random( );
private:
    int  mMinimum, mMaximum;
};


#endif
