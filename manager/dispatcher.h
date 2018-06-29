/*
 * Copyright 2018 <Gustavo Pantuza>
 *
 * ============================================================================
 *
 *       Filename:  dispatcher.h
 *
 *    Description:  Class to control which Abstract Data Type implementation
 *                  will be used if the given one exists
 *
 *        Version:  1.0
 *        Created:  21/06/2018 06:51:23 PM
 *       Compiler:  g++
 *
 *         Author:  Gustavo Pantuza (gustavopantuza@gmail.com)
 *   Organization:  Computer science community
 *
 * ============================================================================
 */


#ifndef _MANAGER_DISPATCHER_H
#define _MANAGER_DISPATCHER_H


#include "./spdlog/spdlog.h"


namespace dispatcher {


/**
 * Class to dispatch which Abstract Data Type will be executed as a service
 */
class VetulusDispatcher {

 public:
  VetulusDispatcher ()
  {
  }

 private:

};
}

#endif // _MANAGER_DISPATCHER_H
