/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimedContainer.h
 * Author: pankaj
 *
 * Created on April 15, 2017, 11:42 AM
 */

#ifndef TIMEDCONTAINER_H_
#define TIMEDCONTAINER_H_

class TimedContainer
{
public:
    TimedContainer();
    virtual ~TimedContainer();

    void reset_elapsed_time();
    long get_elapsed_time() const;

protected:
    void increment_elapsed_time(const long usec);

private:
    long elapsed_time;
};

#endif /* TIMEDCONTAINER_H_ */

