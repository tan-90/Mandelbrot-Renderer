# MandelbrotRenderer

## About
I wanted to show how quickly you can get a simple program paralelized over all pixels of a canvas by using OpenGL fragment shaders. My (obvious) choice was to render fractals, so this realtime interactive [Mandelbrot Set](https://goo.gl/JIVgRu) renderer was born. It's written in C++ and makes it very easy to write and use your own fragment shader (that here works as a way to define a program you want to run for every pixel).

![Mandelbrot Renderer](https://i.imgur.com/DFlpDSE.jpg)

## Notes
This is meant to be a proof of concept, so there are no custom floating points for the extra precision that would be needed or a really good input system. Maybe it will become a fully featured project one day.

## Running
The dependencies are part of the repository and this doesn't use any external resources, so you should be able to just build and run it with Visual Studio.
