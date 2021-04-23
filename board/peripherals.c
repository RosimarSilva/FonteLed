/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v7.0
processor: MKE15Z32xxx4
package_id: MKE15Z32VLF4
mcu_data: ksdk2_0
processor_version: 7.0.2
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: 668c2c4f-6a76-4478-911c-64d186ca3f40
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system_54b53072540eeeb8f8e9343e71f28176'
- global_system_definitions: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'msg'
- type_id: 'msg_6e2baaf3b97dbeef01c0043275f9a0e7'
- global_messages: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * LPUART0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LPUART0'
- type: 'lpuart'
- mode: 'interrupts'
- custom_name_enabled: 'false'
- type_id: 'lpuart_bebe3e12b6ec22bbd14199038f2bf459'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'LPUART0'
- config_sets:
  - lpuartConfig_t:
    - lpuartConfig:
      - clockSource: 'LpuartClock'
      - lpuartSrcClkFreq: 'BOARD_BootClockRUN'
      - baudRate_Bps: '9600'
      - parityMode: 'kLPUART_ParityDisabled'
      - dataBitsCount: 'kLPUART_EightDataBits'
      - isMsb: 'false'
      - stopBitCount: 'kLPUART_OneStopBit'
      - txFifoWatermark: '0'
      - rxFifoWatermark: '4'
      - enableRxRTS: 'false'
      - enableTxCTS: 'false'
      - txCtsSource: 'kLPUART_CtsSourcePin'
      - txCtsConfig: 'kLPUART_CtsSampleAtStart'
      - rxIdleType: 'kLPUART_IdleTypeStartBit'
      - rxIdleConfig: 'kLPUART_IdleCharacter128'
      - enableTx: 'true'
      - enableRx: 'true'
  - interruptsCfg:
    - interrupts: 'kLPUART_RxDataRegFullInterruptEnable'
    - interrupt_vectors:
      - enable_rx_tx_irq: 'true'
      - interrupt_rx_tx:
        - IRQn: 'LPUART0_IRQn'
        - enable_priority: 'true'
        - priority: '3'
        - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const lpuart_config_t LPUART0_config = {
  .baudRate_Bps = 9600,
  .parityMode = kLPUART_ParityDisabled,
  .dataBitsCount = kLPUART_EightDataBits,
  .isMsb = false,
  .stopBitCount = kLPUART_OneStopBit,
  .txFifoWatermark = 0,
  .rxFifoWatermark = 4,
  .enableRxRTS = false,
  .enableTxCTS = false,
  .txCtsSource = kLPUART_CtsSourcePin,
  .txCtsConfig = kLPUART_CtsSampleAtStart,
  .rxIdleType = kLPUART_IdleTypeStartBit,
  .rxIdleConfig = kLPUART_IdleCharacter128,
  .enableTx = true,
  .enableRx = true
};

void LPUART0_init(void) {
  LPUART_Init(LPUART0_PERIPHERAL, &LPUART0_config, LPUART0_CLOCK_SOURCE);
  LPUART_EnableInterrupts(LPUART0_PERIPHERAL, kLPUART_RxDataRegFullInterruptEnable);
  /* Interrupt vector LPUART0_IRQn priority settings in the NVIC */
  NVIC_SetPriority(LPUART0_SERIAL_RX_TX_IRQN, LPUART0_SERIAL_RX_TX_IRQ_PRIORITY);
  /* Enable interrupt LPUART0_IRQn request in the NVIC */
  EnableIRQ(LPUART0_SERIAL_RX_TX_IRQN);
}

/***********************************************************************************************************************
 * GPIOE initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'GPIOE'
- type: 'gpio'
- mode: 'GPIO'
- custom_name_enabled: 'false'
- type_id: 'gpio_be9de87e5addb6b0f416d9acbab34797'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'GPIOE'
- config_sets:
  - fsl_gpio:
    - enable_irq: 'false'
    - port_interrupt:
      - IRQn: 'PORTAE_IRQn'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
    - quick_selection: 'QS_GPIO_1'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

void GPIOE_init(void) {
  /* Make sure, the clock gate for port E is enabled (e. g. in pin_mux.c) */
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  LPUART0_init();
  GPIOE_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
