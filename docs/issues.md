# issues
**Issues that exist in this project**

# **Engine**

## **window**
* ~~Automatically adjust the viewport and object size based on the window size~~(2025/04/15)

## **Structure**
* Introduce namespaces to prevent name duplication between classes and improve readability.
* Implementing an entity hierarchy
* Refactor to "safe release design"

## **user input**
* ~~Release mouse capture when the Control key is pressed~~(2025/04/15)
* Input abstraction for greater flexibility
* ~~When moving and rotating with WASD, the viewpoint feels strange.~~(2025/04/22)
    * -> Abolished `mouse_callback()`. Centralized mouse coordinate acquisition in InputMapping.

## **Asset**
* Implement an asset manager to centralize asset management
* **Optimize model loading process**
* Asset Manager Implementation
* Management of intermediate data (storage and release)


## **drawing**
* ~~Load 3D models~~(2025/04/17)
* ~~Create a system to pass 3D model textures to shaders~~(2025/04/21)
* ~~Integrate `mesh.Draw(render)` called in `model.cpp` into the drawing process in `RenderSystem.cpp`~~(2025/04/21)
* **Fix for normal vector processing in shaders**
* Implementing 3D model animation


## **Lighting**
* Add lighting support

---

# **Game**

## **camera**
* Converting Euler angles to Quaternions
* Implement CameraComponent

---

# **others**

## **docs**
* Draw and organize UML diagrams (class diagrams)

## **Project**
* ~~Organize folder structure~~(2025/04/18)
