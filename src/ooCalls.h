/*
 * Copyright (C) 2004-2005 by Objective Systems, Inc.
 *
 * This software is furnished under an open source license and may be
 * used and copied only in accordance with the terms of this license.
 * The text of the license may generally be found in the root
 * directory of this installation in the COPYING file.  It
 * can also be viewed online at the following URL:
 *
 *   http://www.obj-sys.com/open/license.html
 *
 * Any redistributions of this file including modified versions must
 * maintain this copyright notice.
 *
 *****************************************************************************/
/**
 * @file ooCalls.h
 * This file contains Call management functions.
 */
#ifndef _OOCALLS_H_
#define _OOCALLS_H_

#include "ootypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXTERN
#ifdef _WIN32
#define EXTERN __declspec(dllexport)
#else
#define EXTERN
#endif /* _WIN32 */
#endif /* EXTERN */

/**
 * @defgroup callmgmt  Call Management
 * @{
 */
/**
 * This function is used to create a new call entry.
 * @param type         Type of the call (incoming/outgoing)
 * @param callToken    Call Token, an uniques identifier for the call
 *
 * @return             Pointer to a newly created call
 */
EXTERN ooCallData* ooCreateCall(char *type, char *callToken);

/**
 * This function is used to add a call to the list of existing calls.
 * @param h323ep       Pointer to the H323 Endpoint structure.
 * @param call         Pointer to the call to be added.
 *
 * @return             OO_OK, on success. OO_FAILED, on failure
 */
EXTERN int ooAddCallToList(ooEndPoint * h323ep, ooCallData *call);

/**
 * This function is used to find a call by using the unique token for the call.
 * @param callToken      The unique token for the call.
 *
 * @return               Pointer to the call if found, NULL otherwise.
 */
EXTERN ooCallData* ooFindCallByToken(char *callToken);

/**
 * This function is used to clear a call. Based on what stage of clearance the
 * call is it takes appropriate action.
 * @param call   Handle to the call which has to be cleared.
 *
 * @return       OO_OK, on success. OO_FAILED, on failure.
 */
EXTERN int ooEndCall(ooCallData *call);

/**
 * This function is used to remove a call from the list of existing calls.
 * @param h323ep        Pointer to the H323 Endpoint.
 * @param call          Pointer to the call to be removed.
 *
 * @return              OO_OK, on success. OO_FAILED, on failure.
 */
EXTERN int ooRemoveCallFromList(ooEndPoint * h323ep, ooCallData *call);

/**
 * This function is used to clean a call. It closes all associated sockets,
 * removes call from list and frees up associated memory.
 * @param call          Pointer to the call to be cleared.
 *
 * @return              OO_OK, on success. OO_FAILED, on failure.
 */
EXTERN int ooCleanCall(ooCallData *call);

/**
 * This function is used to add a new logical channel entry into the list
 * of currently active logical channels.
 * @param call      Pointer to the call for which new logical channel
 *                  entry has to be created.
 * @param channelNo Channel number for the new channel entry.
 * @param sessionID Session identifier for the new channel.
 * @param type      Type of the channel(audio/video/data)
 * @param dir       Direction of the channel(transmit/receive)
 * @param epCap     Capability to be used for the new channel.
 *
 * @return          Pointer to logical channel, on success. NULL, on failure
 */
EXTERN ooLogicalChannel* ooAddNewLogicalChannel(ooCallData *call, int channelNo,
                                  int sessionID, char *type, char * dir,
                                  ooH323EpCapability *epCap);

/**
 * This function is used to find a logical channel by logical channel number.
 * @param call          Pointer to the call for which logical channel is
 *                      required.
 * @param channelNo     Forward Logical Channel number for the logical channel
 *
 * @return              Pointer to the logical channel if found, NULL
 *                      otherwise.  
 */
EXTERN ooLogicalChannel* ooFindLogicalChannelByLogicalChannelNo
                                  (ooCallData *call,int channelNo);

/**
 * This function is called when a new logical channel is established. It is particularly
 * useful in case of faststart. When the remote endpoint selects one of the proposed
 * alternatives, other channels for the same session type need to be closed. This function
 * is used for that.
 * @param call      Handle to the call which owns the logical channel.
 * @param pChannel  Handle to the newly established logical channel.
 *
 * @return          OO_OK, on success. OO_FAILED, on failure.
 */
EXTERN int ooOnLogicalChannelEstablished(ooCallData *call, ooLogicalChannel * pChannel);

/**
 * This fuction is used to check whether a specified session in specified direction
 * is active for the call.
 * @param call       Handle to call for which session has to be queried.
 * @param sessionID  Session id to identify the type of session(1 for audio,
 *                   2 for voice and 3 for data)
 * @param dir        Direction of the session(transmit/receive)
 *
 * @return           1, if session active. 0, otherwise.
 */
EXTERN ASN1BOOL ooIsSessionEstablished(ooCallData *call, int sessionID, char* dir);

/**
 * This function is used to retrieve a logical channel with particular sessionID. Note
 * that there can be two entries of logical channel, one in each direction. This function
 * will return the first channel which has the same session ID.
 * @param call      Handle to the call which owns the channels to be searched.
 * @param sessionID Session id of the session which is to be searched for.
 *
 * @return          Returns a pointer to the logical channel if found, NULL otherwise.
 */
EXTERN ooLogicalChannel* ooGetLogicalChannel(ooCallData *call, int sessionID);

/**
 * This function is used to remove a logical channel from the list of logical
 * channels.
 * @param call              Pointer to the call from which logical channel has
 *                          to be removed.
 * @param ChannelNo         Forward logical channel number of the channel to be
 *                          removed.
 */
EXTERN int ooRemoveLogicalChannel(ooCallData *call, int ChannelNo);

/**
 * This function is used to cleanup a logical channel. It first stops media, if it
 * is still active and then removes the channel from the list, freeing up all the
 * associated memory.
 * @param call       Handle to the call which owns the logical channel.
 * @param channelNo  Channel number identifying the channel.
 *
 * @return           OO_OK, on success. OO_FAILED, on failure.
 */
EXTERN int ooClearLogicalChannel(ooCallData *call, int channelNo);

/**
 * This function is used to cleanup all the logical channels associated with the call.
 * @param call      Handle to the call which owns the channels.
 *
 * @return          OO_OK, on success. OO_FAILED, on failure.
 */
EXTERN int ooClearAllLogicalChannels(ooCallData *call);

/**
 * This function can be used by an application to specify media endpoint information
 * for different types of media. The stack by default uses local IP and port for media.
 * An application can provide mediainfo if it wants to override default.
 * @param call      Handle to the call
 * @param mediaInfo mediainfo structure which defines the media endpoint to be used.
 *
 * @return          OO_OK, on success. OO_FAILED, on failure.
 */
EXTERN int ooAddMediaInfo(ooCallData *call, ooMediaInfo mediaInfo);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif



#endif