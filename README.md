# OpenGL .obj Quad Mesh Visualization

An OpenGL tool that can display .obj files in combination with a Quad Mesh. This tool has the ability to view .obj files, a widely-used file format for 3D models. This project is a successor of the previous project: [Quad Mesh Visualization](https://github.com/Wuschelbueb/quadmesh-visualization.git) which is a fork of Glitter.

## Getting started

- First you need to clone the repository on to your local machine

```bash
git clone --recursive https://github.com/Wuschelbueb/opengl_visualization.git
```

- Open the project with your favorite IDE.
- Build the CMake project.

## Credits

For this project I used a lot code snippets / ideas from two other projects:
- [Glitter](https://github.com/Polytonic/Glitter.git)
- [LearnOpenGL](https://github.com/JoeyDeVries/LearnOpenGL.git)

Both of these tools are designed to help new developers quickly and effectively learn the ins and outs of coding with OpenGL graphics library, as well as the GLFW library for creating and managing windows, and the CMake dependency management tool. At the start of a project, utilizing these tools can greatly reduce the time and effort required for setup and configuration. By automating many of the repetitive and time-consuming tasks involved in setting up a new project, such as managing dependencies and configuring the build environment, developers can focus on the more important aspects of their work, such as writing code and creating new features. These tools provide a streamlined and efficient workflow, allowing developers to quickly and easily dive into the project at hand and make progress more rapidly

In addition to the tools for coding with OpenGL, GLFW, and managing dependencies with CMake, I have also added several other libraries as git submodules. This allows you to easily include and manage these additional libraries within your project, ensuring that they are version controlled and easily shareable with other people. These git submodules have the advantage that they are easy to maintain and update as they can be updated independently of the rest of your project code. This allows you to take advantage of the latest features and bug fixes provided by these libraries without having to manually update them each time.

Functionality           | Library
----------------------- | ------------------------------------------
Mesh Loading            | [assimp](https://github.com/assimp/assimp)
User Interface          | [imgui](https://github.com/ocornut/imgui.git)
OpenGL Function Loader  | [glad](https://github.com/Dav1dde/glad)
Windowing and Input     | [glfw](https://github.com/glfw/glfw)
OpenGL Mathematics      | [glm](https://github.com/g-truc/glm)
Texture Loading         | [stb](https://github.com/nothings/stb)
File Dialog             | [nfd](https://github.com/btzy/nativefiledialog-extended.git)


## License
>The MIT License (MIT)

>Copyright (c) 2023 wuschelbueb

>Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

>The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
