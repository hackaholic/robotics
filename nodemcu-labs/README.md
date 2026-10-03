# NodeMCU PlatformIO Labs

This repository contains small NodeMCU / ESP8266 experiments used while
learning microcontroller fundamentals.

Topics include:

- GPIO
- Analog / ADC
- I2C
- SPI
- UART
- PWM
- Interrupts
- Sensors and peripherals

The project uses:

- NodeMCU ESP8266
- Arduino framework
- PlatformIO

---

# 1. PlatformIO Project Basics

A normal PlatformIO project looks like:

```text
project/
├── include/
├── lib/
├── src/
│   └── main.cpp
├── test/
└── platformio.ini
```

The important parts are:

```text
platformio.ini
      │
      ├── defines board
      ├── defines framework
      ├── defines build environments
      └── defines which source files are compiled

src/
      │
      └── application source code

lib/
      │
      └── project-specific reusable libraries

include/
      │
      └── shared header files
```

By default PlatformIO compiles all applicable source files under `src/`.

---

# 2. Creating a Standalone PlatformIO Project

A completely independent project can be created using:

```bash
mkdir gpio-blink
cd gpio-blink

pio project init \
    --board nodemcuv2 \
    --project-option="framework=arduino"
```

PlatformIO creates:

```text
gpio-blink/
├── include/
├── lib/
├── src/
├── test/
└── platformio.ini
```

Create the application:

```bash
touch src/main.cpp
```

Example:

```cpp
#include <Arduino.h>

void setup()
{
    pinMode(D3, OUTPUT);
}

void loop()
{
    digitalWrite(D3, HIGH);
    delay(1000);

    digitalWrite(D3, LOW);
    delay(1000);
}
```

Build:

```bash
pio run
```

Upload:

```bash
pio run -t upload
```

This architecture is useful when each application should be a completely
independent project.

Example:

```text
robotics/
├── gpio-blink/
│   ├── platformio.ini
│   ├── lib/
│   └── src/
│
├── adc-test/
│   ├── platformio.ini
│   ├── lib/
│   └── src/
│
└── i2c-test/
    ├── platformio.ini
    ├── lib/
    └── src/
```

The disadvantage for learning labs is duplication: every experiment has its
own PlatformIO configuration and project directories.

---

# 3. Multi-Lab PlatformIO Architecture

For our learning labs we use **one PlatformIO project with multiple
environments**.

Create the project once:

```bash
mkdir nodemcu-labs
cd nodemcu-labs

pio project init \
    --board nodemcuv2 \
    --project-option="framework=arduino"
```

Instead of creating a new PlatformIO project for every experiment, create
directories inside `src/`.

Example:

```text
nodemcu-labs/
│
├── platformio.ini
├── include/
├── lib/
│
└── src/
    │
    ├── gpio_output/
    │   └── main.cpp
    │
    ├── gpio_input/
    │   └── main.cpp
    │
    ├── adc/
    │   └── main.cpp
    │
    └── i2c/
        └── main.cpp
```

All labs share:

```text
platformio.ini
lib/
include/
```

while each lab has its own source directory.

---

# 4. Why Build Filtering Is Needed

Normally PlatformIO sees:

```text
src/
├── gpio_output/main.cpp
├── gpio_input/main.cpp
├── adc/main.cpp
└── i2c/main.cpp
```

and attempts to compile the source files together.

But each experiment may contain its own:

```cpp
void setup()
{
}

void loop()
{
}
```

That would cause duplicate definitions.

We therefore tell each PlatformIO environment which source directory it
should compile.

---

# 5. build_src_filter

PlatformIO supports source filtering.

The basic syntax is:

```text
-<pattern>     exclude matching source files
+<pattern>     include matching source files
```

For example:

```ini
build_src_filter =
    -<*>
    +<gpio_output/*>
```

means:

```text
-<*>
 │
 └── exclude everything

+<gpio_output/*>
 │
 └── include everything inside src/gpio_output/
```

Therefore:

```text
src/
├── gpio_output/       ← BUILD THIS
│   └── main.cpp
│
├── gpio_input/        ← ignore
│   └── main.cpp
│
├── adc/               ← ignore
│   └── main.cpp
│
└── i2c/               ← ignore
    └── main.cpp
```

---

# 6. PlatformIO Environments

Each lab gets its own environment in `platformio.ini`.

Example:

```ini
[env:gpio_output]
platform = espressif8266
board = nodemcuv2
framework = arduino

build_src_filter =
    -<*>
    +<gpio_output/*>


[env:gpio_input]
platform = espressif8266
board = nodemcuv2
framework = arduino

build_src_filter =
    -<*>
    +<gpio_input/*>


[env:adc]
platform = espressif8266
board = nodemcuv2
framework = arduino

build_src_filter =
    -<*>
    +<adc/*>


[env:i2c]
platform = espressif8266
board = nodemcuv2
framework = arduino

build_src_filter =
    -<*>
    +<i2c/*>
```

The environment name is the value after:

```text
env:
```

For example:

```ini
[env:adc]
```

creates an environment named:

```text
adc
```

---

# 7. Selecting a Lab from the CLI

The `-e` option selects an environment.

GPIO output:

```bash
pio run -e gpio_output -t upload
```

GPIO input:

```bash
pio run -e gpio_input -t upload
```

ADC:

```bash
pio run -e adc -t upload
```

I2C:

```bash
pio run -e i2c -t upload
```

The flow is therefore:

```text
pio run -e adc -t upload
          │
          ▼
     [env:adc]
          │
          ▼
   build_src_filter
          │
          ▼
      src/adc/*
          │
          ▼
       compile
          │
          ▼
       firmware
          │
          ▼
       ESP8266
```

---

# 8. Multiple Source Files Inside One Lab

A lab does not have to contain only `main.cpp`.

For example:

```text
src/
└── i2c/
    ├── main.cpp
    ├── scanner.cpp
    ├── oled.cpp
    └── helpers.cpp
```

Because the environment contains:

```ini
build_src_filter =
    -<*>
    +<i2c/*>
```

all files inside the `i2c` directory are compiled together:

```text
main.cpp
scanner.cpp
oled.cpp
helpers.cpp
     │
     ▼
one firmware
```

This allows experiments to grow without putting everything into one file.

---

# 9. Shared Code

Code used by several experiments can be placed in:

```text
include/
```

for headers, or:

```text
lib/
```

for reusable project libraries.

Example:

```text
nodemcu-labs/
│
├── include/
│   └── pins.h
│
├── lib/
│   └── DisplayUtils/
│       ├── DisplayUtils.cpp
│       └── DisplayUtils.h
│
└── src/
    ├── adc/
    ├── gpio_output/
    └── i2c/
```

This code can then be shared between multiple environments.

---

# 10. Final Lab Architecture

Our repository will gradually become:

```text
nodemcu-labs/
│
├── platformio.ini
├── README.md
│
├── include/
├── lib/
│
└── src/
    │
    ├── 01_gpio_output/
    │   └── main.cpp
    │
    ├── 02_gpio_input/
    │   └── main.cpp
    │
    ├── 03_adc/
    │   └── main.cpp
    │
    ├── 04_i2c/
    │   └── main.cpp
    │
    ├── 05_spi/
    │   └── main.cpp
    │
    ├── 06_uart/
    │   └── main.cpp
    │
    └── ...
```

Each experiment is selected through its PlatformIO environment.

Example:

```bash
pio run -e gpio_output -t upload
```

rather than manually replacing `src/main.cpp`.

---

# Architecture Mental Model

```text
                 ONE PLATFORMIO PROJECT

                    platformio.ini
                          │
          ┌───────────────┼────────────────┐
          │               │                │
          ▼               ▼                ▼
   env:gpio_output      env:adc          env:i2c
          │               │                │
          ▼               ▼                ▼
 src/gpio_output/*     src/adc/*        src/i2c/*
          │               │                │
          └───────────────┬────────────────┘
                          │
                    shared include/
                    shared lib/
                          │
                          ▼
                     ESP8266
```

This gives us:

- one repository
- one PlatformIO project
- shared libraries
- shared headers
- isolated experiments
- multiple source files per experiment
- CLI-selectable labs
- no duplicate `setup()` / `loop()` conflicts