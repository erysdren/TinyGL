# TinyGL

An extension of [Fabrice Bellard's TinyGL](https://bellard.org/TinyGL/) project.

Original versions (in `.tar.gz` format) can be found in the "legacy" folder.

See `examples/ui.c` for an example of implementing TinyGL under SDL2.

## Todo

- [x] Port examples to platform-agnostic window system
- [x] Remove BeOS code
- [x] Remove GLX & NGLX
- [ ] Fix memory leaks in original code
- [ ] Clean up syntax where necessary
- [ ] Implement more GLU functions
- [ ] Implement areas of OpenGL 1.1 and 1.2 that are missing
- [ ] Fixed-point math
- [ ] Native 8bpp renderng

## License

MIT License

Copyright (c) 1997-2022 Fabrice Bellard

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
