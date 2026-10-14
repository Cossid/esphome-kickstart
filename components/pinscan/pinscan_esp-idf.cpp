#if defined(USE_ESP_IDF) && !defined(USE_ARDUINO)

#include "pinscan.h"
#include "driver/gpio.h"

namespace esphome {
namespace pinscan {

static const char *const TAG = "pinscan";

// Pins that can interfere with the chip or the device's own link are left out of the pin map unless
// the matching flag is defined (e.g. via build_flags): PINSCAN_ALLOW_FLASH_PINS (SPI flash/PSRAM),
// PINSCAN_ALLOW_USB_PINS (USB D+/D-), PINSCAN_ALLOW_UART_PINS (UART0 TX/RX).
// Note that enabling these flags changes which GPIO each pin index maps to.

#if defined(USE_ESP32_VARIANT_ESP32C3)
static const int PIN_MAP[] = {
    0,   // GPIO0 / ADC1_0
    1,   // GPIO1 / ADC1_1
    2,   // GPIO2 / ADC1_2
    3,   // GPIO3 / ADC1_3
    4,   // GPIO4 / ADC1_4 / MTMS
    5,   // GPIO5 / ADC2_0 / MTDI
    6,   // GPIO6 / MTCK
    7,   // GPIO7 / MTDO
    8,   // GPIO8
    9,   // GPIO9
    10,  // GPIO10
#ifdef PINSCAN_ALLOW_FLASH_PINS
    11,  // GPIO11 / VDD_SPI / SPI flash
    12,  // GPIO12 / SPI flash
    13,  // GPIO13 / SPI flash
    14,  // GPIO14 / SPI flash
    15,  // GPIO15 / SPI flash
    16,  // GPIO16 / SPI flash
    17,  // GPIO17 / SPI flash
#endif
#ifdef PINSCAN_ALLOW_USB_PINS
    18,  // GPIO18 / USB D-
    19,  // GPIO19 / USB D+
#endif
#ifdef PINSCAN_ALLOW_UART_PINS
    20,  // GPIO20 / U0RXD
    21,  // GPIO21 / U0TXD
#endif
};
#elif defined(USE_ESP32_VARIANT_ESP32S2)
static const int PIN_MAP[] = {
    0,   // GPIO0
    1,   // GPIO1
    2,   // GPIO2
    3,   // GPIO3
    4,   // GPIO4
    5,   // GPIO5
    6,   // GPIO6
    7,   // GPIO7
    8,   // GPIO8
    9,   // GPIO9
    10,  // GPIO10
    11,  // GPIO11
    12,  // GPIO12
    13,  // GPIO13
    14,  // GPIO14
    15,  // GPIO15
    16,  // GPIO16
    17,  // GPIO17
    18,  // GPIO18
#ifdef PINSCAN_ALLOW_USB_PINS
    19,  // GPIO19 / USB D-
    20,  // GPIO20 / USB D+
#endif
    21,  // GPIO21
#ifdef PINSCAN_ALLOW_FLASH_PINS
    26,  // GPIO26 / SPI flash/PSRAM
    27,  // GPIO27 / SPI flash/PSRAM
    28,  // GPIO28 / SPI flash/PSRAM
    29,  // GPIO29 / SPI flash/PSRAM
    30,  // GPIO30 / SPI flash/PSRAM
    31,  // GPIO31 / SPI flash/PSRAM
    32,  // GPIO32 / SPI flash/PSRAM
#endif
    33,  // GPIO33
    34,  // GPIO34
    35,  // GPIO35
    36,  // GPIO36
    37,  // GPIO37
    38,  // GPIO38
    39,  // GPIO39 / MTCK
    40,  // GPIO40 / MTDO
    41,  // GPIO41 / MTDI
    42,  // GPIO42 / MTMS
#ifdef PINSCAN_ALLOW_UART_PINS
    43,  // GPIO43 / U0TXD
    44,  // GPIO44 / U0RXD
#endif
    45,  // GPIO45
    46,  // GPIO46 / input only
};
#elif defined(USE_ESP32_VARIANT_ESP32S3)
static const int PIN_MAP[] = {
    0,   // GPIO0
    1,   // GPIO1
    2,   // GPIO2
    3,   // GPIO3
    4,   // GPIO4
    5,   // GPIO5
    6,   // GPIO6
    7,   // GPIO7
    8,   // GPIO8
    9,   // GPIO9
    10,  // GPIO10
    11,  // GPIO11
    12,  // GPIO12
    13,  // GPIO13
    14,  // GPIO14
    15,  // GPIO15
    16,  // GPIO16
    17,  // GPIO17
    18,  // GPIO18
#ifdef PINSCAN_ALLOW_USB_PINS
    19,  // GPIO19 / USB D-
    20,  // GPIO20 / USB D+
#endif
    21,  // GPIO21
#ifdef PINSCAN_ALLOW_FLASH_PINS
    26,  // GPIO26 / SPI flash/PSRAM
    27,  // GPIO27 / SPI flash/PSRAM
    28,  // GPIO28 / SPI flash/PSRAM
    29,  // GPIO29 / SPI flash/PSRAM
    30,  // GPIO30 / SPI flash/PSRAM
    31,  // GPIO31 / SPI flash/PSRAM
    32,  // GPIO32 / SPI flash/PSRAM
    33,  // GPIO33 / octal flash/PSRAM
    34,  // GPIO34 / octal flash/PSRAM
    35,  // GPIO35 / octal flash/PSRAM
    36,  // GPIO36 / octal flash/PSRAM
    37,  // GPIO37 / octal flash/PSRAM
#endif
    38,  // GPIO38
    39,  // GPIO39 / MTCK
    40,  // GPIO40 / MTDO
    41,  // GPIO41 / MTDI
    42,  // GPIO42 / MTMS
#ifdef PINSCAN_ALLOW_UART_PINS
    43,  // GPIO43 / U0TXD
    44,  // GPIO44 / U0RXD
#endif
    45,  // GPIO45
    46,  // GPIO46
    47,  // GPIO47
    48,  // GPIO48
};
#elif defined(USE_ESP32_VARIANT_ESP32C2)
static const int PIN_MAP[] = {
    0,   // GPIO0
    1,   // GPIO1
    2,   // GPIO2
    3,   // GPIO3
    4,   // GPIO4
    5,   // GPIO5
    6,   // GPIO6
    7,   // GPIO7
    8,   // GPIO8 / strapping
    9,   // GPIO9 / strapping
    10,  // GPIO10
#ifdef PINSCAN_ALLOW_FLASH_PINS
    11,  // GPIO11 / VDD_SPI / SPI flash
    12,  // GPIO12 / SPI flash
    13,  // GPIO13 / SPI flash
    14,  // GPIO14 / SPI flash
    15,  // GPIO15 / SPI flash
    16,  // GPIO16 / SPI flash
    17,  // GPIO17 / SPI flash
#endif
    18,  // GPIO18
#ifdef PINSCAN_ALLOW_UART_PINS
    19,  // GPIO19 / U0RXD
    20,  // GPIO20 / U0TXD
#endif
};
#elif defined(USE_ESP32_VARIANT_ESP32C5)
static const int PIN_MAP[] = {
    0,   // GPIO0
    1,   // GPIO1
    2,   // GPIO2
    3,   // GPIO3
    4,   // GPIO4
    5,   // GPIO5
    6,   // GPIO6
    7,   // GPIO7
    8,   // GPIO8
    9,   // GPIO9
    10,  // GPIO10
#ifdef PINSCAN_ALLOW_UART_PINS
    11,  // GPIO11 / U0TXD
    12,  // GPIO12 / U0RXD
#endif
#ifdef PINSCAN_ALLOW_USB_PINS
    13,  // GPIO13 / USB D-
    14,  // GPIO14 / USB D+
#endif
    15,  // GPIO15 / strapping
#ifdef PINSCAN_ALLOW_FLASH_PINS
    16,  // GPIO16 / SPI flash
    17,  // GPIO17 / SPI flash
    18,  // GPIO18 / SPI flash
    19,  // GPIO19 / SPI flash
    20,  // GPIO20 / SPI flash
    21,  // GPIO21 / SPI flash
    22,  // GPIO22 / SPI flash
#endif
    23,  // GPIO23
    24,  // GPIO24
    25,  // GPIO25
    26,  // GPIO26
    27,  // GPIO27
    28,  // GPIO28
};
#elif defined(USE_ESP32_VARIANT_ESP32C6)
static const int PIN_MAP[] = {
    0,   // GPIO0
    1,   // GPIO1
    2,   // GPIO2
    3,   // GPIO3
    4,   // GPIO4
    5,   // GPIO5
    6,   // GPIO6
    7,   // GPIO7
    8,   // GPIO8
    9,   // GPIO9
    10,  // GPIO10
    11,  // GPIO11
#ifdef PINSCAN_ALLOW_USB_PINS
    12,  // GPIO12 / USB D-
    13,  // GPIO13 / USB D+
#endif
    14,  // GPIO14
    15,  // GPIO15
#ifdef PINSCAN_ALLOW_UART_PINS
    16,  // GPIO16 / U0TXD
    17,  // GPIO17 / U0RXD
#endif
    18,  // GPIO18
    19,  // GPIO19
    20,  // GPIO20
    21,  // GPIO21
    22,  // GPIO22
    23,  // GPIO23
#ifdef PINSCAN_ALLOW_FLASH_PINS
    24,  // GPIO24 / SPI flash
    25,  // GPIO25 / SPI flash
    26,  // GPIO26 / SPI flash
    27,  // GPIO27 / SPI flash
    28,  // GPIO28 / SPI flash
    29,  // GPIO29 / SPI flash
    30,  // GPIO30 / SPI flash
#endif
};
#elif defined(USE_ESP32_VARIANT_ESP32C61)
static const int PIN_MAP[] = {
    0,   // GPIO0
    1,   // GPIO1
    2,   // GPIO2
    3,   // GPIO3
    4,   // GPIO4
    5,   // GPIO5
    6,   // GPIO6
    7,   // GPIO7
    8,   // GPIO8
    9,   // GPIO9
    10,  // GPIO10
    11,  // GPIO11
#ifdef PINSCAN_ALLOW_USB_PINS
    12,  // GPIO12 / USB D-
    13,  // GPIO13 / USB D+
#endif
    14,  // GPIO14
    15,  // GPIO15
#ifdef PINSCAN_ALLOW_UART_PINS
    16,  // GPIO16 / U0TXD
    17,  // GPIO17 / U0RXD
#endif
    18,  // GPIO18
    19,  // GPIO19
    20,  // GPIO20
    21,  // GPIO21
    22,  // GPIO22
    23,  // GPIO23
#ifdef PINSCAN_ALLOW_FLASH_PINS
    24,  // GPIO24 / SPI flash
    25,  // GPIO25 / SPI flash
    26,  // GPIO26 / SPI flash
    27,  // GPIO27 / SPI flash
    28,  // GPIO28 / SPI flash
    29,  // GPIO29 / SPI flash
    30,  // GPIO30 / SPI flash
#endif
};
#elif defined(USE_ESP32_VARIANT_ESP32H2)
static const int PIN_MAP[] = {
    0,   // GPIO0
    1,   // GPIO1
    2,   // GPIO2
    3,   // GPIO3
    4,   // GPIO4
    5,   // GPIO5
    8,   // GPIO8
    9,   // GPIO9
    10,  // GPIO10
    11,  // GPIO11
    12,  // GPIO12
    13,  // GPIO13
    14,  // GPIO14
#ifdef PINSCAN_ALLOW_FLASH_PINS
    15,  // GPIO15 / SPI flash
    16,  // GPIO16 / SPI flash
    17,  // GPIO17 / SPI flash
    18,  // GPIO18 / SPI flash
    19,  // GPIO19 / SPI flash
    20,  // GPIO20 / SPI flash
    21,  // GPIO21 / SPI flash
#endif
    22,  // GPIO22
#ifdef PINSCAN_ALLOW_UART_PINS
    23,  // GPIO23 / U0RXD
    24,  // GPIO24 / U0TXD
#endif
    25,  // GPIO25
#ifdef PINSCAN_ALLOW_USB_PINS
    26,  // GPIO26 / USB D-
    27,  // GPIO27 / USB D+
#endif
};
#elif defined(USE_ESP32_VARIANT_ESP32P4)
static const int PIN_MAP[] = {
    0,   // GPIO0
    1,   // GPIO1
    2,   // GPIO2
    3,   // GPIO3
    4,   // GPIO4
    5,   // GPIO5
    6,   // GPIO6
    7,   // GPIO7
    8,   // GPIO8
    9,   // GPIO9
    10,  // GPIO10
    11,  // GPIO11
    12,  // GPIO12
    13,  // GPIO13
    14,  // GPIO14
    15,  // GPIO15
    16,  // GPIO16
    17,  // GPIO17
    18,  // GPIO18
    19,  // GPIO19
    20,  // GPIO20
    21,  // GPIO21
    22,  // GPIO22
    23,  // GPIO23
#ifdef PINSCAN_ALLOW_USB_PINS
    24,  // GPIO24 / USB D-
    25,  // GPIO25 / USB D+
#endif
    26,  // GPIO26
    27,  // GPIO27
    28,  // GPIO28
    29,  // GPIO29
    30,  // GPIO30
    31,  // GPIO31
    32,  // GPIO32
    33,  // GPIO33
    34,  // GPIO34
    35,  // GPIO35
    36,  // GPIO36
#ifdef PINSCAN_ALLOW_UART_PINS
    37,  // GPIO37 / U0TXD
    38,  // GPIO38 / U0RXD
#endif
    39,  // GPIO39
    40,  // GPIO40
    41,  // GPIO41
    42,  // GPIO42
    43,  // GPIO43
    44,  // GPIO44
    45,  // GPIO45
    46,  // GPIO46
    47,  // GPIO47
    48,  // GPIO48
    49,  // GPIO49
    50,  // GPIO50
    51,  // GPIO51
    52,  // GPIO52
    53,  // GPIO53
    54,  // GPIO54
};
#elif defined(USE_ESP32)
static const int PIN_MAP[] = {
    0,  // GPIO0
    1,  // GPIO1
    2,  // GPIO2
    3,  // GPIO3
    4,  // GPIO4
    5,  // GPIO5
#ifdef PINSCAN_ALLOW_FLASH_PINS
    6,   // GPIO6 / SPI flash
    7,   // GPIO7 / SPI flash
    8,   // GPIO8 / SPI flash
    9,   // GPIO9 / SPI flash
    10,  // GPIO10 / SPI flash
    11,  // GPIO11 / SPI flash
#endif
    12,  // GPIO12
    13,  // GPIO13
    14,  // GPIO14
    15,  // GPIO15
    16,  // GPIO16
    17,  // GPIO17
    18,  // GPIO18
    19,  // GPIO19 / MISO
    21,  // GPIO21 / SDA
    22,  // GPIO22 / SCL
    23,  // GPIO23 / MOSI
    25,  // GPIO25 / DAC1
    26,  // GPIO26 / DAC2
    27,  // GPIO27
    32,  // GPIO32
    33,  // GPIO33
    34,  // GPIO34
    35,  // GPIO35
    36,  // GPIO36
    39,  // GPIO39
};
#else
#error "Unsupported chip type"
#endif

void Pinscan::setup() { ESP_LOGCONFIG(TAG, "Setting up Pinscan..."); }

void Pinscan::dump_config() { ESP_LOGCONFIG(TAG, "Pinscan:"); }

void Pinscan::set_pin(int pin) {
  if (pin != -1) {
    pin = PIN_MAP[pin];
  }
  if (this->current_pin_ != pin && this->current_pin_ != -1) {
    gpio_set_direction((gpio_num_t) this->current_pin_, GPIO_MODE_INPUT);
    gpio_set_pull_mode((gpio_num_t) this->current_pin_, GPIO_FLOATING);
  }
  this->current_pin_ = pin;
}

void Pinscan::set_mode(int mode) {
  if (this->current_pin_ != -1) {
    gpio_num_t pin = (gpio_num_t) this->current_pin_;
    std::string modeStr = "";
    switch (mode) {
      case 0:
        gpio_set_direction(pin, GPIO_MODE_INPUT);
        gpio_set_pull_mode(pin, GPIO_FLOATING);
        this->current_state_ = -1;
        this->current_mode_ = 1;
        modeStr = "INPUT";
        break;
      case 1:
        gpio_set_direction(pin, GPIO_MODE_INPUT);
        gpio_set_pull_mode(pin, GPIO_PULLUP_ONLY);
        this->current_state_ = -1;
        this->current_mode_ = 1;
        modeStr = "INPUT_PULLUP";
        break;
      case 2:
        gpio_set_pull_mode(pin, GPIO_FLOATING);
        gpio_set_direction(pin, GPIO_MODE_OUTPUT);
        gpio_set_level(pin, 1);
        this->current_state_ = -1;
        this->current_mode_ = 0;
        modeStr = "OUTPUT_HIGH";
        break;
      case 3:
        gpio_set_pull_mode(pin, GPIO_FLOATING);
        gpio_set_direction(pin, GPIO_MODE_OUTPUT);
        gpio_set_level(pin, 0);
        this->current_state_ = -1;
        this->current_mode_ = 0;
        modeStr = "OUTPUT_LOW";
        break;
      default:
        gpio_set_direction(pin, GPIO_MODE_INPUT);
        gpio_set_pull_mode(pin, GPIO_FLOATING);
        modeStr = "OUTPUT_HIGH";
        break;
    }
    ESP_LOGD(TAG, "Changed pin to %d, mode: %s", this->current_pin_, modeStr.c_str());
  }
}

void Pinscan::update() {
  if (this->current_mode_ == 1 && this->current_pin_ != -1) {
    int newState = gpio_get_level((gpio_num_t) this->current_pin_);
    if (newState != this->current_state_) {
      this->current_state_ = newState;
      ESP_LOGD(TAG, "Pin changed to %s", (this->current_state_) ? "HIGH" : "LOW");
      if (this->pin_state_sensor_ != nullptr) {
        this->pin_state_sensor_->publish_state((this->current_state_) ? "HIGH" : "LOW");
      }
    }
  }
}

}  // namespace pinscan
}  // namespace esphome

#endif  // USE_ESP_IDF
