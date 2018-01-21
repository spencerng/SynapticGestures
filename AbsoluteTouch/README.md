# AbsoluteTouch

Synaptics "absolute mode" emulation in software. Ever wanted to use
your laptop touchpad to play osu!, or to draw your signature? Well,
now you can!

## Requirements

- A Synaptics touchpad
- Synaptics COM libraries (if you installed the drivers, you probably have this)

## Command-line arguments

| Argument         | Description                                                                    |
|------------------|--------------------------------------------------------------------------------|
| `-t x1,y1,x2,y2` | Sets the mapped touchpad region (0 to 100, 0 = left/top, 100 = right/bottom)   |
| `-s x1,y1,x2,y2` | Sets the mapped screen region (see above)                                      |
| `-w weight`      | Sets the touch smoothing factor (0 to 100, 0 for no smoothing)                 |
| `-c`             | Enables left clicking by touching the touchpad                                 |
| `-m`             | Enables your touchpad when the program starts, and disables it on exit         |

Examples:
- `-w 50 -t 50,0,100,100` apply 50% touch smoothing and only use the right
half of the touchpad.
- `-t 50,0,100,50 -s 50,0,100,50` make the top-right quarter of the
touchpad map to the top-right quarter of the screen.

## License

Distributed under the [MIT License](http://opensource.org/licenses/MIT).
