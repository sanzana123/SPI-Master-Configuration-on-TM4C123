# Bare-Metal SPI Master Initialization – TM4C123
## 📌 Description
This project demonstrates bare-metal programming to initialize and use the SSI0 (SPI) module of the TM4C123GH6PM microcontroller as a master device. The code sets up SPI on Port A (PA2–PA5) and transmits data over the SPI bus.

## 🧰 Features
- Direct register-level configuration (bare-metal)
- Uses system clock for SPI

### Configures:
- PA2 as SSIClk
- PA3 as SSIFss
- PA4 as SSITx
- PA5 as SSIRx

### Sends an 8-bit data value (example: 'P')

# 🛠️ How to Build
## 🔧 Requirements
- TM4C123GH6PM microcontroller (or Tiva C LaunchPad)
- Code Composer Studio
- Header files: clock.h, wait.h, and tm4c123gh6pm.h

# 🏗️ Steps
- Initialize system clock
- Set system clock to 20MHz using initSystemClckTo20Mz() (defined in clock.h)
- Call initSPI()
- Enables SSI0 and configures GPIO port A pins for SPI peripheral mode.
- Sets clock polarity, phase, frame format, and bit rate.
- Send data
- Use SSI_send_data(char data) to transmit a byte via SPI.
