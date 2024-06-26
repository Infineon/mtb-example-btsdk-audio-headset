/*
 * Copyright 2016-2024, Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
 *
 * This software, including source code, documentation and related
 * materials ("Software") is owned by Cypress Semiconductor Corporation
 * or one of its affiliates ("Cypress") and is protected by and subject to
 * worldwide patent protection (United States and foreign),
 * United States copyright laws and international treaty provisions.
 * Therefore, you may use this Software only as provided in the license
 * agreement accompanying the software package from which you
 * obtained this Software ("EULA").
 * If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
 * non-transferable license to copy, modify, and compile the Software
 * source code solely for use in connection with Cypress's
 * integrated circuit products.  Any reproduction, modification, translation,
 * compilation, or representation of this Software except as specified
 * above is prohibited without the express written permission of Cypress.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
 * reserves the right to make changes to the Software without notice. Cypress
 * does not assume any liability arising out of the application or use of the
 * Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death ("High Risk Product"). By
 * including Cypress's product in a High Risk Product, the manufacturer
 * of such system or application assumes all risk of such use and in doing
 * so agrees to indemnify Cypress against all liability.
 */

/** @file
 *
 * A2DP support for HCI AV Source application
 */
#ifndef A2DP_APP_H
#define A2DP_APP_H

#include "bt_types.h"
#include "wiced_bt_avdt.h"

#define CASE_RETURN_STR(const) case const: return #const;

/* A2DP Audio Route */
#define AUDIO_ROUTE_I2S             0x00
#define AUDIO_ROUTE_UART            0x01
#define AUDIO_ROUTE_SINE            0x02

/*A2DP Sampling Frequencies */
#define AUDIO_SF_16K                0x00
#define AUDIO_SF_32K                0x01
#define AUDIO_SF_44_1K              0x02
#define AUDIO_SF_48K                0x03

/* Channel Configurations */
#define AUDIO_CHCFG_MONO            0x00
#define AUDIO_CHCFG_STEREO          0x01

#define AV_CTRL_MTU                 L2CAP_MTU_SIZE
#define AV_DATA_MTU                 L2CAP_MTU_SIZE
#define AV_RET_TOUT                 4
#define AV_SIG_TOUT                 4
#define AV_IDLE_TOUT                10
#define AV_SEC_MASK                 BTM_SEC_NONE

/* offset of media type in codec info byte array */
#define AV_MEDIA_TYPE_IDX           1

#define  AV_NUM_SEPS                3

typedef enum
{
    AV_STATE_IDLE,              /* Initial state (channel is unused) */
    AV_STATE_CONFIGURED,        /* Remote has sent configuration request */
    AV_STATE_CONNECTED,         /* Signaling Channel is connected and active */
    AV_STATE_STARTED,			/* Data streaming */
} AV_STATE;

typedef enum
{
    AV_STREAM_STATE_STOPPED,
    AV_STREAM_STATE_STARTING,
    AV_STREAM_STATE_STARTED,
    AV_STREAM_STATE_STOPPING
} AV_STREAM_STATE;

/* Feature mask definitions */
#define AV_FEAT_CONTROL         0x0001  /* controller role */
#define AV_FEAT_TARGET          0x0002  /* target role */
#define AV_FEAT_INT             0x0004  /* initiator */
#define AV_FEAT_ACP             0x0008  /* acceptor */
#define AV_FEAT_VENDOR          0x0010  /* vendor dependent commands */
#define AV_FEAT_METADATA        0x0020  /* metadata Transfer */
typedef uint32_t  tAV_APP_FEAT;

#define AUDIO_IDLE_SUSPEND_TIMEOUT_IN_SECONDS 3

/* Entry in peer_cb table reserved for acceptor connection */
#define AV_IDX_ACP              0

/*  BIT pool calculation
    ********************
    bit_rate = 8*frame_length*fs(in kHz)/nrof_subbands/nrof_blocks,

    where,
    frame_length = 4+(4*nrof_subbands*nrof_channels)/8
                    +[nrof_blocks*nrof_channels*bitpool/8]
    for the MONO and DUAL_CHANNEL channel modes
    frame_length = 4+(4*nrof_subbands*nrof_channels)/8
                   +[(join*nrof_subbands + nrof_blocks*nrof_channels*bitpool)/8]
    for the STEREO a and JOIN_STEREO channel modes
    join = 1 when join stereo is used else 0

    for fs = 16kHz, nrof_subbands = 8, nrof_blocks = 16, nrof_channels = 1
    and channel mode = MONO
    => bit_rate = frame_length.
    => frame_length = 8+2*bitpool.
    Therefore, bitpool = (bit_rate-8)/2
    For bit_rate of 128kbps, bitpool = 60

    reference : A2DP spec v12
*/

#endif  /* A2DP_APP_H */
