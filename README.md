# **ECS + OpenGL Game-engine Prototype**

* A self-built game engine framework using OpenGL and a custom Entity-Component-System (ECS) architecture.  

* This project is a study in low-level graphics programming and modular game logic design.


## **Features**
- Custom ECS implementation in C++
- OpenGL-based 3D rendering


## **Libraries used**
- GLAD
- GLFW
- GLM
- stb


## **2025/04/21: Create a 3D model import pipeline**
1. Import 3D model with `Assimp`
2. -> Convert to `Intermediate data`
3. -> Convert data to `Component`
4. -> Create `Entity` and assign `Component`
5. -> `Draw`

![現状の成果](Images/readme_01.png)