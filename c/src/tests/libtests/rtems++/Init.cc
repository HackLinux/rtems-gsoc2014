/*  Init
 *
 *  This routine is the initialization task for this test program.
 *
 *  Input parameters:
 *    argument - task argument
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1997
 *  Objective Design Systems Ltd Pty (ODS)
 *  All rights reserved (R) Objective Design Systems Ltd Pty
 *
 *  COPYRIGHT (c) 1989-1997.
 *  On-Line Applications Research Corporation (OAR).
 *  Copyright assigned to U.S. Government, 1994.
 *
 *  The license and distribution terms for this file may in
 *  the file LICENSE in this distribution or at
 *  http://www.OARcorp.com/rtems/license.html.
 *
 *  $Id$
 */

#define TEST_INIT
#include "System.h"

rtems_task Init(rtems_task_argument )
{
  puts( "\n\n*** RTEMS++ TEST ***" );

  rtemsEvent end_me("INIT");
  Task1 task_1;
  
  task_1.set_end_event(end_me);
  
  printf( "INIT - Task.create() - " );
  task_1.create("TA1 ", 0, RTEMS_MINIMUM_STACK_SIZE);
  printf("%s\n", task_1.last_status_string());

  printf( "INIT - Task.create() - " );
  task_1.create("TA1 ", 10, RTEMS_MINIMUM_STACK_SIZE * 6);
  printf("%s\n", task_1.last_status_string());

  printf( "INIT - Task.create() - " );
  task_1.create("TA1 ", 10, RTEMS_MINIMUM_STACK_SIZE * 6);
  printf("%s\n", task_1.last_status_string());

  printf( "INIT - Task.restart() - " );
  task_1.restart(0);
  printf("%s\n", task_1.last_status_string());

  printf( "INIT - Task.start(0xDEADDEAD) - " );
  task_1.start(0xDEADDEAD);
  printf("%s\n", task_1.last_status_string());

  // block waiting for any event
  rtems_event_set out;

  // wait for task1 to tell me to finish
  end_me.receive(RTEMS_SIGNAL_0, out);

  task_1.destroy();
  
  printf("*** END OF RTEMS++ TEST ***");

  // needs to be in C, no C++ object owns the Init task
  rtems_status_code status  = rtems_task_delete( RTEMS_SELF );
  directive_failed( status, "rtems_task_delete of RTEMS_SELF" );
}



