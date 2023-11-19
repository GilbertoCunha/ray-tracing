#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <iostream>
using namespace std;

/**
 * @brief Creates a visual progress bar to access the status of the program
 * 
 * @param cout The output stream to log the progress bar to
 * @param current TCurrent iteration
 * @param total Total iterations
 */
void progress_bar(ostream& cout, int current, int total) {
    int done = 100 * double(current) / total;
    cout << "\rProgress: |";
    for (int i=0; i<done; i++) cout << '#';
    for (int i=done; i<100; i++) cout << ' ';
    cout << '|' << ' ' << flush;
}

#endif