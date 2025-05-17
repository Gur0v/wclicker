# wclicker

A dead simple autoclicker for Linux.

## Overview

`wclicker` is a minimal and secure CLI tool that simulates mouse clicks using the Linux `uinput` subsystem. It works on both Wayland and X11 by injecting input at the kernel level, with no reliance on desktop APIs.

## Usage

```bash
wclicker [-n count] [-d delay_ms]
```

### Options

- `-n count` — Number of clicks to send (0 = infinite)
- `-d delay_ms` — Delay between clicks in milliseconds (default: 100)

### Example

Click 20 times with 75ms delay:

```bash
sudo wclicker -n 20 -d 75
```

> **Note:** Requires root permissions as access to `/dev/uinput` needs elevated privileges.

## Installation

```bash
git clone https://github.com/Gur0v/wclicker
cd wclicker
sudo make clean install
```

To uninstall:

```bash
sudo make uninstall
```

## License

[BSD-3-Clause License](LICENSE)
