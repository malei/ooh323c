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
 * @file ooq931.h
 * This file contains functions to support call signalling.
 */

#ifndef _OOQ931HDR_H_
#define _OOQ931HDR_H_

#include "ooasn1.h"
#include "ootypes.h"
#include "H323-MESSAGES.h"

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
 * @defgroup q931 Q931/H.2250 Message Handling
 * @{
 */

/* Q.931 packet must be at least 5 bytes long */
#define Q931_E_TOOSHORT         (-1001) 
/* callReference field must be 2 bytes long */
#define Q931_E_INVCALLREF       (-1002) 
/* invalid length of message */
#define Q931_E_INVLENGTH        (-1003) 

enum Q931MsgTypes {
   Q931NationalEscapeMsg  = 0x00,
   Q931AlertingMsg        = 0x01,
   Q931CallProceedingMsg  = 0x02,
   Q931ConnectMsg         = 0x07,
   Q931ConnectAckMsg      = 0x0f,
   Q931ProgressMsg        = 0x03,
   Q931SetupMsg           = 0x05,
   Q931SetupAckMsg        = 0x0d,
   Q931ResumeMsg          = 0x26,
   Q931ResumeAckMsg       = 0x2e,
   Q931ResumeRejectMsg    = 0x22,
   Q931SuspendMsg         = 0x25,
   Q931SuspendAckMsg      = 0x2d,
   Q931SuspendRejectMsg   = 0x21,
   Q931UserInformationMsg = 0x20,
   Q931DisconnectMsg      = 0x45,
   Q931ReleaseMsg         = 0x4d,
   Q931ReleaseCompleteMsg = 0x5a,
   Q931RestartMsg         = 0x46,
   Q931RestartAckMsg      = 0x4e,
   Q931SegmentMsg         = 0x60,
   Q931CongestionCtrlMsg  = 0x79,
   Q931InformationMsg     = 0x7b,
   Q931NotifyMsg          = 0x6e,
   Q931StatusMsg          = 0x7d,
   Q931StatusEnquiryMsg   = 0x75,
   Q931FacilityMsg        = 0x62
};
enum Q931IECodes {
   Q931BearerCapabilityIE   = 0x04,
   Q931CauseIE              = 0x08,
   Q931FacilityIE           = 0x1c,
   Q931ProgressIndicatorIE  = 0x1e,
   Q931CallStateIE          = 0x14,
   Q931DisplayIE            = 0x28,
   Q931SignalIE             = 0x34,
   Q931CallingPartyNumberIE = 0x6c,
   Q931CalledPartyNumberIE  = 0x70,
   Q931RedirectingNumberIE  = 0x74,
   Q931UserUserIE           = 0x7e
};

enum Q931InformationTransferCapability {
   Q931TransferSpeech,
   Q931TransferUnrestrictedDigital = 8,
   Q931TransferRestrictedDigital = 9,
   Q931Transfer3_1kHzAudio = 16,
   Q931TrasnferUnrestrictedDigitalWithTones = 17,
   Q931TransferVideo = 24
};

enum Q931CauseValues {
   Q931NoRouteToNetwork      = 0x02,
   Q931NoRouteToDestination  = 0x03,
   Q931ChannelUnacceptable   = 0x06,
   Q931NormalCallClearing    = 0x10,
   Q931UserBusy              = 0x11,
   Q931NoResponse            = 0x12,
   Q931NoAnswer              = 0x13,
   Q931SubscriberAbsent      = 0x14,
   Q931CallRejected          = 0x15,
   Q931NumberChanged         = 0x16,
   Q931Redirection           = 0x17,
   Q931DestinationOutOfOrder = 0x1b,
   Q931InvalidNumberFormat   = 0x1c,
   Q931StatusEnquiryResponse = 0x1e,
   Q931NoCircuitChannelAvailable = 0x22,
   Q931Congestion            = 0x2a,
   Q931InvalidCallReference  = 0x51,
   Q931ErrorInCauseIE        = 0
};

enum Q931SignalInfo {
   Q931SignalDialToneOn,
   Q931SignalRingBackToneOn,
   Q931SignalInterceptToneOn,
   Q931SignalNetworkCongestionToneOn,
   Q931SignalBusyToneOn,
   Q931SignalConfirmToneOn,
   Q931SignalAnswerToneOn,
   Q931SignalCallWaitingTone,
   Q931SignalOffhookWarningTone,
   Q931SignalPreemptionToneOn,
   Q931SignalTonesOff = 0x3f,
   Q931SignalAlertingPattern0 = 0x40,
   Q931SignalAlertingPattern1,
   Q931SignalAlertingPattern2,
   Q931SignalAlertingPattern3,
   Q931SignalAlertingPattern4,
   Q931SignalAlertingPattern5,
   Q931SignalAlertingPattern6,
   Q931SignalAlertingPattern7,
   Q931SignalAlretingOff = 0x4f,
   Q931SignalErrorInIE = 0x100
};

enum Q931NumberingPlanCodes {
   Q931UnknownPlan          = 0x00,
   Q931ISDNPlan             = 0x01,
   Q931DataPlan             = 0x03,
   Q931TelexPlan            = 0x04,
   Q931NationalStandardPlan = 0x08,
   Q931PrivatePlan          = 0x09,
   Q931ReservedPlan         = 0x0f
};

enum Q931TypeOfNumberCodes {
   Q931UnknownType          = 0x00,
   Q931InternationalType    = 0x01,
   Q931NationalType         = 0x02,
   Q931NetworkSpecificType  = 0x03,
   Q931SubscriberType       = 0x04,
   Q931AbbreviatedType      = 0x06,
   Q931ReservedType         = 0x07
};

/*
  Structure to build store outgoing encoded UUIE
  The different fields in the structure have octet lengths
  as specified in the spec.
*/
typedef struct Q931InformationElement {
   int discriminator;
   int offset;
   int length;
   ASN1OCTET data[1];
} Q931InformationElement;




/**
 * This function is invoked to decode a Q931 message.
 *
 * @param msg      Pointer to the Q931 message
 * @param length   Length of the encoded data
 * @param data     Pointer to the data to be decoded
 *
 * @return         Completion status - 0 on success, -1 on failure
 */
EXTERN int ooQ931Decode (Q931Message* msg, int length, ASN1OCTET *data);

/**
 * This function is used to decode the UUIE of the message from the list of
 * ies. It decodes the User-User ie and populates the userInfo field of the
 * message.
 * @param q931Msg    Pointer to the message whose User-User ie has to be
 *                   decoded.   
 *
 * @return           OO_OK, on success. OO_FAILED, on failure.
 */
EXTERN int ooDecodeUUIE(Q931Message *q931Msg);

/**
 * This function is used to encode the UUIE field of the Q931 message.
 * It encodes UUIE and adds the encoded data to the list of ies.
 * @param q931msg        Pointer to the Q931 message whose UUIE field has to be
 *                       encoded.
 *
 * @return               OO_OK, on success. OO_FAILED, on failure.
 */
EXTERN int ooEncodeUUIE(Q931Message *q931msg);

/**
 * This function is invoked to retrieve an IE element from a Q931 message.
 *
 * @param q931msg  Pointer to the Q931 message
 * @param ieCode   IE code for the IE element to be retrieved
 *
 * @return         Pointer to a Q931InformationElement contating
 *                 the IE element.
 */
EXTERN Q931InformationElement* ooQ931GetIE (const Q931Message* q931msg,
                                            int ieCode);

/**
 * This function is invoked to print a Q931 message.
 *
 * @param q931msg  Pointer to the Q931 message
 *
 * @return         - none
 */
EXTERN void ooQ931Print (const Q931Message* q931msg);


/**
 * This function is invoked to create an outgoing Q931 message.
 *
 * @param msg      Reference to the pointer of type Q931 message.
 * @param msgType  Type of Q931 message to be created
 *
 * @return         Completion status - 0 on success, -1 on failure
 */
EXTERN int ooCreateQ931Message(Q931Message **msg, int msgType);


/*
Need to figure out what parameters are to be passed to create bearer capability
EXTERN int ooAddBearerCapabilityIE(struct ooAppContext *);
*/

/**
 * This function is invoked to generate a unique call reference number.
 * @param None
 *
 * @return         - call reference number
 */
EXTERN ASN1USINT ooGenerateCallReference();


/**
 * This function is used to generate a unique call identifier for the call.
 * @param callid      Pointer to the callid structure, which will be populated
 *                    with the generated callid.
 *
 * @return            OO_OK, on success. OO_FAILED, on failure.
 */
EXTERN int ooGenerateCallIdentifier(H225CallIdentifier *callid);

/**
 * This function is invoked to release the memory used up by a Q931 message
 *
 * @param q931Msg  Pointer to a Q931 message which has to be freed.
 *
 * @return         Completion status - 0 on success, -1 on failure
 */
EXTERN int ooFreeQ931Message(Q931Message *q931Msg);

/**
 * This function is invoked to retrive the outgoing message buffer for
 * Q931 message
 *
 * @param call     Pointer to call for which outgoing Q931 message has to be
 *                 retrieved.
 * @param msgbuf   Pointer to a buffer in which retrieved message will
 *                 be returned.
 * @param len      Pointer to int in which length of the buffer will
 *                 be returned.
 * @param msgType  Pointer to integer in which message type of the ougoing
 *                 message is returned.
 *
 * @return         Completion status - 0 on success, -1 on failure
 */
EXTERN int ooGetOutgoingQ931Msgbuf(ooCallData *call, ASN1OCTET * msgbuf,
                                   int * len, int *msgType);

/**
 * This function is invoked to send a ReleaseComplete message for
 * the currently active call.
 *
 * @param call    Pointer to the call for which ReleaseComplete message have
 *                to be sent. 
 *
 * @return         Completion status - 0 on success, -1 on failure
 */
EXTERN int ooSendReleaseComplete(ooCallData *call);

/**
 * This function is invoked to send a call proceeding message in response to
 * received setup message.
 *
 * @param call    Pointer to the call for which CallProceeding message have to
 *                be sent. 
 *
 * @return        Completion status - 0 on success, -1 on failure
 */
EXTERN int ooSendCallProceeding(ooCallData *call);

/**
 * This function is invoked to send alerting message in response to received 
 * setup message.
 *
 * @param call     Pointer to the call for which Alerting message have to be
 *                 sent. 
 *
 * @return         Completion status - 0 on success, -1 on failure
 */
EXTERN int ooSendAlerting(ooCallData *call);

/**
 * This function is invoked to send Facility message.
 *
 * @param call     Pointer to the call for which Facility message have to be
 *                 sent. 
 *
 * @return         Completion status - 0 on success, -1 on failure
 */
EXTERN int ooSendFacility(ooCallData *call);

/**
 * This function is invoked to send a Connect message in response to received 
 * setup message.
 *
 * @param call      Pointer to the call for which connect message has to be
 *                  sent. 
 *
 * @return          Completion status - 0 on success, -1 on failure
 */
EXTERN int ooSendConnect(ooCallData *call);

/**
 * This function is used to send a SETUP message for outgoing call. It first
 * creates an H.225 TCP connection with the remote end point and then sends
 * SETUP message over this connection.
 * @param destip    Dotted IP address of the remote end point.
 * @param port      Port at which remote endpoint is listening for calls.
 * @param callToken Unique token for the new call.
 *
 * @return          OO_OK, on success. OO_FAILED, on failure
 */
EXTERN int ooH323MakeCall(char *destip, int port, char *callToken);

/**
 * This function is used to handup a currently active call. It sets the call
 * state to CLEARING and initiates closing of all logical channels.
 * @param callToken Unique token of the call to be hanged.
 *
 * @return          OO_OK, on success. OO_FAILED, on failure.
 */
EXTERN int ooH323HangCall(char * callToken);


/**
 * Function to accept a call by sending connect. This function is used
 * as a helper function to ooSendConnect.
 * @param call      Pointer to the call for which connect has to be sent
 *
 * @return          OO_OK, on success. OO_FAILED, on failure.
 */
EXTERN int ooAcceptCall(ooCallData *call);

/**
 * An helper function to ooMakeCall.
 * @param call      Pointer to the new call.
 *
 * @return          OO_OK, on success. OO_FAILED, on failure.
 */
EXTERN int ooH323MakeCall_helper(ooCallData *call);


/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* __Q931HDR_H */