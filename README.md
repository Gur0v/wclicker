# wclicker

**A dead simple autoclicker for Linux.**

`wclicker` is a minimal and secure CLI tool that simulates mouse clicks using the Linux `uinput` subsystem. It works on Wayland and X11 by injecting input at the kernel level: no reliance on desktop APIs.

## Usage

```bash
wclicker [-n count] [-d delay_ms]
````

* `-n count` — number of clicks to send (0 = infinite)
* `-d delay_ms` — delay between clicks in milliseconds (default: 100)

### Example

Click 20 times with 75ms delay:

```bash
sudo wclicker -n 20 -d 75
```

> Requires root: access to `/dev/uinput` needs elevated privileges.

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

