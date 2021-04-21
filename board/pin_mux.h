/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*! @name PORTB0 (number 27), DisplayRx
  @{ */
#define BOARD_INITPINS_DisplayRx_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_DisplayRx_PIN 0U     /*!<@brief PORTB pin index: 0 */
                                            /* @} */

/*! @name PORTB1 (number 26), DisplayTx
  @{ */
#define BOARD_INITPINS_DisplayTx_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_DisplayTx_PIN 1U     /*!<@brief PORTB pin index: 1 */
                                            /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/