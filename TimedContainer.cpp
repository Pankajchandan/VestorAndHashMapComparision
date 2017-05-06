/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimedContainer.cpp
 * Author: pankaj
 * 
 * Created on April 15, 2017, 11:42 AM
 */

#include "TimedContainer.h"
TimedContainer::TimedContainer() : elapsed_time(0)
{
}

TimedContainer::~TimedContainer()
{
}

long TimedContainer::get_elapsed_time() const { return elapsed_time; }
void TimedContainer::reset_elapsed_time() { elapsed_time = 0; }
void TimedContainer::increment_elapsed_time(const long usec) { elapsed_time += usec; }

