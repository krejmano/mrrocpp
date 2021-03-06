/*
 *  Player - One Hell of a Robot Server
 *  Copyright (C) 2000  
 *     Brian Gerkey, Kasper Stoy, Richard Vaughan, & Andrew Howard
 *                      
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/*
 * $Id$
 *
 * A device is a driver/interface pair.
 */

#ifndef _DEVICE_H
#define _DEVICE_H


#include "playerqueue.h"

// Forward declarations
class Driver;


// A device entry describes an instantiated driver/interface
// combination.  Drivers may support more than one interface,
// and hence appear more than once in the device table.
class Device
{
  private:
    // did we allocate buffers, or did somebody else?
    bool allocp;

  public:
  
  // Default constructor etc
  Device(player_device_id_t id, Driver *driver, unsigned char access);
  ~Device();

  // Initialize the buffers for this interface
  void SetupBuffers(size_t datasize, size_t commandsize,
                    size_t reqqueuelen, size_t repqueuelen);

  // Initialize the buffers for this interface, with memory pre-allocated
  void SetupBuffers(void* data, size_t datasize, 
                    void* command, size_t commandsize, 
                    void* reqqueue, int reqqueuelen, 
                    void* repqueue, int repqueuelen);

  // Index in the device table
  int index;              

  // Next entry in the device table (this is a linked-list)
  Device* next;

  // Id for this device
  player_device_id_t id;

  // Allowed access mode: 'r', 'w', or 'a'
  unsigned char access;   

  // The string name for the driver
  char drivername[PLAYER_MAX_DEVICE_STRING_LEN];
  
  // the string name for the robot (only used with Stage)
  char robotname[PLAYER_MAX_DEVICE_STRING_LEN];

  // Pointer to the driver
  Driver* driver;

  // Size of the buffers
  size_t data_size, command_size;

  // Size of the last packet written
  size_t data_used_size, command_used_size;
  
  // Data buffer
  unsigned char *data;

  // Command buffer
  unsigned char *command;

  // Timestamp for most recent data
  struct timeval data_timestamp;

  // Timestamp for most recent command
  struct timeval command_timestamp;

  // Queues for incoming requests and outgoing replies
  PlayerQueue* reqqueue;
  PlayerQueue* repqueue;
};

#endif
