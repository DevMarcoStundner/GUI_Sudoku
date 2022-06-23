// -----------------------------------------------------------------------
//  sudoku-c
//  Copyright 2014 Jan Břečka. All Rights Reserved.
//
//  This program is free software. You can redistribute and/or modify it
//  in accordance with the terms of the accompanying license agreement.
// -----------------------------------------------------------------------

// Part of https://github.com/honzabrecka/sudoku-c

#define N 9
#define EMPTY 0

/** @brief generate a sudoku solution by filling in the passed array
 *
 * @param *grid an int array consisting of NxN elements
 */
int sudoku_generate(int * grid);


/** @brief generate a sudoku puzzle by removing elements from a 
 *         solution grid
 *
 * @param *grid an int array consisting of NxN elements
 * @param empty the number of fields which shall be empty in the
 *        initial puzzle
 */
int sudoku_classic(int * grid, int empty);