/*
 * homework4.h
 *
 *  Created on:
 *      Author:
 */

#ifndef HOMEWORK4_H_
#define HOMEWORK4_H_

// This function initializes the board by turning off the Watchdog Timer.
void initBoard();
bool charFSM(char rChar);

// TODO: Define any constants that are local to homework.c using #define
typedef enum state
{
    base,
    state_1,
    state_2,
    state_3,
}state;


#endif /* HOMEWORK4_H_ */
