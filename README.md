# TinyGL

![a 3D render of multiple gears floating in empty space, one red, one blue, and one green.](.github/tgl_gears.png)

This is an extension of [Fabrice Bellard's TinyGL](https://bellard.org/TinyGL/) project.

TinyGL is an implementation of the OpenGL 1.2 specification in pure software, using no hardware acceleration. It is designed to be lightweight and fast, using highly optimized rasterization routines originally written by [Fabrice Bellard](https://bellard.org).

The minimum requirements to compile & run this code is ISO C99 compliance and a 32-bit processor respectively.

The original versions (in `.tar.gz` format) can be found in the "contrib" folder.

## Examples

- [`bounce.c`](./examples/bounce.c) - Bouncing ball demo by Brian Paul
- [`cube.c`](./examples/cube.c) - glDrawElements example by erysdren
- [`gears.c`](./examples/gears.c) - Gears demo by Brian Paul
- [`mech.c`](./examples/mech.c) - glutmech by Simon Parkinson-Bates
- [`spin.c`](./examples/spin.c) - Spinning box demo by Brian Paul
- [`texobj.c`](./examples/texobj.c) - Textured object demo by Brian Paul
- [`ui_headless.c`](./examples/ui_headless.c) - Render TinyGL frame to image file
- [`ui.c`](./examples/ui.c) - TinyGL under SDL2 example

## Thirdparty

- [`stb_image_write.h`](https://github.com/nothings/stb/)

## Platforms

TinyGL is compatible with Clang, GCC, TinyCC, and Open Watcom. Tested platforms:

- Linux
- Windows
- Haiku
- MS-DOS
- OS/2

## License

MIT License

Copyright (c) 1997-2022 Fabrice Bellard

Copyright (c) 2023 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
