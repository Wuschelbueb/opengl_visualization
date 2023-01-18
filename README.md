# OpenGL .obj visualization

A OpenGL tool to display .obj files.

Based on the project: https://github.com/Wuschelbueb/quadmesh-visualization.git which is a fork of Glitter.


This project took a lot of ideas from pretty much everywhere:
Glitter a dead simple boilerplate for OpenGL: https://github.com/Polytonic/Glitter.git
which I needed Glitter to get accustomed to OpenGL and all its dependencies.

A lot of code is straight from the learnOpenGL tutorial: https://github.com/JoeyDeVries/LearnOpenGL.git which I then adapted for my use.


In addition I used the following libraries as submodules:

- Assimp: https://github.com/assimp/assimp.git
- glad: https://github.com/Dav1dde/glad.git
- glfw: https://github.com/glfw/glfw.git
- glm: https://github.com/g-truc/glm.git
- imgui: https://github.com/Wuschelbueb/imgui_incl_cmake.git
- nativefiledialog: https://github.com/btzy/nativefiledialog-extended.git
- stb: https://github.com/nothings/stb.git

I created a cmake file which builds the whole project and allows you to launch it from the console.
